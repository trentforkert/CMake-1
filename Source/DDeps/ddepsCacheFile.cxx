/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "ddepsCacheFile.h"
#include "ddepsModule.h"
#include "ddepsLexer.h"

// Declare the parser method (defined in ddepsParser.cxx/ddepsParser.y)
int ddeps_yyparse(yyscan_t yyscanner);

// We need to track text in the manifest and the cachefiles, as
// there could be a module "api.txt", and a text "api.txt" which
// would be two different things. Without the information in both
// places, there would be no good way to tell what is what when
// reading the cache.
const std::string ddepsCacheFile::TEXT_TYPE = "text";
const std::string ddepsCacheFile::TEMPLATE_TYPE = "template";
const std::string ddepsCacheFile::PUBLIC_TYPE = "public";
const std::string ddepsCacheFile::PRIVATE_TYPE = "private";

//----------------------------------------------------------------------------
ddepsCacheFile::ddepsCacheFile(std::string const& cachePath,
                               std::string const& realPath,
                               size_t id,
                               ddepsOptions& options):
    ddepsCache(cachePath, realPath, ""), // no lock
    Id(id),
    ModuleName(""),
    Options(options)
{
  // Unlike the other ddepsCache* classes, we don't call Read here.
  // Instead, Read will be called later by Parse to try loading
  // from the cache before re-parsing a source file.
  // There are two big reasons for this:
  //  1) Avoid reading cache files we don't need to read
  //  2) Allow ddepsCacheManifest create skeletons before trying
  //     to resolve all the import links between ddepsCacheFiles
}

//----------------------------------------------------------------------------
ddepsCacheFile::~ddepsCacheFile()
{
  // Ensure that the cache gets written if needed
  Write();
}

//----------------------------------------------------------------------------
void ddepsCacheFile::GetObjDependencies(
                                std::deque<std::string>& unprocessedModules,
                                std::set<std::string>& encounteredModules,
                                std::set<std::string>& encounteredTexts,
                                bool recursePrivateImports)
{
  // Ensure this CacheFile is loaded
  if(ReadOrParse())
    {
    for(std::vector<ddepsImport>::const_iterator it = Imports.begin();
        it != Imports.end(); ++it)
      {
      if(it->Text)
        {
        // Always keep text imports
        encounteredTexts.insert(it->ImportString);
        }
      else if(recursePrivateImports || it->Public || it->Templated)
        {
        // Always recurse public/template imports
        if(encounteredModules.find(it->ImportString)
                        == encounteredModules.end())
          {
          unprocessedModules.push_back(it->ImportString);
          encounteredModules.insert(it->ImportString);
          }
        }
      }
    }
}

//----------------------------------------------------------------------------
bool ddepsCacheFile::ReadOrParse()
{
  // Try to read the cache if we need to
  if(!IsLoaded())
    {
    Read();

    // If still not loaded, parse the source
    if(!IsLoaded())
      {
      ParseSource();
      }
    }

  return IsLoaded();
}

//----------------------------------------------------------------------------
void ddepsCacheFile::WriteImpl(std::ostream& out) const
{
  for(std::vector<ddepsImport>::const_iterator it = Imports.begin();
      it != Imports.end(); ++it)
    {
    if(it != Imports.begin())
      {
      out << RECORD_DELIM;
      }

    if(it->Text)
      {
      out << TEXT_TYPE;
      }
    else if(it->Templated)
      {
      out << TEMPLATE_TYPE;
      }
    else if(it->Public)
      {
      out << PUBLIC_TYPE;
      }
    else
      {
      out << PRIVATE_TYPE;
      }

    out << UNIT_DELIM << it->ImportString;
    }
}

//----------------------------------------------------------------------------
void ddepsCacheFile::ReadImpl(std::istream& in)
{
  std::string type, importName;
  while(in.good())
    {
    std::getline(in, type, UNIT_DELIM);
    std::getline(in, importName, RECORD_DELIM);

    // We may not have actually read anything
    if(importName.length() > 0)
      {
      Imports.push_back(ddepsImport(importName,
                                    type==TEXT_TYPE,
                                    type==TEMPLATE_TYPE,
                                    type==PUBLIC_TYPE));
      }
    }
}

//----------------------------------------------------------------------------
void ddepsCacheFile::ParseSource()
{
  if(GetRealPath().length() > 0)
    {
    // Set up scaffolding for parsing
    ddepsModule Module(GetRealPath(), Options, Imports, ModuleName);

    // Do the actual parsing with bison/flex
    yyscan_t yyscanner;
    ddeps_yylex_init(&yyscanner);
    ddeps_yyset_extra(&Module, yyscanner);
    int res = ddeps_yyparse(yyscanner);
    ddeps_yylex_destroy(yyscanner);

    // Was there a problem in parsing?
    if( res != 0 )
      {
      std::cerr << "Parsing failed: " << res << std::endl;
      return;
      }

    // Set the Cache's state
    SetLoaded();
    SetModified();
    }
}

