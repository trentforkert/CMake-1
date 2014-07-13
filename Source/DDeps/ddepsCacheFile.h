/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsCacheFile_h
#define ddepsCacheFile_h
#include "ddepsCache.h"

class ddepsOptions;
class ddepsImport;

// Represents a cache entry corresponding to a source file.
// This caches the parsed dependency info for a file by storing
// The dependency type (i.e., public) and the import name (i.e., std.stdio)
// Located at ".ddeps_cache/{manifest-id}/{dep-id}"
class ddepsCacheFile: public ddepsCache
{
public:
  // Constructor.
  // Passes its arguments to Cache's constructor.
  // Does *not* use Cache's lock-file, assuming that the needed locks will
  // have been established before this is created.
  // Does *not* read the cache implicitly
  ddepsCacheFile(std::string const& cacheFileName,
                 std::string const& realFileName,
                 size_t id,
                 ddepsOptions& opts);

  // Destructor.
  // Writes the Cache (if needed)
  virtual ~ddepsCacheFile();

  // Generate object dependency information.
  // Will load the Cache and/or parse the source as needed.
  // Recurses public and template imports.
  // Optionally recurses private imports.
  void GetObjDependencies(std::deque<std::string>& mod_deque,
                          std::set<std::string>& mod_names,
                          std::set<std::string>& text_names,
                          bool recursePrivateImports);

  // Read the cache or parse the source as needed
  // Returns true if loaded, false otherwise
  bool ReadOrParse();

  // Get the numeric id of this cache file
  inline size_t GetId() const { return Id; }

  // Return the name the module is imported with
  // This will be an empty string until the file is parsed
  inline std::string GetModuleName() const { return ModuleName; }

protected:
  // Required by ddepsCache
  virtual void WriteImpl(std::ostream& ofs) const;
  virtual void ReadImpl(std::istream& ifs);

  // Define the dependency types
  static const std::string TEXT_TYPE;
  static const std::string TEMPLATE_TYPE;
  static const std::string PUBLIC_TYPE;
  static const std::string PRIVATE_TYPE;

private:
  // Runs the parser on this CacheFile's source file
  void ParseSource();

  size_t const Id;
  std::string ModuleName;
  std::vector<ddepsImport> Imports;
  ddepsOptions& Options;
};
#endif
