/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsScope_h
#define ddepsScope_h

#include "cmStandardIncludes.h"

// Represents a "scope" for the parser.
// Does *not* accurately represent a scope:
//  There are circumstances in which a new Scope
//  is created when there is not actually a new scope.
//  This is done to make it easier to handle certain
//  constructs that would otherwise require a more
//  complicated parser.
class ddepsScope
{
private:
  // This is only accessible from ddepsModule
  friend class ddepsModule;
  ddepsScope(bool inTemplate=false, bool pub=false, bool reqs=true);
  int UnclaimedParenExprSeq;
  size_t MaxVersionLevel;
  size_t MaxDebugLevel;
  bool Template;
  bool EndlessScope;
  bool Public;
  bool RequirementsMet;
};

#endif
