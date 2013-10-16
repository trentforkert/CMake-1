/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
// include these first, otherwise there will be problems on Windows
// with GetCurrentDirectory() being redefined
#ifdef CMAKE_BUILD_WITH_CMAKE
#include "cmDynamicLoader.h"
#include "cmDocumentation.h"
#endif

#include "cmake.h"
#include "cmcmd.h"
#include "cmCacheManager.h"
#include "cmListFileCache.h"
#include "cmakewizard.h"
#include "cmSourceFile.h"
#include "cmGlobalGenerator.h"
#include "cmLocalGenerator.h"
#include "cmMakefile.h"

#ifdef CMAKE_BUILD_WITH_CMAKE
//----------------------------------------------------------------------------
static const char * cmDocumentationName[][2] =
{
  {0,
   "  cmake - Cross-Platform Makefile Generator."},
  {0,0}
};

//----------------------------------------------------------------------------
static const char * cmDocumentationUsage[][2] =
{
  {0,
   "  cmake [options] <path-to-source>\n"
   "  cmake [options] <path-to-existing-build>"},
  {0,0}
};

#define CMAKE_BUILD_OPTIONS                                             \
  "  <dir>          = Project binary directory to be built.\n"          \
  "  --target <tgt> = Build <tgt> instead of default targets.\n"        \
  "  --config <cfg> = For multi-configuration tools, choose <cfg>.\n"   \
  "  --clean-first  = Build target 'clean' first, then build.\n"        \
  "                   (To clean only, use --target 'clean'.)\n"         \
  "  --use-stderr   = Don't merge stdout/stderr output and pass the\n"  \
  "                   original stdout/stderr handles to the native\n"   \
  "                   tool so it can use the capabilities of the\n"     \
  "                   calling terminal (e.g. colored output).\n"        \
  "  --             = Pass remaining options to the native tool.\n"

//----------------------------------------------------------------------------
static const char * cmDocumentationOptions[][2] =
{
  CMAKE_STANDARD_OPTIONS_TABLE,
  {"-E", "CMake command mode."},
  {"-i", "Run in wizard mode."},
  {"-L[A][H]", "List non-advanced cached variables."},
  {"--build <dir>", "Build a CMake-generated project binary tree."},
  {"-N", "View mode only."},
  {"-P <file>", "Process script mode."},
  {"--find-package", "Run in pkg-config like mode."},
  {"--graphviz=[file]", "Generate graphviz of dependencies, see "
   "CMakeGraphVizOptions.cmake for more."},
  {"--system-information [file]", "Dump information about this system."},
  {"--debug-trycompile", "Do not delete the try_compile build tree. Only "
   "useful on one try_compile at a time."},
  {"--debug-output", "Put cmake in a debug mode."},
  {"--trace", "Put cmake in trace mode."},
  {"--warn-uninitialized", "Warn about uninitialized values."},
  {"--warn-unused-vars", "Warn about unused variables."},
  {"--no-warn-unused-cli", "Don't warn about command line options."},
  {"--check-system-vars", "Find problems with variable usage in system "
   "files."},
  {0,0}
};

#endif

int do_cmake(int ac, char** av);
static int do_build(int ac, char** av);

static cmMakefile* cmakemainGetMakefile(void *clientdata)
{
  cmake* cm = (cmake *)clientdata;
  if(cm && cm->GetDebugOutput())
    {
    cmGlobalGenerator* gg=cm->GetGlobalGenerator();
    if (gg)
      {
      cmLocalGenerator* lg=gg->GetCurrentLocalGenerator();
      if (lg)
        {
        cmMakefile* mf = lg->GetMakefile();
        return mf;
        }
      }
    }
  return 0;
}

static std::string cmakemainGetStack(void *clientdata)
{
  std::string msg;
  cmMakefile* mf=cmakemainGetMakefile(clientdata);
  if (mf)
    {
    msg = mf->GetListFileStack();
    if (!msg.empty())
      {
      msg = "\n   Called from: " + msg;
      }
    }

  return msg;
}

static void cmakemainErrorCallback(const char* m, const char*, bool&,
                                   void *clientdata)
{
  std::cerr << m << cmakemainGetStack(clientdata) << std::endl << std::flush;
}

