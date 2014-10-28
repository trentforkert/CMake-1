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

enum DDepsArgsMode
{
    MAKE = 0,
    NINJA = 1,
};

//----------------------------------------------------------------------------
void Usage()
{
  /* The actual usage is as follows:
   *    ddeps <mode> <arguments>
   * Where <mode> is one of "ninja" or "make"
   *    ddeps make <versions> <source> <object> <flags>
   *    ddeps ninja <versions> <source> <depfile> <compiler-passthrough>
   * <versions> is a semicolon separated list of built-in version conditions.
   * <object> is the name of the object file to be used in the output.
   * <flags> is a series of compiler flags for:
   *    Include directories
   *    Text include directories
   *    Version conditions
   *    Debug conditions
   *    Unittest
   *    Output file
   *  The flags corresponding to DMD, GDC or LDC will be selected based
   *  on which compiler's identifier is found in <versions>.
   * <depfile> is the dependency file to write to instead of stdout/stderr.
   * <compiler-passthrough> is the full compiler command line, which will be
   *    run after ddeps scans for imports.
   */
  std::cerr
    << "NOTE: This is intended for use internally by CMake,"
    << std::endl
    << "so the interface may be confusing to a human"
    << std::endl
    << "and is subject to change without notice."
    << std::endl
    << "If you are seeing this without having called it directly,"
    << std::endl
    << "please file a bug report at:"
    << std::endl
    << " https://github.com/trentforkert/cmake/issues"
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
  DDepsArgsMode mode;

  cmsys::Encoding::CommandLineArguments args =
            cmsys::Encoding::CommandLineArguments::Main(argc, argv);
  int ac = args.argc();
  char const* const* av = args.argv();
  bool unittest = false;

  if(ac < 2)
    {
    Usage();
    return 1;
    }

  int i = 1;
  if(strncmp(av[i], "make", 4) == 0)
    {
    if(ac < 5)
      {
      Usage();
      return 1;
      }
    mode = MAKE;
    }
  else if(strncmp(av[i], "ninja", 5) == 0)
    {
    if(ac < 7)
      {
      Usage();
      return 1;
      }
    mode = NINJA;
    }
  else
    {
    Usage();
    return 1;
    }

  ++i;

  if( mode == MAKE || mode == NINJA )
    {
    cmSystemTools::ExpandListArgument(av[i++], versionIdents);
    }

  if( mode == MAKE || mode == NINJA )
    {
    source = cmSystemTools::GetRealPath(av[i++]);
    }

  if( mode == MAKE )
    {
    obj = av[i++];
    }
  else if( mode == NINJA )
    {
    output = av[i++];
    }

  int startNonPosOpts = i - 1; // CommandLineArguments ignores argv[0]
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
      arg.AddArgument("-of", argT::EQUAL_ARGUMENT, &obj, "");
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
      arg.AddArgument("-o", argT::CONCAT_ARGUMENT, &obj, "");
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
    arg.AddArgument("-of", argT::CONCAT_ARGUMENT, &obj, "");
    }
  arg.StoreUnusedArguments(true);

  arg.Parse();

  if(unittest)
    {
    versionIdents.push_back("unittest");
    }

  // "all" should always be defined
  versionIdents.push_back("all");

  if(mode == NINJA)
    {
    // Prepare the command
    for(; i < ac; i++)
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

    ddepsCacheMeta Meta(cacheName,
                        base,
                        *Options);

    bool writeInternalDeps = (mode == MAKE);
    bool oneDepPerLine = (mode == MAKE);

    Meta.WriteDependencyInfo(source, obj, writeInternalDeps, oneDepPerLine);
    }

  // Run the compiler pass-through command if not empty
  if(!cmd.empty())
    {
    int retval;
    cmSystemTools::RunSingleCommand(cmd, 0, &retval, 0, cmSystemTools::OUTPUT_PASSTHROUGH);
    return retval;
    }


  return 0;
}

