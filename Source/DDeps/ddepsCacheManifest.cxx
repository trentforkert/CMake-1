/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "ddepsCacheManifest.h"
#include "ddepsCacheFile.h"
#include "ddepsOptions.h"
#include <cmSystemTools.h>

// We need to track text in the manifest and the cachefiles, as
// there could be a module "api.txt", and a text "api.txt" which
// would be two different things. Without the information in both
// places, there would be no good way to tell what is what when
// reading the cache.
const std::string ddepsCacheManifest::MODULE_TYPE = "module";
const std::string ddepsCacheManifest::TEXT_TYPE = "text";

//----------------------------------------------------------------------------
ddepsCacheManifest::ddepsCacheManifest(std::string const& cachePath,
                                       std::string const& realPath,
                                       std::string const& cacheDir,
                                       ddepsOptions& options):
  ddepsCache(cachePath, realPath, cachePath + ".lock"),
  ConfigDir(cacheDir),
  Options(options),
  NextId(0)
{
  SetModified(); // always write CacheManifest
  Read();
}

//----------------------------------------------------------------------------
ddepsCacheManifest::~ddepsCacheManifest()
{
  Write();
  std::map<std::string, ddepsCacheFile*>::iterator it;
  for(it = ModuleFiles.begin(); it != ModuleFiles.end(); ++it)
    {
    delete it->second;
    }
  for(it = TextFiles.begin(); it != TextFiles.end(); ++it)
    {
    delete it->second;
    }
}

//----------------------------------------------------------------------------
void ddepsCacheManifest::WriteDependencyInfo(std::string const& src,
                                             std::string const& obj,
                                             bool writeInternalDeps)
{
  std::set<std::string> encounteredModules;
  std::set<std::string> encounteredTexts;
  std::deque<std::string> unprocessedModules;
  ddepsCacheFile* sourceModule = NULL;
  std::string sourceModuleName = "";

  // Try to find src in the cached modules
  std::map<std::string, ddepsCacheFile*>::const_iterator modFile;
  for(modFile = ModuleFiles.begin(); modFile != ModuleFiles.end(); ++modFile)
    {
    if(modFile->second->GetRealPath() == src)
      {
      sourceModuleName = modFile->first;
      break;
      }
    }

  // If src wasn't cached
  if(sourceModuleName == "")
    {
    // Parse src to figure out its module name
    sourceModule = CreateCacheFile(src, NextId++);
    sourceModule->ReadOrParse();
    sourceModuleName = sourceModule->GetModuleName();

    // Warn and return if we can't find the module by its parsed name
    if(!cmSystemTools::FileExists(FindModule(sourceModuleName).c_str()))
      {
      std::cerr << "DDeps Warning: "
                << sourceModule->GetRealPath()
                << " could not be found by the name \""
                << sourceModuleName
                << "\" in any of the following directories:"
                << std::endl;
      for(std::vector<std::string>::const_iterator
          it  = Options.ModuleImportPaths.begin();
          it != Options.ModuleImportPaths.end(); ++it)
        {
        std::cerr << "    " << *it << std::endl;
        }
      std::cerr << "Ensure your import directories are correct,"
                << "and that the module name matches the filename."
                << std::endl
                << sourceModule->GetRealPath()
                << " will be not be scanned for dependencies."
                << std::endl;
      return;
      }

    // Associate the name to our cache
    ModuleFiles[sourceModuleName] = sourceModule;
    }
  else
    {
    // Retrieve the cache
    sourceModule = ModuleFiles[sourceModuleName];
    }

  // Prevent re-parsing src's module
  encounteredModules.insert(sourceModuleName);


  // Write the current source as its own object dependency
  std::cout << obj << ": " << sourceModule->GetRealPath();

  if(writeInternalDeps)
    {
    std::cerr << "intdeps:" << obj << std::endl;
    std::cerr << "intdeps: " << sourceModule->GetRealPath() << std::endl;
    }


  // Get direct object dependencies
  sourceModule->GetObjDependencies(unprocessedModules,
                                   encounteredModules,
                                   encounteredTexts,
                                   true); // Include private imports

  // Continue processing all remaining dependencies
  for(std::deque<std::string>::iterator it = unprocessedModules.begin();
      it != unprocessedModules.end(); ++it)
    {
    ddepsCacheFile* dependency = GetModule(*it);
    if(dependency)
      {
      // Write the dependency
      std::cout << obj << ": " << dependency->GetRealPath() << std::endl;

      if(writeInternalDeps)
        {
        std::cerr << "intdeps: " << dependency->GetRealPath() << std::endl;
        }

      // Recurse dependencies
      dependency->GetObjDependencies(unprocessedModules,
                                     encounteredModules,
                                     encounteredTexts,
                                     false); // Exclude private imports
      }
    }

  // Also write all text imports as dependencies
  for(std::set<std::string>::const_iterator it = encounteredTexts.begin();
      it != encounteredTexts.end(); ++it)
    {
    ddepsCacheFile* dependency = GetText(*it);
    if(dependency)
      {
      std::cout << obj << ": " << dependency->GetRealPath() << std::endl;

      if(writeInternalDeps)
        {
        std::cerr << "intdeps: " << dependency->GetRealPath() << std::endl;
        }
      }
    }
}

