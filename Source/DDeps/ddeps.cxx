/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "ddepsCacheMeta.h"
#include "ddepsOptions.h"
#include "cmStandardIncludes.h"
#include <cmsys/Encoding.hxx>
#include <cmsys/CommandLineArguments.hxx>
#include <cmSystemTools.h>

//----------------------------------------------------------------------------
void Usage()
{
  std::cerr
    << "NOTE: This is intended for use internally by CMake,"
    << std::endl
    << "so the interface may be confusing to a human"
    << std::endl
    << "and is subject to change without notice."
    << std::endl
    << "Usage: ddeps [-o <depfile>] <version list> <object> <source> [flags]"
    << std::endl
    << "             [-- <compiler-command>]"
    << std::endl
    << std::endl
    << "<version list> is a semicolon-separated list of version identifiers."
    << std::endl
    << "It is used to specify compiler-defined version identifiers, including"
    << std::endl
    << "the compiler vendor (DigitalMars, GNU, or LLVM), which determines the"
    << std::endl
    << "remaining flags supported."
    << std::endl
    << std::endl
    << "<compiler-command> can specify a command to build the object. No"
    << std::endl
    << "additional flags are passed by ddeps, but ddeps will parse"
    << std::endl
    << "the flags it understands (below) from <compiler-command>."
    << std::endl
    << std::endl
    << "Flags for DigitalMars"
    << std::endl
    << "  -I<include dir>    = Where to look for imports"
    << std::endl
    << "  -J<include dir>    = Where to look for text imports"
    << std::endl
    << "  -version=<ident>   = Parse version code identified by ident"
    << std::endl
    << "  -debug=<ident>     = Parse debug code identified by ident"
    << std::endl
    << "  -unittest          = Parse unittest code"
    << std::endl
    << std::endl
    << "Flags for GNU"
    << std::endl
    << "  -I<include dir>    = Where to look for imports"
    << std::endl
    << "  -J<include dir>    = Where to look for text imports"
    << std::endl
    << "  -fversion=<ident>  = Parse version code identified by ident"
    << std::endl
    << "  -fdebug=<ident>    = Parse debug code identified by ident"
    << std::endl
    << "  -funittest         = Parse unittest code"
    << std::endl
    << std::endl
    << "Flags for LLVM"
    << std::endl
    << "  -I=<include dir>   = Where to look for imports"
    << std::endl
    << "  -J=<include dir>   = Where to look for text imports"
    << std::endl
    << "  -d-version=<ident> = Parse version code identified by ident"
    << std::endl
    << "  -d-debug=<ident>   = Parse debug code identified by ident"
    << std::endl
    << "  -unittest          = Parse unittest code"
    << std::endl;
}

