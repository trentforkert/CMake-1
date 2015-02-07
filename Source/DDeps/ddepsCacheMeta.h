/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsCacheMeta_h
#define ddepsCacheMeta_h
#include "ddepsCache.h"

class ddepsOptions;
// Represent a meta-manifest. That is, a manifest of what
// manifests there are. Records version identifiers, debug identifiers,
// import paths, and text import paths so that if these change,
// a different manifest and cache will be used. The tracked items
// are everything (other than compiler version) that can influence
// D's code generation. Manifest ids are determined implicitly
// based on the order the entries appear in the file.
// Location: ".ddeps_cache/manifest"
class ddepsCacheMeta: public ddepsCache
{
public:
  // Constructor.
  ddepsCacheMeta(std::string const& cachePath,
                 std::string const& dir,
                 ddepsOptions& options);

  // Destructor.
  virtual ~ddepsCacheMeta();

  // Write object dependency information for src
  void WriteDependencyInfo(std::string const& src,
                           std::string const& obj,
                           bool writeInternalDeps=true,
                           bool oneDepPerLine=true);

protected:
  // Required by ddepsCache
  virtual void WriteImpl(std::ostream& out) const;
  virtual void ReadImpl(std::istream& in);
  virtual void OnOutdatedCache();

  // Define ident types
  static const std::string VERSION_TYPE;
  static const std::string DEBUG_TYPE;
  static const std::string MOD_IMPORT_TYPE;
  static const std::string TEXT_IMPORT_TYPE;
  static const std::string VERSION_LEVEL_TYPE;
  static const std::string DEBUG_LEVEL_TYPE;
  static const std::string DEBUG_FLAG_TYPE;

private:
  // Determines and returns the path to the cache directory that
  // corresponds to the parser's configurations, creating it if needed.
  std::string GetCacheDir();

  std::vector<ddepsOptions*> AllOptions;
  std::string MetaCacheDir;
  ddepsOptions& Options;
};
#endif
