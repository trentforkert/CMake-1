/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "ddepsCacheMeta.h"
#include "ddepsCacheManifest.h"
#include "ddepsOptions.h"
#include <cmSystemTools.h>

const std::string ddepsCacheMeta::VERSION_TYPE = "version";
const std::string ddepsCacheMeta::DEBUG_TYPE = "debug";
const std::string ddepsCacheMeta::MOD_IMPORT_TYPE = "module_import_path";
const std::string ddepsCacheMeta::TEXT_IMPORT_TYPE = "text_import_path";

//----------------------------------------------------------------------------
ddepsCacheMeta::ddepsCacheMeta(std::string const& cachePath,
                               std::string const& realPath,
                               std::string const& dir,
                               ddepsOptions& options):
  ddepsCache(cachePath, realPath, cachePath + ".lock"),
  MetaCacheDir(dir),
  Options(options)
{
  Read();
}

//----------------------------------------------------------------------------
ddepsCacheMeta::~ddepsCacheMeta()
{
  Write();

  for(std::vector<ddepsOptions*>::iterator it = AllOptions.begin();
      it != AllOptions.end(); ++it)
    {
    delete *it;
    }
}

//----------------------------------------------------------------------------
void ddepsCacheMeta::WriteDependencyInfo(std::string const& src,
                                         std::string const& obj)
{
  std::string base = GetCacheDir();
  std::string cachePath = base + "/manifest";
  std::string realPath = "CMakeCache.txt";

  ddepsCacheManifest manifest(cachePath, realPath, base, Options);
  manifest.WriteDependencyInfo(src, obj);
}

//----------------------------------------------------------------------------
void ddepsCacheMeta::WriteImpl(std::ostream& out) const
{
  for(std::vector<ddepsOptions*>::const_iterator it = AllOptions.begin();
      it != AllOptions.end(); ++it)
    {
    if( it != AllOptions.begin() )
      {
      out << GROUP_DELIM;
      }
    bool firstInGroup = true;

    // Write Version identifiers
    std::set<std::string>::const_iterator ident;
    for(ident = (*it)->VersionIdents.begin();
        ident != (*it)->VersionIdents.end(); ++ident)
      {
      if( !firstInGroup )
        {
        out << RECORD_DELIM;
        }
      out << VERSION_TYPE << UNIT_DELIM << *ident;
      firstInGroup = false;
      }

    // Write debug identifiers
    for(ident  = (*it)->DebugIdents.begin();
        ident != (*it)->DebugIdents.end(); ++ident)
      {
      if( !firstInGroup )
        {
        out << RECORD_DELIM;
        }
      out << DEBUG_TYPE << UNIT_DELIM << *ident;
      firstInGroup = false;
      }

    // Write module import paths
    std::vector<std::string>::const_iterator dir;
    for(dir  = (*it)->ModuleImportPaths.begin();
        dir != (*it)->ModuleImportPaths.end(); ++dir)
      {
      if( !firstInGroup )
        {
        out << RECORD_DELIM;
        }
      out << MOD_IMPORT_TYPE << UNIT_DELIM << *dir;
      firstInGroup = false;
      }

    // Write text import paths
    for(dir  = (*it)->TextImportPaths.begin();
        dir != (*it)->TextImportPaths.end(); ++dir)
      {
      if( !firstInGroup )
        {
        out << RECORD_DELIM;
        }
      out << TEXT_IMPORT_TYPE << UNIT_DELIM << *dir;
      firstInGroup = false;
      }
    }
}

//----------------------------------------------------------------------------
void ddepsCacheMeta::ReadImpl(std::istream& in)
{
  std::string type, ident;
  char x;
  while(in.good())
    {
    x = '\0';
    ddepsOptions* options = new ddepsOptions;
    while(in.good() && x != GROUP_DELIM)
      {
      std::getline(in, type, UNIT_DELIM);

      for(;;)
        {
        x = in.get();
        if( in.good() && (x < FILE_DELIM || UNIT_DELIM < x ))
          {
          ident += x;
          }
        else
          {
          break;
          }
        }

      if(ident == "")
        {
        break;
        }

      // We emit them in order in WriteImpl, but can't assume that will
      // always be the case.
      if(type == VERSION_TYPE)
        {
        options->VersionIdents.insert(ident);
        }
      else if(type == DEBUG_TYPE)
        {
        options->DebugIdents.insert(ident);
        }
      else if(type == MOD_IMPORT_TYPE)
        {
        options->ModuleImportPaths.push_back(ident);
        }
      else if(type == TEXT_IMPORT_TYPE)
        {
        options->TextImportPaths.push_back(ident);
        }
      ident.clear();
      }

    AllOptions.push_back(options);
    }
}

//----------------------------------------------------------------------------
std::string ddepsCacheMeta::GetCacheDir()
{
  size_t id = 0;
  std::vector<ddepsOptions*>::iterator it;
  for(it = AllOptions.begin(); it != AllOptions.end(); ++it, ++id)
    {
    // If matches parser config, take it
    if(**it == Options)
      {
      break;
      }
    }

  // Add our new Options if needed
  if(id == AllOptions.size())
    {
    SetModified();
    AllOptions.push_back(&Options);
    }
  else
    {
    // Replace the copy in AllOptions
    ddepsOptions* temp = *it;
    *it = &Options;
    delete temp;
    }

  std::ostringstream oss;
  oss << std::hex << id;
  std::string res = MetaCacheDir + "/" + oss.str();

  // Ensure the directory actually exists
  cmSystemTools::MakeDirectory(res.c_str());

  return res;
}


