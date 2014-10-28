/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsCacheManifest_h
#define ddepsCacheManifest_h
#include "ddepsCache.h"

class ddepsCacheFile;
class ddepsOptions;

// Represents a manifest recording what files have been parsed and their
// results cached. This caches the CacheFile Id, type (module or text),
// import name, and the full path to the file.
// Located at ".ddeps_cache/{manifest-id}/manifest"
class ddepsCacheManifest: public ddepsCache
{
public:
  // Constructor.
  // Read the manifest
  // The real name specified to Cache's constructor is "CMakeCache.txt",
  // so that the DDeps cache can be recreated after CMake reconfigures.
  ddepsCacheManifest(std::string const& cfn,
                     std::string const& rfn,
                     std::string const& dir,
                     ddepsOptions& opts);

  // Destructor.
  // Writes the manifest
  // Destroys the CacheFiles that were known to this CacheManifest.
  virtual ~ddepsCacheManifest();

  // Write the object dependency of obj, based on the source src
  void WriteDependencyInfo(std::string const& src,
                           std::string const& obj,
                           bool writeInternalDeps=true);
protected:
  virtual void WriteImpl(std::ostream& ofs) const;
  virtual void ReadImpl(std::istream& ifs);

  static const std::string MODULE_TYPE;
  static const std::string TEXT_TYPE;

private:
  // Get the module CacheFile corresponding to the given import name
  // Will create a new CacheFile and add it to the manifest if needed.
  ddepsCacheFile* GetModule(std::string const& importName);

  // Get the text CacheFile corresponding to the given import name
  // Will create a new CacheFile and add it to the manifest if needed.
  ddepsCacheFile* GetText(std::string const& importName);


  // Finds path of the module by the specified name
  std::string FindModule(std::string const& name);

  // Finds the file specified by name in dirs, trying
  // the name with each suffix
  std::string FindFile(std::vector<std::string> const& dirs,
                           std::string const& name,
                           std::vector<std::string> const& suffices);

  // Finds the file specified by name in dirs, with no suffix
  std::string FindFile(std::vector<std::string> const& dirs,
                           std::string const& name);

  // Convenience method to create an instance of ddepsCacheFile
  ddepsCacheFile* CreateCacheFile(std::string const& path, size_t id);

private:
  std::string ConfigDir;
  ddepsOptions& Options;
  std::map<std::string, ddepsCacheFile*> ModuleFiles;
  std::map<std::string, ddepsCacheFile*> TextFiles;
  std::map<std::string, std::string> FoundModules;
  size_t NextId;
};
#endif
