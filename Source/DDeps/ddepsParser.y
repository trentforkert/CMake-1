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

Run bison like this:

  bison --yacc --name-prefix=ddeps_yy \
        --defines=ddepsTok.h -oddepsParser.cxx ddepsParser.y

Modify ddepsParser.cxx:
  - remove TABs

*/

/*-------------------------------------------------------------------------*/
#include "ddepsModule.h" /* Interface to module parser object */
#include "ddepsLexer.h" /* Interface to lexer object */
#include "ddepsTok.h" /* Needs YYSTYPE for YY_DECL */
#include <iostream>

/* Configure the parser to use a lexer object. */
#define YYPARSE_PARAM yyscanner
#define YYLEX_PARAM yyscanner
#define YYERROR_VERBOSE 1
#define yyGetParser (ddeps_yyget_extra(yyscanner))
#define ddeps_yyerror(y,x) \
        yyGetParser->ParserError(x)


/* Forward declare the lexer entry point */
YY_DECL;

/* Disable some warnings in the generated code */
#ifdef __BORLANDC__
# pragma warn -8004 /* Variable assigned a value that is not used.  */
# pragma warn -8008 /* condition always returns true */
# pragma warn -8060 /* possibly incorrect assignment */
# pragma warn -8066 /* unreachable code */
#endif
#ifdef _MSC_VER
# pragma warning (disable: 4102) /* Unused goto label.  */
# pragma warning (disable: 4065) /* Switch statement contains default but no case. */
#endif
%}

/* Generate a reentrant parser object */
%pure-parser
%lex-param {yyscan_t yyscanner}
%parse-param {yyscan_t yyscanner}

/*-------------------------------------------------------------------------*/
/* Tokens*/

%token dp_SHEBANG "#!"

%token dp_COLON ":"
%token dp_COMMA ","
%token dp_CURLYEND "}"
%token dp_CURLYSTART "{"
%token dp_DOT "."
%token dp_EQUAL "="
%token dp_PARENEND ")"
%token dp_PARENSTART "("
%token dp_SEMICOL ";"
%token dp_EXCLAIM "!"

%token dp_STRINGLITERAL "string"
%token dp_INTLITERAL "integer"
%token dp_NAME "identifer"

%token dp_DEBUG "debug"
%token dp_VERSION "version"
%token dp_IMPORT "import"
%token dp_UNITTEST "unittest"

%token dp_PUBLIC "public"
%token dp_PRIVATE "private"
%token dp_PACKAGE "package"
%token dp_PROTECTED "protected"

%token dp_TEMPLATE "template"
%token dp_CLASS "class"
%token dp_INTERFACE "interface"
%token dp_STRUCT "struct"
%token dp_UNION "union"
%token dp_IF "if"
%token dp_MODULE "module"

%right dp_DEBUG dp_UNITTEST dp_PARENSTART dp_EQUAL dp_EXCLAIM

/*-------------------------------------------------------------------------*/
/* Grammar */
%%

File: dp_SHEBANG Module
    | Module
    ;

Module: ModuleDeclaration Declarations
      | ModuleDeclaration /* empty */
      | Declarations
      ;

Declarations: Declaration
            | Declarations Declaration
            | Declarations SecondaryGarbage
            ;

Declaration: Literal
           | ProtectionDeclaration
           | ImportDeclaration
           | ConditionalDeclaration
           | Specification
           | Block
           | NonTemplateClass
           | NonTemplateInterface
           | NonTemplateStruct
           | NonTemplateUnion
           | TemplateDeclaration
           | Garbage
           ;

ModuleDeclaration: dp_MODULE ModuleName dp_SEMICOL
                 {
                   yyGetParser->SetModuleName();
                 }
                 ;

ModuleName: Identifier
          {
            yyGetParser->AppendModuleComponent($<str>1);
          }
          | ModuleName dp_DOT Identifier
          {
            yyGetParser->AppendModuleComponent($<str>3);
          }
          ;

TemplateDeclaration: PlainTemplate
                   | ClassTemplate
                   | StructTemplate
                   | InterfaceTemplate
                   | UnionTemplate
                   ;

PlainTemplate: dp_TEMPLATE Identifier ParenExpr Constraint TemplateContent
             | dp_TEMPLATE Identifier ParenExpr TemplateContent
             ;

ClassTemplate: dp_CLASS Identifier ParenExpr ClassAddendums TemplateContent
             ;

StructTemplate: dp_STRUCT Identifier ParenExpr Constraint TemplateContent
              | dp_STRUCT Identifier ParenExpr TemplateContent
              ;