//----------------------------------------------------------------------------
int main(int argc, char const* const* argv)
{

  if( cmSystemTools::GetCurrentWorkingDirectory().size() == 0 )
    {
    std::cerr << "Current working directory cannot be established."
              << std::endl;
    return 1;
    }

  std::string output;
  std::string obj;
  std::string source;
  std::vector<std::string> includeDirs;
  std::vector<std::string> textIncludeDirs;
  std::vector<std::string> debugIdents;
  std::vector<std::string> versionIdents;
  std::vector<std::string> cmd;

  cmsys::Encoding::CommandLineArguments args =
            cmsys::Encoding::CommandLineArguments::Main(argc, argv);
  int ac = args.argc();
  char const* const* av = args.argv();
  bool endParams = false;
  bool unittest = false;

  if(ac < 4)
    {
    Usage();
    return 1;
    }

  int i = 1;
  if(av[i][0] == '-' && av[i][1] == 'o')
    {
    if(ac < 5)
      {
      Usage();
      return 1;
      }
    output = av[i+1];
    i+=2;
    }
  cmSystemTools::ExpandListArgument(av[i++], versionIdents);
  obj = av[i++];
  source = cmSystemTools::GetRealPath(av[i++]);

  int startNonPosOpts = i;

  for(; i < ac; i++)
    {
    if(strlen(av[i]) == 2
        && av[i][0] == '-'
        && av[i][1] == '-')
      {
      endParams = true;
      break;
      }
    }

  startNonPosOpts --; // CommandLineArguments ignores argv[0]
  cmsys::CommandLineArguments arg;
  arg.Initialize(ac - startNonPosOpts, &av[startNonPosOpts]);
  typedef cmsys::CommandLineArguments argT;

  bool isDMD = false;
  bool flagsSet = false;
  // Support flags that mimic the D compiler's flags
  // This is done primarily so that we can parse the compiler command
  // for flags, but is also used by Makefile generators
  // to specify, i.e., include directories.
  // TODO There should be a better way to do this
  for(std::vector<std::string>::iterator it = versionIdents.begin();
      it != versionIdents.end(); ++it)
    {
    if(*it == "LDC")
      {
      arg.AddArgument("-I", argT::EQUAL_ARGUMENT, &includeDirs, "");
      arg.AddArgument("-J", argT::EQUAL_ARGUMENT, &textIncludeDirs, "");
      arg.AddArgument("-d-version", argT::EQUAL_ARGUMENT, &versionIdents, "");
      arg.AddArgument("-d-debug", argT::EQUAL_ARGUMENT, &debugIdents, "");
      arg.AddArgument("-unittest", argT::NO_ARGUMENT, &unittest, "");
      flagsSet = true;
      break;
      }
    else if(*it == "GNU")
      {
      arg.AddArgument("-I", argT::CONCAT_ARGUMENT, &includeDirs, "");
      arg.AddArgument("-J", argT::CONCAT_ARGUMENT, &textIncludeDirs, "");
      arg.AddArgument("-fversion", argT::EQUAL_ARGUMENT, &versionIdents, "");
      arg.AddArgument("-fdebug", argT::EQUAL_ARGUMENT, &debugIdents, "");
      arg.AddArgument("-funittest", argT::NO_ARGUMENT, &unittest, "");
      flagsSet = true;
      break;
      }
    else if(*it == "DigitalMars")
      {
      isDMD = true;
      break;
      }
    }
  if(!flagsSet) // Assume DigitalMars or DigitalMars-compatible
    {
    if(!isDMD)
      {
      std::cerr << "Warning: DDeps doesn't recognize this D compiler."
                << std::endl
                << "Assuming a DigitalMars-compatible command line."
                << std::endl;
      }
    arg.AddArgument("-I", argT::CONCAT_ARGUMENT, &includeDirs, "");
    arg.AddArgument("-J", argT::CONCAT_ARGUMENT, &textIncludeDirs, "");
    arg.AddArgument("-version", argT::EQUAL_ARGUMENT, &versionIdents, "");
    arg.AddArgument("-debug", argT::EQUAL_ARGUMENT, &debugIdents, "");
    arg.AddArgument("-unittest", argT::NO_ARGUMENT, &unittest, "");
    }
  arg.StoreUnusedArguments(true);

  arg.Parse();

  if(unittest)
    {
    versionIdents.push_back("unittest");
    }

  // "all" should always be defined
  versionIdents.push_back("all");

  if(endParams)
    {
    // Prepare the command
    for(i++; i < ac; i++)
      {
      cmd.push_back(av[i]);
      }
    }

  // If a file is specified, write to it instead of stdout.
  // Ninja uses this.
  // The Makefile generator instead catches stdout and
  // does this redirect itself.
  if(!output.empty())
    {
    if(!freopen(output.c_str(), "wb", stdout))
      {
      cmSystemTools::Error("DDeps could not redirect stdout");
      return 1;
      }
    }

    {
    ddepsOptions* Options = new ddepsOptions(versionIdents,
                                             debugIdents,
                                             includeDirs,
                                             textIncludeDirs);

    std::string base = ".ddeps_cache";

    // Make sure the base directory exists
    cmSystemTools::MakeDirectory(base.c_str());

    std::string cacheName = base + "/manifest";
    std::string realName = "CMakeCache.txt";

    ddepsCacheMeta Meta(cacheName,
                        realName,
                        base,
                        *Options);

    Meta.WriteDependencyInfo(source, obj);
    }

  // Run the compiler pass-through command if not empty
  if(!cmd.empty())
    {
    cmSystemTools::RunSingleCommand(cmd);
    }


  return 0;
}

