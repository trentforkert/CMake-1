/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsOptions_h
#define ddepsOptions_h
#include "cmStandardIncludes.h"

// Container for the various compiler parameters we need
// Cached by ddepsCacheMeta, and used by ddepsModule
class ddepsOptions
{
public:
  ddepsOptions(){}
  ddepsOptions(std::vector<std::string> const& versions,
               std::vector<std::string> const& debugs,
               std::vector<std::string> const& includes,
               std::vector<std::string> const& textIncludes)
  {
    // Transfer version identifiers to a set to avoid repeats
    // Order doesn't matter for version identifiers.
    std::vector<std::string>::const_iterator it;
    for(it = versions.begin(); it != versions.end(); ++it)
      {
      VersionIdents.insert(*it);
      }

    // Ditto for debug identifiers
    for(it = debugs.begin(); it != debugs.end(); ++it)
      {
      DebugIdents.insert(*it);
      }

    // Order does matter for (text) include directories
    ModuleImportPaths = includes;
    TextImportPaths = textIncludes;
  }

  inline bool operator==(const ddepsOptions& rhs)
  {
    return (    VersionIdents == rhs.VersionIdents
            &&  DebugIdents == rhs.DebugIdents
            &&  ModuleImportPaths == rhs.ModuleImportPaths
            &&  TextImportPaths == rhs.TextImportPaths);
  }

  std::set<std::string> VersionIdents;
  std::set<std::string> DebugIdents;
  std::vector<std::string> ModuleImportPaths;
  std::vector<std::string> TextImportPaths;
};

#endif