InterfaceTemplate: dp_INTERFACE Identifier ParenExpr ClassAddendums TemplateContent
                 ;

UnionTemplate: dp_UNION Identifier ParenExpr Constraint TemplateContent
             | dp_UNION Identifier ParenExpr TemplateContent

TemplateContent: TemplateBlockStart BlockContent TemplateBlockEnd
               ;

TemplateBlockStart: dp_CURLYSTART
                  {
                    yyGetParser->PushScope();
                    yyGetParser->SetTemplate();
                  }
                  ;

TemplateBlockEnd: dp_CURLYEND
                {
                  yyGetParser->PopScope();
                }

NonTemplateClass: dp_CLASS Identifier SuperClasses Block
                | dp_CLASS Identifier Block
                | dp_CLASS Identifier dp_SEMICOL
                | dp_CLASS Block
                ;

NonTemplateStruct: dp_STRUCT Identifier Block
                 | dp_STRUCT Identifier dp_SEMICOL
                 | dp_STRUCT Block
                 ;

NonTemplateInterface: dp_INTERFACE Identifier SuperClasses Block
                    | dp_INTERFACE Identifier Block
                    | dp_INTERFACE Identifier dp_SEMICOL
                    ;

NonTemplateUnion: dp_UNION Identifier Block
                | dp_UNION Identifier dp_SEMICOL
                | dp_UNION Block
                ;

Constraint: dp_IF ParenExpr
          ;

SuperClasses: dp_COLON ClassNames
            ;

ClassNames: ClassNameWithProtection
          | ClassNames dp_COMMA ClassNameWithProtection
          | /*empty*/
          ;

ClassNameWithProtection: ClassName
                       | InheritanceProtection ClassName
                       ;

InheritanceProtection: dp_PUBLIC
                     | dp_PROTECTED
                     | dp_PACKAGE
                     | dp_PRIVATE
                     ;

ClassName: ClassFullyQualifiedName
         | ClassFullyQualifiedName dp_EXCLAIM ParenExpr
         | ClassFullyQualifiedName dp_EXCLAIM Identifier
         ;

ClassFullyQualifiedName: Identifier
                       | ClassFullyQualifiedName dp_DOT Identifier
                       ;

ClassAddendums: /* empty */
              | ClassAddendums Constraint
              | ClassAddendums SuperClasses
              ;

ProtectionDeclaration: Protection Declaration EndProtection
                     | Protection dp_COLON
                     {
                       yyGetParser->SetEndlessScope();
                     }
                     ;

Protection: dp_PUBLIC
          {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(true);
          }
          | dp_PRIVATE
          {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(false);
          }
          | dp_PROTECTED
          {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(false);
          }
          | dp_PACKAGE
          {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(false);
          }
          ;

EndProtection: /* empty */
             {
              yyGetParser->PopScope();
             }
             ;

Block: BlockStart BlockContent BlockEnd
     ;

BlockStart: dp_CURLYSTART
          {
            yyGetParser->PushScope();
            yyGetParser->MaybeFunctionTemplate();
          }
          ;

BlockEnd: dp_CURLYEND
        {
          yyGetParser->PopScope();
        }
        ;

BlockContent: /*empty*/
            | Declarations
            ;

Garbage: dp_NAME
       {
         yyGetParser->BeginPossibleFunctionTemplate();
       }
       | dp_SEMICOL
       {
         yyGetParser->CancelFunctionTemplate();
       }
       | dp_DOT
       | dp_EQUAL
       {
        yyGetParser->CancelFunctionTemplate();
       }
       | dp_COMMA
       {
        yyGetParser->CancelFunctionTemplate();
       }
       | dp_IF
       | dp_EXCLAIM
       | ParenExpr
       {
        yyGetParser->HitUnclaimedParenExpr();
       }
       | dp_INTLITERAL
       ;

SecondaryGarbage: dp_COLON
                ;

Literal: dp_STRINGLITERAL
       ;

ImportDeclaration: dp_IMPORT ImportList dp_SEMICOL
                 | dp_IMPORT dp_PARENSTART TextImport dp_PARENEND
                 {
                  yyGetParser->AcceptTextImportIfValid();
                 }
                 ;

TextImport: dp_STRINGLITERAL
          {
            // Propose match
            yyGetParser->AddPossibleTextImport($<str>1);
          }
          | ComplicatedExpression
          {
            yyGetParser->InvalidateTextImport();
          }
          ;

Expression: dp_STRINGLITERAL
          | ComplicatedExpression
          ;

ComplicatedExpression: ExprGarbage
                     | ParenExpr
                     | CurlyExpr
                     | Expression dp_STRINGLITERAL
                     | Expression ExprGarbage
                     | Expression ParenExpr
                     | Expression CurlyExpr
                     ;

