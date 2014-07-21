%{
/*============================================================================
  DDeps - D Dependency Scanner for CMake
  Copyright 2014 Trent Forkert

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/

/*

This file must be translated to C and modified to build everywhere.

Run flex like this:

    flex --fast --noline --prefix=ddeps_yy --header-file=ddepsLexer.h \
         -oddepsLexer.cxx ddepsLexer.in.l

Modify ddepsLexer.cxx
    - remove TABs
    - remove the #line directive at the top of the file
    - remove use of the 'register' storage class specifier
    - remove "yyscanner" argument from these methods:
        yy_fatal_error, ddeps_yyalloc, ddeps_yyrealloc, ddeps_yyfree,
        yy_try_nul_trans
    - remove the line in yy_try_NUL_trans that declars 'yyg'
    - remove "yyscanner = NULL" from end of ddepsLexer_yylex_destroy
    - remove the yyunput method (declaration and definition)
    - remove all YY_BREAK lines occurring right after return statements
    - change while ( 1 ) to for(;;)

Modify ddepsLexer.h
    - remove TABs
    - remove #line directives (avoids bogus warning on old Sun)
    - remove unistd

*/

#include "ddepsModule.h" /* Interface to parser object */

/* Replace the lexer input function. */
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) \
  { result = yyextra->LexInput(buf, max_size); }

/* Include the set of tokens from the parser. */
#include "ddepsTok.h"

/*--------------------------------------------------------------------------*/
%}

%option 8bit
%option reentrant
%option never-interactive
%option nounistd
%option noyywrap
%pointer

%x block_comment
%x nested_comment
%x character
%x regular_string
%x wysiwyg_string
%x alt_wysiwyg_string
%x hex_string
%x token_string
%x delimited_string
%x ident_delimited_string
%x nested_delimited_string
%x char_delimited_string

letter [a-zA-Z]
digit [0-9]
hex_digit [0-9a-fA-F]
/* D supports C99 Universal Identifiers. Instead of manually matching against
   all of those ranges, we determine identfiers by exluding important
   characters. Doing it "correctly" yeilds a much bigger file with
   no tangible benefits. */
ident_start _|{letter}|[^`\-=\[\]\\;',./~!@#$%^&*()+{}|:"<>? \t\r\n\v\f0-9]
ident_chars {ident_start}|{digit}|[^`\-=\[\]\\;',./~!@#$%^&*()+{}|:"<>? \t\r\n\v\f]
ident {ident_start}{ident_chars}*

escape \\.
/* This is actually invalid, but that doesn't matter for us */
escapedNewline \\\n


%%

"/*" { BEGIN(block_comment); }

<block_comment>"*/" { BEGIN(INITIAL); }

<block_comment>"*"

<block_comment>[^*\n]+

<block_comment>\n { yyextra->IncrementLine(); }

"/+" {
    BEGIN(nested_comment);
    yyextra->StartNestedComment();
}

<nested_comment>"/+" {
    yyextra->StartNestedComment();
}

<nested_comment>"+/" {
    if(yyextra->EndNestedComment())
        BEGIN(INITIAL);
}

<nested_comment>.

<nested_comment>\n { yyextra->IncrementLine(); }

' { BEGIN(character); }

<character>' { BEGIN(INITIAL); }

<character>{escape}

<character>{escapedNewline} {
  yyextra->IncrementLine();
}

<character>.

<character>\n { yyextra->IncrementLine(); }

\" {
  BEGIN(regular_string);
  yyextra->SetRegularString();
  yyextra->AllocateParserType(yylvalp, "");
}

<regular_string>{escape} {
  yyextra->AppendString(yylvalp, yytext);
}

<regular_string>{escapedNewline} {
  yyextra->IncrementLine();
}

<regular_string>\"[cwd]? {
  BEGIN(INITIAL);
  yyextra->StopSavingStrings();
  return dp_STRINGLITERAL;
}