//----------------------------------------------------------------------------
void ddepsCacheManifest::WriteImpl(std::ostream& ofs) const
{
  bool first = true;

  std::map<std::string, ddepsCacheFile*>::const_iterator it;
  for(it = ModuleFiles.begin(); it != ModuleFiles.end(); ++it)
    {
    // Ignore any invalid dependencies
    if(!it->second) continue;

    if(!first)
      {
      ofs << RECORD_DELIM;
      }
    first = false;
    ofs << std::hex << it->second->GetId()
        << UNIT_DELIM << MODULE_TYPE
        << UNIT_DELIM << it->first
        << UNIT_DELIM << it->second->GetRealPath();
    }

  for(it = TextFiles.begin(); it != TextFiles.end(); ++it)
    {
    // Ignore any invalid dependencies
    if(!it->second) continue;

    if(!first)
      {
      ofs << RECORD_DELIM;
      }
    first = false;
    ofs << std::hex << it->second->GetId()
        << UNIT_DELIM << TEXT_TYPE
        << UNIT_DELIM << it->first
        << UNIT_DELIM << it->second->GetRealPath();
    }
}

//----------------------------------------------------------------------------
void ddepsCacheManifest::ReadImpl(std::istream& ifs)
{
  std::string idStr, type, importName, path;
  size_t id = 0;
  bool foundAtLeastOne = false;
  while(ifs.good())
    {
    std::getline(ifs, idStr, UNIT_DELIM);
    std::getline(ifs, type, UNIT_DELIM);
    std::getline(ifs, importName, UNIT_DELIM);
    std::getline(ifs, path, RECORD_DELIM);

    // We may not have actually read anything
    if(path.length() > 0)
      {
      std::istringstream iss(idStr);
      iss >> std::hex >> id;

      if(type == TEXT_TYPE)
        {
        TextFiles[importName] = CreateCacheFile(path, id);
        }
      else if(type == MODULE_TYPE)
        {
        ModuleFiles[importName] = CreateCacheFile(path, id);
        }

      foundAtLeastOne = true;
      NextId = id > NextId ? id : NextId;
      }
    }

  // Don't try to re-use the highest used id
  if(foundAtLeastOne)
    NextId++;
}

//----------------------------------------------------------------------------
ddepsCacheFile* ddepsCacheManifest::GetModule(std::string const& importName)
{
  ddepsCacheFile*& module = ModuleFiles[importName];
  if(!module)
    {
    std::string path = FindModule(importName);
    if(path.length() > 0)
      {
      module = CreateCacheFile(path, NextId++);
      }
    }

  return module;
}

//----------------------------------------------------------------------------
ddepsCacheFile* ddepsCacheManifest::GetText(std::string const& importName)
{
  ddepsCacheFile*& text = TextFiles[importName];
  if(!text)
    {
    std::string path = FindFile(Options.TextImportPaths, importName);
    if(path.length() > 0)
      {
      text = CreateCacheFile(path, NextId++);
      }
    }

  return text;
}

//----------------------------------------------------------------------------
std::string ddepsCacheManifest::FindModule(std::string const& name)
{
  if(FoundModules.count(name) > 0)
    {
    return FoundModules[name];
    }

  // This is static to save on allocations
  static std::vector<std::string> suffices;
  if(suffices.empty())
    {
    suffices.push_back(".di");
    suffices.push_back(".d");
    suffices.push_back("/packages.d");
    }

  return FoundModules[name] = FindFile(Options.ModuleImportPaths,
                                       name,
                                       suffices);
}

//----------------------------------------------------------------------------
std::string ddepsCacheManifest::FindFile(
                                  std::vector<std::string> const& dirs,
                                  std::string const& name,
                                  std::vector<std::string> const& suffices)
{
  // Look in each directory in order
  for(std::vector<std::string>::const_iterator dir = dirs.begin();
      dir != dirs.end(); ++dir)
    {
    // Check each suffix in order
    for(std::vector<std::string>::const_iterator suf = suffices.begin();
        suf != suffices.end(); ++suf)
      {
      // Accept the first match we find
      std::string path = *dir;
      path += "/";
      path += name;
      path += *suf;
      if(cmSystemTools::FileExists(path.c_str()))
        {
        return path;
        }
      }
    }

  return "";
}

//----------------------------------------------------------------------------
std::string ddepsCacheManifest::FindFile(std::vector<std::string> const& dirs,
                                         std::string const& name)
{
  // Create a vector with an empty suffix to handle cases where there
  // are no suffices to check
  std::vector<std::string> noSuffices;
  noSuffices.push_back("");
  return FindFile(dirs, name, noSuffices);
}

//----------------------------------------------------------------------------
ddepsCacheFile* ddepsCacheManifest::CreateCacheFile(std::string const& path,
                                                    size_t id)
{
  std::ostringstream oss;
  oss << std::hex << id;
  return new ddepsCacheFile(ConfigDir + "/" + oss.str(),
                            path,
                            id,
                            Options);
}