static void cmakemainProgressCallback(const char *m, float prog,
                                      void* clientdata)
{
  cmMakefile* mf = cmakemainGetMakefile(clientdata);
  std::string dir;
  if ((mf) && (strstr(m, "Configuring")==m) && (prog<0))
    {
    dir = " ";
    dir += mf->GetCurrentDirectory();
    }
  else if ((mf) && (strstr(m, "Generating")==m))
    {
    dir = " ";
    dir += mf->GetCurrentOutputDirectory();
    }

  if ((prog < 0) || (!dir.empty()))
    {
    std::cout << "-- " << m << dir << cmakemainGetStack(clientdata)<<std::endl;
    }

  std::cout.flush();
}


int main(int ac, char** av)
{
  cmSystemTools::EnableMSVCDebugHook();
  cmSystemTools::FindExecutableDirectory(av[0]);
  if(ac > 1 && strcmp(av[1], "--build") == 0)
    {
    return do_build(ac, av);
    }
  int ret = do_cmake(ac, av);
#ifdef CMAKE_BUILD_WITH_CMAKE
  cmDynamicLoader::FlushCache();
#endif
  return ret;
}

int do_cmake(int ac, char** av)
{
  if ( cmSystemTools::GetCurrentWorkingDirectory().size() == 0 )
    {
    std::cerr << "Current working directory cannot be established."
              << std::endl;
    return 1;
    }

#ifdef CMAKE_BUILD_WITH_CMAKE
  cmDocumentation doc;
  doc.addCMakeStandardDocSections();
  if(doc.CheckOptions(ac, av, "-E"))
    {
    // Construct and print requested documentation.
    cmake hcm;
    hcm.AddCMakePaths();
    doc.SetCMakeRoot(hcm.GetCacheDefinition("CMAKE_ROOT"));

    // the command line args are processed here so that you can do
    // -DCMAKE_MODULE_PATH=/some/path and have this value accessible here
    std::vector<std::string> args;
    for(int i =0; i < ac; ++i)
      {
      args.push_back(av[i]);
      }
    hcm.SetCacheArgs(args);

    std::vector<cmDocumentationEntry> generators;

    hcm.GetGeneratorDocumentation(generators);

    doc.SetName("cmake");
    doc.SetSection("Name",cmDocumentationName);
    doc.SetSection("Usage",cmDocumentationUsage);
    doc.AppendSection("Generators",generators);
    doc.PrependSection("Options",cmDocumentationOptions);

    return doc.PrintRequestedDocumentation(std::cout)? 0:1;
    }
#else
  if ( ac == 1 )
    {
    std::cout <<
      "Bootstrap CMake should not be used outside CMake build process."
              << std::endl;
    return 0;
    }
#endif

  bool wiz = false;
  bool sysinfo = false;
  bool command = false;
  bool list_cached = false;
  bool list_all_cached = false;
  bool list_help = false;
  bool view_only = false;
  cmake::WorkingMode workingMode = cmake::NORMAL_MODE;
  std::vector<std::string> args;
  for(int i =0; i < ac; ++i)
    {
    if(!command && strcmp(av[i], "-i") == 0)
      {
      wiz = true;
      }
    else if(!command && strcmp(av[i], "--system-information") == 0)
      {
      sysinfo = true;
      }
    // if command has already been set, then
    // do not eat the -E
    else if (!command && strcmp(av[i], "-E") == 0)
      {
      command = true;
      }
    else if (!command && strcmp(av[i], "-N") == 0)
      {
      view_only = true;
      }
    else if (!command && strcmp(av[i], "-L") == 0)
      {
      list_cached = true;
      }
    else if (!command && strcmp(av[i], "-LA") == 0)
      {
      list_all_cached = true;
      }
    else if (!command && strcmp(av[i], "-LH") == 0)
      {
      list_cached = true;
      list_help = true;
      }
    else if (!command && strcmp(av[i], "-LAH") == 0)
      {
      list_all_cached = true;
      list_help = true;
      }
    else if (!command && strncmp(av[i], "-P", strlen("-P")) == 0)
      {
      if ( i == ac -1 )
        {
        cmSystemTools::Error("No script specified for argument -P");
        }
      else
        {
        workingMode = cmake::SCRIPT_MODE;
        args.push_back(av[i]);
        i++;
        args.push_back(av[i]);
        }
      }
    else if (!command && strncmp(av[i], "--find-package",
                                 strlen("--find-package")) == 0)
      {
      workingMode = cmake::FIND_PACKAGE_MODE;
      args.push_back(av[i]);
      }
    else
      {
      args.push_back(av[i]);
      }
    }
  if(command)
    {
    int ret = cmcmd::ExecuteCMakeCommand(args);
    return ret;
    }
  if (wiz)
    {
    cmakewizard wizard;
    return wizard.RunWizard(args);
    }
  if (sysinfo)
    {
    cmake cm;
    int ret = cm.GetSystemInformation(args);
    return ret;
    }
  cmake cm;
  cmSystemTools::SetErrorCallback(cmakemainErrorCallback, (void *)&cm);
  cm.SetProgressCallback(cmakemainProgressCallback, (void *)&cm);
  cm.SetWorkingMode(workingMode);

  int res = cm.Run(args, view_only);
  if ( list_cached || list_all_cached )
    {
    cmCacheManager::CacheIterator it =
      cm.GetCacheManager()->GetCacheIterator();
    std::cout << "-- Cache values" << std::endl;
    for ( it.Begin(); !it.IsAtEnd(); it.Next() )
      {
      cmCacheManager::CacheEntryType t = it.GetType();
      if ( t != cmCacheManager::INTERNAL && t != cmCacheManager::STATIC &&
        t != cmCacheManager::UNINITIALIZED )
        {
        bool advanced = it.PropertyExists("ADVANCED");
        if ( list_all_cached || !advanced)
          {
          if ( list_help )
            {
            std::cout << "// " << it.GetProperty("HELPSTRING") << std::endl;
            }
          std::cout << it.GetName() << ":" <<
            cmCacheManager::TypeToString(it.GetType())
            << "=" << it.GetValue() << std::endl;
          if ( list_help )
            {
            std::cout << std::endl;
            }
          }
        }
      }
    }

  // Always return a non-negative value.  Windows tools do not always
  // interpret negative return values as errors.
  if(res != 0)
    {
    return 1;
    }
  else
    {
    return 0;
    }
}

