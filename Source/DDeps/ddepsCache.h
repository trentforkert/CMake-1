/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsCache_h
#define ddepsCache_h
#include "cmStandardIncludes.h"

// Base class of the Cache* classes, which implement
// ASCII Delimited Text. DT is similar to CSV or TSV, except
// that it uses ASCII characters which are reserved as
// delimiters and thus DT doesn't need to escaping its
// content (assuming the content never includes the
// reserved characters).
// The following characters are used as separators:
// \x1C: "File Separator"
// \x1D: "Group Separator"
// \x1E: "Record Separator"
// \x1F: "Unit Separator"
// Cache and its subclasses treat units, records, groups and files
// as cells, rows, tables, and databases respectively. However,
// the actual data expected and handled will differ in each
// of Cache's subclasses, which handle different cached information,
// and are each responsible for the implementation details.
class ddepsCache
{
public:
  // Constructor.
  // If lockPath is specified, will block until
  // it can create a directory by the specified name
  // See rationale.md for more information
  ddepsCache(std::string const& cachePath,
        std::string const& realPath,
        std::string const& lockPath="");

  // Destructor.
  // Deletes the directory the Ctor created, if any
  virtual ~ddepsCache();

  // Returns the path to file being Cached
  inline std::string GetRealPath() const { return RealPath; }

  // Return whether or not the Cache is loaded
  inline bool IsLoaded() const { return Loaded; }

protected:
  // If the real file is older than the cache file, reads the cache
  // Otherwise, return
  void Read();

  // If cache data has changed, write the cache
  // Otherwise, return
  void Write() const;

  // Setters for the subclasses to use
  inline void SetLoaded(bool s=true) { Loaded = s; }
  inline void SetModified(bool s=true) { Modified = s; }

  // Require implementation of cache file write
  virtual void WriteImpl(std::ostream& out) const =0;

  // Require implementation of cache file read
  virtual void ReadImpl(std::istream& in) =0;

  // Called when a cache is older than the cached file
  virtual void OnOutdatedCache() =0;

  // Define the delimiters
  static const char UNIT_DELIM='\x1F';
  static const char RECORD_DELIM='\x1E';
  static const char GROUP_DELIM='\x1D';
  static const char FILE_DELIM='\x1C';
private:
  bool Loaded;
  bool Modified;
  std::string const RealPath;
  std::string const CachePath;
  std::string const LockPath;
};
#endif
