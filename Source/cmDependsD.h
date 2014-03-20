
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
#ifndef cmDependsD_h
#define cmDependsD_h

#include "cmDepends.h"

/** \class cmDependsD
 * \brief Dependency scanner for D object files.
 *
 * Purposefully not implemented, as anything we could do here
 * short of compiling the D code wouldn't be useful.
 */
class cmDependsD: public cmDepends
{
public:
  cmDependsD();
  virtual ~cmDependsD();

protected:
  virtual bool WriteDependencies(const std::set<std::string>& sources,
                                 const std::string& obj,
                                 std::ostream& makeDepends,
                                 std::ostream& internalDepends);
  virtual bool CheckDependencies(std::istream&, const char*,
                                 std::map<std::string, DependencyVector>&);
};

#endif
