/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "ddepsCache.h"
#include <cmSystemTools.h>
#include <cmsys/FStream.hxx>

// Lifted from kwsys/SystemTools.cxx
// We need the unfiltered call for the file-based lock to work
// See rationale.md for more information
#if defined(_WIN32) && (defined(_MSC_VER) || defined(__WATCOMC__) \
    || defined(__BORLANDC__) || defined(__MINGW32__))
#include <wctype.h>
inline int Mkdir(const char* dir)
{
  return _wmkdir(cmsys::Encoding::ToWide(dir).c_str());
}
inline int Rmdir(const char* dir)
{
  return _wrmdir(cmsys::Encoding::ToWide(dir).c_str());
}
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
inline int Mkdir(const char* dir)
{
  return mkdir(dir, 00777);
}
inline int Rmdir(const char* dir)
{
  return rmdir(dir);
}
#endif

//----------------------------------------------------------------------------
ddepsCache::ddepsCache(std::string const& cachePath,
                       std::string const& realPath,
                       std::string const& lockPath):
  Loaded(false),
  Modified(false),
  RealPath(realPath),
  CachePath(cachePath),
  LockPath(lockPath)
{
  // Create the lock, if any

  if(LockPath.length() > 0)
    {
    // Lock
    while(Mkdir(LockPath.c_str()) != 0){}
    }
}

//----------------------------------------------------------------------------
ddepsCache::~ddepsCache()
{
  // Delete the lock, if any

  if(LockPath.length() > 0)
    {
      // Unlock
      while(Rmdir(LockPath.c_str()) != 0){}
    }
}

//----------------------------------------------------------------------------
void ddepsCache::Read()
{
  // Only read cache if it is newer than the corresponding source file
  //  *OR* if there is no corresponding file
  int cmp_result = 0;
  if(!cmSystemTools::FileTimeCompare(RealPath.c_str(),
                                    CachePath.c_str(),
                                    &cmp_result))
    {
    cmp_result = 0;
    }

  if(cmp_result < 0 || RealPath == "")
    {
    // Read Cache data
    cmsys::ifstream ifs(CachePath.c_str(), std::ifstream::binary);
    if(ifs)
      {
      ReadImpl(ifs);
      Loaded = true;
      ifs.close();
      }
    }
  else
    {
    OnOutdatedCache();
    }
}

//----------------------------------------------------------------------------
void ddepsCache::Write() const
{
  // Only write the cache if it has changed
  if(Modified)
    {
    cmsys::ofstream ofs(CachePath.c_str(), std::ofstream::binary);
    if(ofs)
      {
      WriteImpl(ofs);
      ofs.close();
      }
    }
}

