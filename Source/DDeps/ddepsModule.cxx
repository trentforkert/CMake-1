/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "ddepsModule.h"
#include "ddepsCacheManifest.h"
#include "ddepsOptions.h"
#include "ddeps_entities.h"
#include <cmSystemTools.h>

// Static for memory efficiency, since we only operate on one Module at a time
std::stack<ddepsScope> ddepsModule::ScopeStack;

//----------------------------------------------------------------------------
ddepsModule::ddepsModule(std::string const& realPath,
                         ddepsOptions const& options,
                         std::vector<ddepsImport>& imports,
                         std::string& importName)
  : ImportSet(imports),
    Filename(realPath),
    ModuleName(importName),
    Options(options),
    strDelim(""),
    nestingLevels(0),
    charDelim('\0'),
    saveStrings(false),
    stringIsWysiwyg(false),
    stringIsHex(false)
{
  ScopeStack.push(ddepsScope(options));
  CurrentLine = 1;

  OpenInputFile(Filename);
}

//----------------------------------------------------------------------------
ddepsModule::~ddepsModule()
{
  CloseInputFile();

  while(!ScopeStack.empty())
    ScopeStack.pop();
}

//----------------------------------------------------------------------------
void ddepsModule::ParserError(const char* message) const
{
  std::cerr << "DDeps: "
            << Filename
            << ":"
            << CurrentLine
            << ": "
            << message
            << std::endl;
}

//----------------------------------------------------------------------------
void ddepsModule::PushScope()
{
  ScopeStack.push(ddepsScope(ScopeStack.top()));
}

//----------------------------------------------------------------------------
void ddepsModule::PopScope()
{
  bool again = ScopeStack.top().EndlessScope;
  ScopeStack.pop();
  if(again) PopScope();
}

//----------------------------------------------------------------------------
void ddepsModule::SetEndlessScope()
{
  ScopeStack.top().EndlessScope = true;
}

//----------------------------------------------------------------------------
void ddepsModule::SetPublic(bool public_)
{
  ScopeStack.top().Public = public_;
}

//----------------------------------------------------------------------------
void ddepsModule::SetTemplate()
{
  ScopeStack.top().Template = true;
}

//----------------------------------------------------------------------------
void ddepsModule::AddModuleImport()
{
  if(ScopeStack.top().RequirementsMet)
    {
    AddDependency(BuiltModuleName,
                  false,
                  ScopeStack.top().Template,
                  ScopeStack.top().Public);
    }
  BuiltModuleName.clear();
}

//----------------------------------------------------------------------------
void ddepsModule::AppendModuleComponent(std::string const& component)
{
  // We build with "/" directly instead of ".", since this
  // is the form we'll need it in anyway
  if(BuiltModuleName.length() > 0)
    {
    BuiltModuleName += "/";
    }
  BuiltModuleName += component;
}

//----------------------------------------------------------------------------
void ddepsModule::SetModuleName()
{
  ModuleName = BuiltModuleName;
  BuiltModuleName.clear();
}

//----------------------------------------------------------------------------
void ddepsModule::RequireVersion(std::string const& ident)
{
  if(Options.VersionIdents.find(ident) == Options.VersionIdents.end())
    ScopeStack.top().RequirementsMet = false;
}

//----------------------------------------------------------------------------
void ddepsModule::DeclareVersion(std::string const& ident)
{
  if(ScopeStack.top().RequirementsMet)
    Options.VersionIdents.insert(ident);
}

//----------------------------------------------------------------------------
void ddepsModule::RequireVersionLevel(std::string const& num)
{
  if(ScopeStack.top().RequirementsMet)
    {
    size_t lev = InterpretInteger(num);
    if(lev > ScopeStack.top().MaxVersionLevel)
      {
      ScopeStack.top().RequirementsMet = false;
      }
    }
}

//----------------------------------------------------------------------------
void ddepsModule::DeclareVersionLevel(std::string const& num)
{
  if( ScopeStack.top().RequirementsMet )
    {
    size_t lev = InterpretInteger(num);
    ScopeStack.top().MaxVersionLevel =
        lev > ScopeStack.top().MaxVersionLevel
      ? lev : ScopeStack.top().MaxVersionLevel;
    }
}

//----------------------------------------------------------------------------
void ddepsModule::RequireDebug(std::string const& ident)
{
  if(Options.DebugIdents.find(ident) == Options.DebugIdents.end())
    ScopeStack.top().RequirementsMet = false;
}

//----------------------------------------------------------------------------
void ddepsModule::DeclareDebug(std::string const& ident)
{
  if(ScopeStack.top().RequirementsMet)
    Options.DebugIdents.insert(ident);
}

