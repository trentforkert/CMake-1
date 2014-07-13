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
cmDependsD::cmDependsD(cmLocalGenerator* lg): cmDepends(lg)
{
  this->SetIncludePathFromLanguage("D");
}

//----------------------------------------------------------------------------
cmDependsD::~cmDependsD()
{
}

//----------------------------------------------------------------------------
bool cmDependsD::WriteDependencies(const std::set<std::string>& sources,
                                   const std::string& obj,
                                   std::ostream& makeDepends,
                                   std::ostream&)
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

    std::vector<std::string> cmd;
    cmMakefile* mf = this->LocalGenerator->GetMakefile();
    if(!mf->IsDefinitionSet("CMAKE_D_DEPS_COMMAND"))
      {
      return false;
      }

    // Redirect stdout, stderr
    std::streambuf* cout_buf = std::cout.rdbuf(makeDepends.rdbuf());
    std::stringstream errors;
    std::streambuf* cerr_buf = std::cerr.rdbuf(errors.rdbuf());

    for(std::set<std::string>::iterator src = sources.begin();
        src != sources.end(); ++src)
      {
      std::string cmd_str = mf->GetDefinition("CMAKE_D_DEPS_COMMAND");
      cmSystemTools::ReplaceString(cmd_str, "<OBJECT>", obj.c_str());
      cmSystemTools::ReplaceString(cmd_str, "<SOURCE>", src->c_str());
      cmSystemTools::ExpandListArgument(cmd_str, cmd);

      if(!cmSystemTools::RunSingleCommand(cmd, 0, 0, 0,
                                cmSystemTools::OUTPUT_NORMAL))
        {
        // Restablish stdout, cerr
        std::cout.rdbuf(cout_buf);
        std::cerr.rdbuf(cerr_buf);
        cmSystemTools::Error(errors.str().c_str());
        return false;
        }
      }

  // Restablish stdout, cerr
  std::cout.rdbuf(cout_buf);
  std::cerr.rdbuf(cerr_buf);
  {
    std::string errstr = errors.str();
    if(errstr.length() > 0)
      {
      cmSystemTools::Message(errstr.c_str());
      }
  }
  return true;
}
