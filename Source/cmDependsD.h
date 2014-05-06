
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
#include "cmMakefile.h"
#include "cmLocalGenerator.h"

/** \class cmDependsD
 * \brief Dependency scanner for D object files.
 *
 * Calls D compiler to do the dirty work, as properly scanning
 * D dependencies would otherwise require a nearly complete compiler
 * be implemented inside CMake.
 */
class cmDependsD: public cmDepends
{
public:
  cmDependsD(cmLocalGenerator*);
  virtual ~cmDependsD();

protected:
  virtual bool WriteDependencies(const std::set<std::string>& sources,
                                 const std::string& obj,
                                 std::ostream& makeDepends,
                                 std::ostream& internalDepends);

  virtual bool Finalize(std::ostream& makeDepends,
                        std::ostream& internalDepends);

private:
  static void EscapeSpaces(std::string&);
  static void UnescapeParens(std::string&);
};

#endif