//----------------------------------------------------------------------------
void ddepsModule::RequireDebugLevel(std::string const& num)
{
  if( ScopeStack.top().RequirementsMet )
    {
    size_t lev = InterpretInteger(num);
    if(lev > ScopeStack.top().MaxDebugLevel)
      {
      ScopeStack.top().RequirementsMet = false;
      }
    }
}

//----------------------------------------------------------------------------
void ddepsModule::DeclareDebugLevel(std::string const& num)
{
  if( ScopeStack.top().RequirementsMet )
    {
    size_t lev = InterpretInteger(num);
    ScopeStack.top().MaxDebugLevel =
        lev > ScopeStack.top().MaxDebugLevel
      ? lev : ScopeStack.top().MaxDebugLevel;
    }
}

//----------------------------------------------------------------------------
void ddepsModule::RequireDebugFlag()
{
  if( ScopeStack.top().RequirementsMet )
    {
    // D allows either -debug or -debug=<number> to enable debug { } blocks
    if( !ScopeStack.top().DebugFlag && ScopeStack.top().MaxDebugLevel == 0 )
      {
      ScopeStack.top().RequirementsMet = false;
      }
    }
}

//----------------------------------------------------------------------------
void ddepsModule::AddPossibleTextImport(std::string const& imp)
{
  if(ScopeStack.top().RequirementsMet)
    {
    PossibleTextImport += InterpretString(imp);
    }
}

//----------------------------------------------------------------------------
void ddepsModule::AcceptTextImportIfValid()
{
  if(ScopeStack.top().RequirementsMet && PossibleTextImport.length() > 0)
    {
    AddDependency(PossibleTextImport, true, false, true);
    }
  PossibleTextImport.clear();
}

//----------------------------------------------------------------------------
void ddepsModule::InvalidateTextImport()
{
  if(ScopeStack.top().RequirementsMet)
    {
    PossibleTextImport.clear();
    }
}

//----------------------------------------------------------------------------
void ddepsModule::BeginPossibleFunctionTemplate()
{
  if(ScopeStack.top().RequirementsMet && !ScopeStack.top().Template)
    {
    if(ScopeStack.top().UnclaimedParenExprSeq < 2)
      {
      ScopeStack.top().UnclaimedParenExprSeq = 0;
      }
    }
}

//----------------------------------------------------------------------------
void ddepsModule::HitUnclaimedParenExpr()
{
  if(ScopeStack.top().RequirementsMet && !ScopeStack.top().Template)
    {
    if(ScopeStack.top().UnclaimedParenExprSeq >= 0)
      {
      ScopeStack.top().UnclaimedParenExprSeq ++;
      }
    }
}

//----------------------------------------------------------------------------
void ddepsModule::MaybeFunctionTemplate()
{
  ddepsScope& top = ScopeStack.top();
  ScopeStack.pop();
  ddepsScope& parent = ScopeStack.top();

  if(top.RequirementsMet && !top.Template)
    {
    if(parent.UnclaimedParenExprSeq >= 2)
      {
      top.Template = true;
      }
    parent.UnclaimedParenExprSeq = -1;
    }

  ScopeStack.push(top);
}

//----------------------------------------------------------------------------
void ddepsModule::CancelFunctionTemplate()
{
  if(ScopeStack.top().RequirementsMet && !ScopeStack.top().Template)
    {
    ScopeStack.top().UnclaimedParenExprSeq = -1;
    }
}

//----------------------------------------------------------------------------
int ddepsModule::LexInput(char* buf, int maxlen)
{
  if(InputFile.good())
    {
    InputFile.read(buf, maxlen);
    return InputFile.gcount();
    }
  else
    {
    buf[0] = '\n';
    return 0;
    }
}

//----------------------------------------------------------------------------
void ddepsModule::IncrementLine()
{
  CurrentLine ++;
}

//----------------------------------------------------------------------------
void ddepsModule::StartSavingStrings()
{
  saveStrings = true;
}

//----------------------------------------------------------------------------
void ddepsModule::StopSavingStrings()
{
  saveStrings = false;
}

//----------------------------------------------------------------------------
void ddepsModule::SetHexString()
{
  stringIsWysiwyg = false;
  stringIsHex = true;
}

//----------------------------------------------------------------------------
void ddepsModule::SetRegularString()
{
  stringIsWysiwyg = false;
  stringIsHex = false;
}

//----------------------------------------------------------------------------
void ddepsModule::SetWysiwygString()
{
  stringIsWysiwyg = true;
  stringIsHex = false;
}

//----------------------------------------------------------------------------
void ddepsModule::AllocateParserType(ParserType* pt, const char* str)
{
  if(saveStrings)
    {
    pt->str = str;
    }
}

