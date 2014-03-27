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

  std::set<std::string> dependencies;
  cmMakefile* mf = this->LocalGenerator->GetMakefile();
  if(!mf->IsDefinitionSet("CMAKE_D_DEPS_COMMAND"))
    {
    return false;
    }
  std::vector<std::string> cmd;
  cmSystemTools::ExpandListArgument(
      mf->GetDefinition("CMAKE_D_DEPS_COMMAND"),
      cmd);

  cmd.insert(cmd.end(), sources.begin(), sources.end());

  std::string deps_listing;
  if(!cmSystemTools::RunSingleCommand(cmd,
        &deps_listing, 0, 0, cmSystemTools::OUTPUT_NONE))
    {
    return false;
    }

  // deps_listing format is:
  // depsImport module_name (filepath) : visibility : dep_module (filepath)
  // depsLib module_name (filepath) : lib
  // depsFile module_name (filepath) : shortFileName (filepath)
  // depsVersion module_name (filepath) : ident
  // depsDebug module_name (filepath) : ident
  //
  // We only deal with depsImport and depsFile varieties
  std::istringstream deps(deps_listing);

  std::string fromFile, toFile;
  std::size_t lparen, rparen;
  while(!deps.eof())
    {
    std::string line;
    std::getline(deps, line);
    lparen = line.find("(") + 1;
    rparen = line.find(")");
    while( line[rparen - 1] == '\\' )
      {
      rparen = line.find(")", rparen + 1);
      }

    if(lparen != std::string::npos && rparen != std::string::npos)
      {
      fromFile = line.substr(lparen, rparen-lparen);
      }
    else
      {
      continue;
      }

    lparen = line.rfind("(");
    while( line[lparen - 1] == '\\' )
      {
      lparen = line.rfind("(", lparen - 1);
      }
    lparen ++;
    rparen = line.rfind(")");
    if(lparen != std::string::npos && rparen != std::string::npos)
      {
      toFile = line.substr(lparen, rparen-lparen);
      }
    else
      {
      continue;
      }

    // Unescape parentheses
    UnescapeParens(fromFile);
    UnescapeParens(toFile);

    // Spaces are unescaped in sources, so wait to escape them
    // TODO: Should they be?
    if(sources.find(fromFile) != sources.end()
        && sources.find(toFile) == sources.end())
      {
      dependencies.insert(toFile);
      }
    }

  if(dependencies.size() > 0)
    {
    internalDepends << obj << "\n";
    for(std::set<std::string>::iterator it = sources.begin();
        it != sources.end(); it++)
      {
      std::string filename = *it;
      EscapeSpaces(filename);
      makeDepends << obj << ": " << filename << "\n";
      internalDepends << " " << filename << "\n";
      }
    for(std::set<std::string>::iterator it = dependencies.begin();
        it != dependencies.end(); it++)
      {
      std::string filename = *it;
      EscapeSpaces(filename);
      makeDepends << obj << ": " << filename << "\n";
      internalDepends << " " << filename << "\n";
      }

    makeDepends << "\n";
    internalDepends << "\n";
    }

  return true;
}

void cmDependsD::EscapeSpaces(std::string& str)
{
  for(std::size_t i = str.find(" ");
      i != std::string::npos;
      i = str.find(" ", i+1))
    {
    if(str[i-1] != '\\')
      {
      str.replace(i, 1, "\\ ");
      i++;
      }
    }
}

void cmDependsD::UnescapeParens(std::string& str)
{
  std::size_t i;
  for(  i = str.find("\\(");
        i != std::string::npos;
        i = str.find("\\("))
    {
    str.replace(i, 2, "(");
    }
  for(  i = str.find("\\)");
        i != std::string::npos;
        i = str.find("\\)"))
    {
    str.replace(i, 2, ")");
    }
}
