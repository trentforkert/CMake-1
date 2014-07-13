/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsImport_h
#define ddepsImport_h

// Represents an actual import, be it to a module or text file
class ddepsImport
{
public:
  ddepsImport(std::string const& impstring,
              bool text,
              bool templated,
              bool pub)
      : ImportString(impstring),
        Text(text),
        Templated(templated),
        Public(pub)
  {
  }

  std::string ImportString;
  bool Text;
  bool Templated;
  bool Public;
};

#endif
