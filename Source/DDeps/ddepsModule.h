/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef ddepsModule_h
#define ddepsModule_h
#include "ddepsScope.h"
#include "ddepsImport.h"
#include "ddepsOptions.h"
#include <stack>
#include <cmsys/FStream.hxx>

#define YYSTYPE ddepsModule::ParserType
#define YYSTYPE_IS_DECLARED
#define YY_EXTRA_TYPE ddepsModule*
#define YY_DECL int ddeps_yylex(YYSTYPE* yylvalp, yyscan_t yyscanner)

// Represents a D module
// D's module system has a one-to-one correspondence to the file system:
// modules are individual source files, packages are the directories that
// contain them. Used by the parser to encapsulate a module's data.
// Each module has its own set of version and debug identifiers, so if one
// module sets a version (i.e., with ``version = foo;``), this doesn't
// effect any other modules.
class ddepsModule
{
public:
  ddepsModule(std::string const& realPath,
              ddepsOptions const& options,
              std::vector<ddepsImport>& imports,
              std::string& importName);
  virtual ~ddepsModule();

  // For Parser
  void ParserError(const char* msg) const;

  void PushScope();
  void PopScope();
  void SetEndlessScope();
  void SetPublic(bool publicity);
  void SetTemplate();

  void AddModuleImport();
  void AppendModuleComponent(std::string const& mod);
  void SetModuleName();

  void RequireVersion(std::string const&);
  void DeclareVersion(std::string const&);
  void RequireVersionLevel(std::string const& num);
  void DeclareVersionLevel(std::string const& num);
  void RequireDebug(std::string const& vers);
  void DeclareDebug(std::string const& vers);
  void RequireDebugLevel(std::string const& num);
  void DeclareDebugLevel(std::string const& num);
  void RequireDebugFlag();

  void AddPossibleTextImport(std::string const&);
  void AcceptTextImportIfValid();
  void InvalidateTextImport();

  void BeginPossibleFunctionTemplate();
  void HitUnclaimedParenExpr();
  void MaybeFunctionTemplate();
  void CancelFunctionTemplate();

  // For Lexer
  typedef struct {
    std::string str;
  } ParserType;
  int LexInput(char* buf, int maxlen);
  void IncrementLine();
  void StartSavingStrings();
  void StopSavingStrings();

  void SetHexString();
  void SetRegularString();
  void SetWysiwygString();

  void AllocateParserType(ParserType* pt, const char* str);
  void AppendString(ParserType* ptr, std::string const& str);

  // These are mutually exclusive, allowing them to use one variable
  // This *might* change in the future, however
  void StartNestedComment();
  bool EndNestedComment();
  void StartNestedDelimitedString();
  bool EndNestedDelimitedString();
  void StartNestedTokenString();
  bool EndNestedTokenString();

  void SetDelimitedStringIdent(std::string const& str);
  bool CheckDelimitedStringIdent(std::string const& str);
  void SetCharDelimiter(char delim);
  bool CheckCharDelimiter(char delim);
  bool CheckNestingCharDelimiter(char delim);

private:
  size_t InterpretInteger(std::string const& num);
  std::string InterpretString(std::string const& str);
  std::string InterpretHexString(std::string const& str);
  std::string InterpretRegularString(std::string const& str);
  std::string InterpretWysiwygString(std::string const& str);

  bool OpenInputFile(std::string const& fn);
  void CloseInputFile();

  // Add the path as a dependency
  // "text" specifies a text-import
  // "temp" specifies a templated import
  // "pub" specifies a public import
  void AddDependency(std::string const& path, bool text, bool temp, bool pub);

  std::vector<ddepsImport>& ImportSet;

  size_t CurrentLine;
  std::string Filename;
  std::string PossibleTextImport;
  std::string BuiltModuleName;

  std::string& ModuleName;

  // Intentionally not a reference, as each Module has its
  // own scope when it comes to version and debug conditions.
  ddepsOptions Options;

  cmsys::ifstream InputFile;

  std::string strDelim;
  size_t nestingLevels;
  char charDelim;
  bool saveStrings;
  bool stringIsWysiwyg;
  bool stringIsHex;

  // This is static because we only have on ddepsModule at a time,
  // and reusing the memory gives a performance increase
  static std::stack<ddepsScope> ScopeStack;
};

#endif
