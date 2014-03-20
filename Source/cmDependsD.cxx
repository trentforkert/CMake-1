/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2013-2014 Kitware, Inc.
  Copyright 2013-2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmDependsD.h"

#include "cmSystemTools.h"

//----------------------------------------------------------------------------
cmDependsD::cmDependsD()
{

}

//----------------------------------------------------------------------------
cmDependsD::~cmDependsD()
{

}

//----------------------------------------------------------------------------
bool cmDependsD::WriteDependencies(const std::set<std::string>& sources,
                                   const std::string& obj,
                                   std::ostream& makeDepends,
                                   std::ostream& internalDepends)
{
  // Make sure this is a scanning instance.
  if(sources.empty() || sources.begin()->empty())
    {
    cmSystemTools::Error("Cannot scan dependencies without a source file.");
    return false;
    }
  if(obj.empty())
    {
    cmSystemTools::Error("Cannot scan dependencies without an object file.");
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
bool cmDependsD::CheckDependencies(std::istream&, const char*,
                         std::map<std::string, DependencyVector >&)
{
  return true;
}
