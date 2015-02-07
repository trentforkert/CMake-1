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
               std::vector<std::string> const& textIncludes,
               bool debug)
      : MaxVersionLevel(0), MaxDebugLevel(0), DebugFlag(debug)
  {
    // Transfer version identifiers to a set to avoid repeats
    // Order doesn't matter for version identifiers.
    std::vector<std::string>::const_iterator it;
    for(it = versions.begin(); it != versions.end(); ++it)
      {
      if('0' <= (*it)[0] && (*it)[0] <= '9')
        {
        int level = atoi(it->c_str());
        if( level > MaxVersionLevel )
          {
          MaxVersionLevel = level;
          }
        }
      else
        {
        VersionIdents.insert(*it);
        }
      }

    // Ditto for debug identifiers
    for(it = debugs.begin(); it != debugs.end(); ++it)
      {
      if('0' <= (*it)[0] && (*it)[0] <= '9')
        {
        int level = atoi(it->c_str());
        if( level > MaxDebugLevel )
          {
          MaxDebugLevel = level;
          }
        }
      else
        {
        DebugIdents.insert(*it);
        }
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
            &&  TextImportPaths == rhs.TextImportPaths
            &&  MaxVersionLevel == rhs.MaxDebugLevel
            &&  MaxDebugLevel == rhs.MaxDebugLevel
            &&  DebugFlag == rhs.DebugFlag);
  }

  std::set<std::string> VersionIdents;
  std::set<std::string> DebugIdents;
  std::vector<std::string> ModuleImportPaths;
  std::vector<std::string> TextImportPaths;
  int MaxVersionLevel;
  int MaxDebugLevel;
  bool DebugFlag;
};

#endif
