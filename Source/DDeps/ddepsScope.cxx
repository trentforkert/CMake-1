/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "ddepsScope.h"

//----------------------------------------------------------------------------
ddepsScope::ddepsScope(bool inTemplate, bool pub, bool reqs)
  : UnclaimedParenExprSeq(-1),
    MaxVersionLevel(0),
    MaxDebugLevel(0),
    Template(inTemplate),
    EndlessScope(false),
    Public(pub),
    RequirementsMet(reqs)
{
}