ExprGarbage: dp_NAME
           | dp_SEMICOL
           | dp_DOT
           | dp_EQUAL
           | dp_COMMA
           | dp_STRUCT
           | dp_CLASS
           | dp_INTERFACE
           | dp_UNION
           | dp_COLON
           | dp_EXCLAIM
           | dp_IMPORT
           | dp_IF
           | dp_INTLITERAL
           ;

ParenExpr: dp_PARENSTART Expression dp_PARENEND
         | dp_PARENSTART /*empty*/ dp_PARENEND
         ;

CurlyExpr: dp_CURLYSTART Expression dp_CURLYEND
         | dp_CURLYSTART /*empty*/ dp_CURLYEND
         ;

ImportList: Import
          | ImportBindings
          | Import dp_COMMA ImportList
          ;

Import: ModuleFullyQualifiedName
      {
        yyGetParser->AddModuleImport();
      }
      | ModuleAliasIdentifier dp_EQUAL ModuleFullyQualifiedName
      {
        yyGetParser->AddModuleImport();
      }
      ;

ImportBindings: Import dp_COLON ImportBindList
              ;

ImportBindList: ImportBind
              | ImportBind dp_COMMA ImportBindList
              ;

ImportBind: Identifier
          | Identifier dp_EQUAL Identifier
          ;

ModuleAliasIdentifier: Identifier
                     ;

ModuleFullyQualifiedName: Identifier
                        {
                          yyGetParser->AppendModuleComponent($<str>1);
                        }
                        | Packages dp_DOT Identifier
                        {
                          yyGetParser->AppendModuleComponent($<str>3);
                        }
                        ;

Packages: Identifier
        {
          yyGetParser->AppendModuleComponent($<str>1);
        }
        | Packages dp_DOT Identifier
        {
          yyGetParser->AppendModuleComponent($<str>3);
        }
        ;

ConditionalDeclaration: Condition Declaration EndCondition
                      | Condition dp_COLON
                      {
                        yyGetParser->SetEndlessScope();
                      }
                      ;

Condition: VersionCondition
         | DebugCondition
         | UnittestCondition
         {
           yyGetParser->PushScope();
           yyGetParser->RequireVersion("unittest");
         }
         ;

VersionCondition: dp_VERSION dp_PARENSTART Identifier dp_PARENEND
                {
                  yyGetParser->PushScope();
                  yyGetParser->RequireVersion($<str>3);
                }
                | dp_VERSION dp_PARENSTART dp_UNITTEST dp_PARENEND
                {
                  yyGetParser->PushScope();
                  yyGetParser->RequireVersion("unittest");
                }
                | dp_VERSION dp_PARENSTART dp_INTLITERAL dp_PARENEND
                {
                  yyGetParser->PushScope();
                  yyGetParser->RequireVersionLevel($<str>3);
                }
                ;


DebugCondition: dp_DEBUG
              {
                yyGetParser->PushScope();
                yyGetParser->RequireDebugFlag();
              }
              | dp_DEBUG dp_PARENSTART Identifier dp_PARENEND
              {
                yyGetParser->PushScope();
                yyGetParser->RequireDebug($<str>3);
              }
              | dp_DEBUG dp_PARENSTART dp_INTLITERAL dp_PARENEND
              {
                yyGetParser->PushScope();
                yyGetParser->RequireDebugLevel($<str>3);
              }
              ;

UnittestCondition: dp_UNITTEST
                 | dp_UNITTEST dp_PARENSTART Identifier dp_PARENEND
                 ;

EndCondition: /*empty*/
            {
              yyGetParser->PopScope();
            }
            ;

Specification: VersionSpecification
             | DebugSpecification
             ;

VersionSpecification: dp_VERSION dp_EQUAL Identifier dp_SEMICOL
                    {
                      yyGetParser->DeclareVersion($<str>3);
                    }
                    | dp_VERSION dp_EQUAL dp_INTLITERAL dp_SEMICOL
                    {
                      yyGetParser->DeclareVersionLevel($<str>3);
                    }
                    ;

DebugSpecification: dp_DEBUG dp_EQUAL Identifier dp_SEMICOL
                  {
                    yyGetParser->DeclareDebug($<str>3);
                  }
                  | dp_DEBUG dp_EQUAL dp_INTLITERAL dp_SEMICOL
                  {
                    yyGetParser->DeclareDebugLevel($<str>3);
                  }
                  ;

Identifier: dp_NAME
          ;

%%
/* End of grammar */