<regular_string>[^\\\"\n]+ {
  yyextra->AppendString(yylvalp, yytext);
}

<regular_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

r\" {
  BEGIN(wysiwyg_string);
  yyextra->SetWysiwygString();
  yyextra->AllocateParserType(yylvalp, "");
}

<wysiwyg_string>\"[cwd]? {
  BEGIN(INITIAL);
  yyextra->StopSavingStrings();
  return dp_STRINGLITERAL;
}

<wysiwyg_string>[^\"\n]+ {
  yyextra->AppendString(yylvalp, yytext);
}

<wysiwyg_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

` {
  BEGIN(alt_wysiwyg_string);
  yyextra->SetWysiwygString();
  yyextra->AllocateParserType(yylvalp, "");
}

<alt_wysiwyg_string>`[cwd]? {
  BEGIN(INITIAL);
  yyextra->StopSavingStrings();
  return dp_STRINGLITERAL;
}

<alt_wysiwyg_string>[^`\n]+ {
  yyextra->AppendString(yylvalp, yytext);
}

<alt_wysiwyg_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

x\" {
  BEGIN(hex_string);
  yyextra->SetHexString();
  yyextra->AllocateParserType(yylvalp, "");
}

<hex_string>\"[cwd]? {
  BEGIN(INITIAL);
  yyextra->StopSavingStrings();
  return dp_STRINGLITERAL;
}

<hex_string>[^\"\n]+ {
  yyextra->AppendString(yylvalp, yytext);
}

<hex_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

"q{" {
  BEGIN(token_string);
  yyextra->SetWysiwygString();
  yyextra->AllocateParserType(yylvalp, "");
  yyextra->StartNestedTokenString();
}

<token_string>"{" {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->StartNestedTokenString();
}

<token_string>"}" {
  if(yyextra->EndNestedTokenString())
  {
    BEGIN(INITIAL);
    return dp_STRINGLITERAL;
  }
  else
  {
    yyextra->AppendString(yylvalp, yytext);
  }

}

<token_string>[^{}\n]+ {
  yyextra->AppendString(yylvalp, yytext);
}

<token_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

q\" {
  BEGIN(delimited_string);
  yyextra->SetWysiwygString();
  yyextra->AllocateParserType(yylvalp, "");
}

<delimited_string>{ident}\n {
  BEGIN(ident_delimited_string);
  yyextra->SetDelimitedStringIdent(yytext);
  yyextra->IncrementLine();
}

<delimited_string>{ident}\" {
  std::string cmp = yytext;
  if(cmp[0] == cmp[cmp.length()-2])
  {
    BEGIN(INITIAL);
    yyextra->AppendString(yylvalp, cmp.substr(1, cmp.length()-3));
  }
  else
  {
    BEGIN(char_delimited_string);
    yyextra->SetCharDelimiter(cmp[0]);
    yyextra->AppendString(yylvalp, cmp.substr(1, cmp.length()-2));
  }
}

<delimited_string>{ident} {
  BEGIN(char_delimited_string);
  yyextra->SetCharDelimiter(yytext[0]);
  yyextra->AppendString(yylvalp, &yytext[1]);
}

<delimited_string>"{" {
  BEGIN(nested_delimited_string);
  yyextra->SetCharDelimiter('}');
  yyextra->StartNestedDelimitedString();
}

<delimited_string>"(" {
  BEGIN(nested_delimited_string);
  yyextra->SetCharDelimiter(')');
  yyextra->StartNestedDelimitedString();
}

<delimited_string>"<" {
  BEGIN(nested_delimited_string);
  yyextra->SetCharDelimiter('>');
  yyextra->StartNestedDelimitedString();
}

<delimited_string>"[" {
  BEGIN(nested_delimited_string);
  yyextra->SetCharDelimiter(']');
  yyextra->StartNestedDelimitedString();
}

<delimited_string>. {
  BEGIN(char_delimited_string);
  yyextra->SetCharDelimiter(yytext[0]);
}

<ident_delimited_string>\n{ident}\" {
  if( yyextra->CheckDelimitedStringIdent(yytext) )
  {
    BEGIN(INITIAL);
    yyextra->StopSavingStrings();
    return dp_STRINGLITERAL;
  }
  yyextra->IncrementLine();
}

<ident_delimited_string>\n{ident} {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

<ident_delimited_string>[^\n]+ {
  yyextra->AppendString(yylvalp, yytext);
}

<ident_delimited_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

<nested_delimited_string>.\" {
  if( yyextra->CheckCharDelimiter(yytext[0]) )
  {
    if(yyextra->EndNestedDelimitedString())
    {
      BEGIN(INITIAL);
      yyextra->SetCharDelimiter('\0');
      yyextra->StopSavingStrings();
      return dp_STRINGLITERAL;
    }
  }
  else
  {
    yyextra->AppendString(yylvalp, yytext);
  }
}

<nested_delimited_string>. {
  if( yyextra->CheckNestingCharDelimiter(yytext[0]) )
  {
    yyextra->StartNestedDelimitedString();
  }
  else
  {
    yyextra->AppendString(yylvalp, yytext);
  }
}

<nested_delimited_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

<char_delimited_string>.\" {
  if ( yyextra->CheckCharDelimiter(yytext[0]) )
  {
    BEGIN(INITIAL);
    yyextra->SetCharDelimiter('\0');
    yyextra->StopSavingStrings();
    return dp_STRINGLITERAL;
  }
  else
  {
    yyextra->AppendString(yylvalp, yytext);
  }
}

<char_delimited_string>. {
  yyextra->AppendString(yylvalp, yytext);
}

<char_delimited_string>\n {
  yyextra->AppendString(yylvalp, yytext);
  yyextra->IncrementLine();
}

public { return dp_PUBLIC; }
protected { return dp_PROTECTED; }
private { return dp_PRIVATE; }
package { return dp_PACKAGE; }
module { yyextra->StartSavingStrings(); return dp_MODULE; }
debug { yyextra->StartSavingStrings(); return dp_DEBUG; }
import { yyextra->StartSavingStrings(); return dp_IMPORT; }
version { yyextra->StartSavingStrings(); return dp_VERSION; }
unittest { return dp_UNITTEST; }

template { return dp_TEMPLATE; }
class { return dp_CLASS; }
interface { return dp_INTERFACE; }
struct { return dp_STRUCT; }
union { return dp_UNION; }
if { return dp_IF; }

__EOF__(.|\n)* /* Don't parse beyond __EOF__*/
\x1A(.|\n)*
\x00(.|\n)*

"," { return dp_COMMA; }
":" { yyextra->StopSavingStrings(); return dp_COLON; }
"}" { yyextra->StopSavingStrings(); return dp_CURLYEND; }
"{" { yyextra->StopSavingStrings(); return dp_CURLYSTART; }
"\." { return dp_DOT; }
"=" { return dp_EQUAL; }
"\)" { yyextra->StopSavingStrings(); return dp_PARENEND; }
"\(" { return dp_PARENSTART; }
";" { yyextra->StopSavingStrings(); return dp_SEMICOL; }
"!" { return dp_EXCLAIM; }

#![^\n]* { return dp_SHEBANG; }

{ident} {
    yyextra->AllocateParserType(yylvalp, yytext);
    return dp_NAME;
}

[0-9][0-9_]* {
  yyextra->AllocateParserType(yylvalp, yytext);
  return dp_INTLITERAL;
}
0[xX][0-9a-f_]* {
  yyextra->AllocateParserType(yylvalp, yytext);
  return dp_INTLITERAL;
}
0[bB][01_]* {
  yyextra->AllocateParserType(yylvalp, yytext);
  return dp_INTLITERAL;
}

\/\/[^\n]*

\n { yyextra->IncrementLine(); }

. /* Any other text can safely be ignored */

%%