//----------------------------------------------------------------------------
void ddepsModule::AppendString(ParserType* ptr, std::string const& str)
{
  if(saveStrings)
  {
    ptr->str += str;
  }
}

//----------------------------------------------------------------------------
void ddepsModule::StartNestedComment()
{
  nestingLevels ++;
}

//----------------------------------------------------------------------------
bool ddepsModule::EndNestedComment()
{
  return --nestingLevels == 0;
}

//----------------------------------------------------------------------------
void ddepsModule::StartNestedDelimitedString()
{
  nestingLevels ++;
}

//----------------------------------------------------------------------------
bool ddepsModule::EndNestedDelimitedString()
{
  return --nestingLevels == 0;
}

//----------------------------------------------------------------------------
void ddepsModule::StartNestedTokenString()
{
  nestingLevels ++;
}

//----------------------------------------------------------------------------
bool ddepsModule::EndNestedTokenString()
{
  return --nestingLevels == 0;
}

//----------------------------------------------------------------------------
void ddepsModule::SetDelimitedStringIdent(std::string const& str)
{
  strDelim.clear();
  // Cut the newline from the input
  strDelim += str.substr(0, str.length() - 1);
}

//----------------------------------------------------------------------------
bool ddepsModule::CheckDelimitedStringIdent(std::string const& str)
{
  // Cut the newline and the double quote
  return strDelim == str.substr(1, str.find("\"") - 1);
}

//----------------------------------------------------------------------------
void ddepsModule::SetCharDelimiter(char delim)
{
  charDelim = delim;
}

//----------------------------------------------------------------------------
bool ddepsModule::CheckCharDelimiter(char delim)
{
  return charDelim == delim;
}

//----------------------------------------------------------------------------
bool ddepsModule::CheckNestingCharDelimiter(char delim)
{
  return (delim == '<' && charDelim == '>')
      || (delim == '(' && charDelim == ')')
      || (delim == '{' && charDelim == '}')
      || (delim == '[' && charDelim == ']');
}

//----------------------------------------------------------------------------
size_t ddepsModule::InterpretInteger(std::string const& num)
{
  size_t res = 0;
  int base = 10;
  int startFrom = 0;
  switch(num[1])
    {
    case 'x':
    case 'X':
      base = 16;
      startFrom = 2;
      break;
    case 'b':
    case 'B':
      base = 2;
      startFrom = 2;
      break;
    // D doesn't support octal literals
    }

  for(size_t i = startFrom; i < num.length(); ++i)
    {
    size_t val = 0;
    char digit = num[i];
    if('0' <= digit && digit <= '9')
      {
      val = digit - '0';
      }
    else if('A' <= digit && digit <= 'F')
      {
      val = digit - 'A' + 10;
      }
    else if('a' <= digit && digit <= 'f')
      {
      val = digit - 'a' + 10;
      }
    else // Underscore is just a separator
      {
      continue;
      }

    res = res * base + val;
    }

  return res;
}

//----------------------------------------------------------------------------
std::string ddepsModule::InterpretString(std::string const& str)
{
  if(stringIsWysiwyg)
    {
    return InterpretWysiwygString(str);
    }
  else if(stringIsHex)
    {
    return InterpretHexString(str);
    }
  else
    {
    return InterpretRegularString(str);
    }
}

