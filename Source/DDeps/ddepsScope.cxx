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
ddepsScope::ddepsScope(ddepsScope const& parent)
  : UnclaimedParenExprSeq(-1),
    MaxVersionLevel(parent.MaxVersionLevel),
    MaxDebugLevel(parent.MaxDebugLevel),
    Template(parent.Template),
    EndlessScope(false),
    Public(parent.Public),
    RequirementsMet(parent.RequirementsMet),
    DebugFlag(parent.DebugFlag)
{
}

//----------------------------------------------------------------------------
ddepsScope::ddepsScope(ddepsOptions const& options)
  : UnclaimedParenExprSeq(-1),
    MaxVersionLevel(options.MaxVersionLevel),
    MaxDebugLevel(options.MaxDebugLevel),
    Template(false),
    EndlessScope(false),
    Public(false),
    RequirementsMet(true),
    DebugFlag(options.DebugFlag)
{
}