//----------------------------------------------------------------------------
static int do_build(int ac, char** av)
{
#ifndef CMAKE_BUILD_WITH_CMAKE
  std::cerr << "This cmake does not support --build\n";
  return -1;
#else
  std::string target;
  std::string config = "Debug";
  std::string dir;
  std::vector<std::string> nativeOptions;
  bool clean = false;
  cmSystemTools::OutputOption outputflag = cmSystemTools::OUTPUT_MERGE;

  enum Doing { DoingNone, DoingDir, DoingTarget, DoingConfig, DoingNative};
  Doing doing = DoingDir;
  for(int i=2; i < ac; ++i)
    {
    if(doing == DoingNative)
      {
      nativeOptions.push_back(av[i]);
      }
    else if(strcmp(av[i], "--target") == 0)
      {
      doing = DoingTarget;
      }
    else if(strcmp(av[i], "--config") == 0)
      {
      doing = DoingConfig;
      }
    else if(strcmp(av[i], "--clean-first") == 0)
      {
      clean = true;
      doing = DoingNone;
      }
    else if(strcmp(av[i], "--use-stderr") == 0)
      {
      outputflag = cmSystemTools::OUTPUT_PASSTHROUGH;
      }
    else if(strcmp(av[i], "--") == 0)
      {
      doing = DoingNative;
      }
    else
      {
      switch (doing)
        {
        case DoingDir:
          dir = av[i];
          doing = DoingNone;
          break;
        case DoingTarget:
          target = av[i];
          doing = DoingNone;
          break;
        case DoingConfig:
          config = av[i];
          doing = DoingNone;
          break;
        default:
          std::cerr << "Unknown argument " << av[i] << std::endl;
          dir = "";
          break;
        }
      }
    }
  if(dir.empty())
    {
    std::cerr <<
      "Usage: cmake --build <dir> [options] [-- [native-options]]\n"
      "Options:\n"
      CMAKE_BUILD_OPTIONS
      ;
    return 1;
    }

  // Hack for vs6 that passes ".\Debug" as "$(IntDir)" value:
  //
  if (cmSystemTools::StringStartsWith(config.c_str(), ".\\"))
    {
    config = config.substr(2);
    }

  cmake cm;
  return cm.Build(dir, target, config, nativeOptions, clean, outputflag);
#endif
}