std::string ddepsModule::InterpretRegularString(std::string const& str)
{
  std::string result = "";
  size_t beg = 0, end = 0;
  int unilen = 8;
  while(end != std::string::npos)
    {
    end = str.find('\\', beg);
    if(end == std::string::npos)
      {
      result += str.substr(beg, end-beg);
      }
    else
      {
      result += str.substr(beg, end-beg);
      switch(str[end+1])
        {
        case 'x':
          {
          unsigned int chr;
          std::istringstream iss(str.substr(end+2,2));
          iss >> std::hex >> chr;
          result  += (char) chr;
          beg = end + 4;
          break;
          }
        case 'u': // Translate \uXXXX into UTF-8
          // Only take four characters
          unilen = 4;
        case 'U': // Translate \uXXXXXXXX into UTF-8
          {
          long uni;
          std::istringstream iss(str.substr(end+2,unilen));
          iss >> std::hex >> uni;
          if(uni < 0x80) // 1 byte (i.e., ASCII)
            {
            result += (char) uni;
            }
          else if(uni < 0x800) // 2 bytes
            {
            result += (char) (0xC0 | ((uni >> 6) & 0x1F));
            result += (char) (0x80 | (uni & 0x3F));
            }
          else if(uni < 0x10000) // 3 bytes
            {
            result += (char) (0xE0 | ((uni >> 12) & 0x0F));
            result += (char) (0x80 | ((uni >> 6) & 0x3F));
            result += (char) (0x80 | (uni & 0x3F));
            }
          else if(uni < 0x110000) // 4 bytes
            {
            result += (char) (0xF0 | ((uni >> 18) & 0x07));
            result += (char) (0x80 | ((uni >> 12) & 0x3F));
            result += (char) (0x80 | ((uni >> 6) & 0x3F));
            result += (char) (0x80 | (uni & 0x3F));
            }
          else
            {
            // Just ignore invalid unicode escapes for now
            }
          beg = end + 2 + unilen;
          unilen = 8;
          break;
          }
        case '&': // Translate HTML-5 Character identities (\&ident;)
          {
          std::string ent = str.substr(end+2, str.find(';', end+2)-(end+2));
          // defined in ddeps_entities.h
          result += translateEntity(ent);
          beg = end + 3 + ent.length();
          break;
          }
        case '0': // Octal escape sequence
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
          {
          int byte;
          int len = 1;
          if('0' <= str[end+2] && str[end+2] <= '7')
            {
            len ++;
            if('0' <= str[end+3] && str[end+3] <= '7')
              {
              len ++;
              }
            }
          std::istringstream iss(str.substr(end+1,len));
          iss >> std::oct >> byte;
          result += (char) byte;
          beg = end + 1 + len;
          break;
          }
        case 'a':
          result += '\a';
          beg = end + 2;
          break;
        case 'b':
          result += '\b';
          beg = end + 2;
          break;
        case 'f':
          result += '\f';
          beg = end + 2;
          break;
        case 'n':
          result += '\n';
          beg = end + 2;
          break;
        case 'r':
          result += '\r';
          beg = end + 2;
          break;
        case 't':
          result += '\t';
          beg = end + 2;
          break;
        case 'v':
          result += '\v';
          beg = end + 2;
          break;
        default:
          result += str[end+1];
          beg = end + 2;
        }
      }
    }
  return result;
}

//----------------------------------------------------------------------------
std::string ddepsModule::InterpretHexString(std::string const& str)
{
  std::string result;
  size_t digitsEncountered = 0;
  char x = 0;

  for(size_t i=0; i < str.length(); ++i)
    {
    if('A' <= str[i] && str[i] <= 'F')
      {
      x <<= 4;
      x |= (str[i] - 'A' + 10);
      digitsEncountered ++;
      }
    else if('a' <= str[i] && str[i] <= 'f')
      {
      x <<= 4;
      x |= (str[i] - 'a' + 10);
      digitsEncountered ++;
      }
    else if('0' <= str[i] && str[i] <= '9')
      {
      x <<= 4;
      x |= (str[i] - '0');
      digitsEncountered ++;
      }

    if(digitsEncountered % 2 == 0 && digitsEncountered > 0)
      {
        result += x;
        x = 0;
        digitsEncountered = 0;
      }
    }

  return result;
}

//----------------------------------------------------------------------------
std::string ddepsModule::InterpretWysiwygString(std::string const& str)
{
  return str;
}

//----------------------------------------------------------------------------
bool ddepsModule::OpenInputFile(std::string const& fn)
{
  // Get the C-string once
  const char* cfn = fn.c_str();

  if(!cmSystemTools::FileExists(cfn))
    {
    std::cerr << "File not found: " << fn << std::endl;
    return false;
    }

  InputFile.open(cfn, std::ios::binary);

  if(!InputFile)
    {
    std::cerr << "Read error: " << fn << std::endl;
    return false;
    }

  // Technically, D supports ASCII and any Unicode encoding.
  // The flex lexer cannot realistically support non-UTF-8.
  // So, make sure the source is either ASCII or UTF-8.
  cmsys::FStream::BOM bom = cmsys::FStream::ReadBOM(InputFile);
  if(bom != cmsys::FStream::BOM_None &&
     bom != cmsys::FStream::BOM_UTF8)
    {
    std::cerr << "File starts with a Byte-Order-Mark that is not UTF-8:"
              << std::endl
              << fn
              << std::endl;
    return false;
    }

  return true;
}

//----------------------------------------------------------------------------
void ddepsModule::CloseInputFile()
{
  InputFile.close();
}

//----------------------------------------------------------------------------
void ddepsModule::AddDependency(std::string const& impstring,
                                bool text,
                                bool temp,
                                bool pub)
{
  for(std::vector<ddepsImport>::iterator it = ImportSet.begin();
      it != ImportSet.end(); ++it)
    {
    if(   it->Text != text
      ||  it->Templated != temp
      ||  it->Public != pub
      ||  it->ImportString != impstring)
      continue; // ...looking

    // We found a match!
    return;
    }

  //If we get here, the dependency isn't in the vector yet
  ImportSet.push_back(ddepsImport(impstring, text, temp, pub));
}
