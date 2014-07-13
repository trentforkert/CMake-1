/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         ddeps_yyparse
#define yylex           ddeps_yylex
#define yyerror         ddeps_yyerror
#define yylval          ddeps_yylval
#define yychar          ddeps_yychar
#define yydebug         ddeps_yydebug
#define yynerrs         ddeps_yynerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "ddepsParser.y"

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
#define ddeps_yyerror(x) \
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


/* Line 268 of yacc.c  */
#line 137 "ddepsParser.cxx"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     dp_SHEBANG = 258,
     dp_COLON = 259,
     dp_COMMA = 260,
     dp_CURLYEND = 261,
     dp_CURLYSTART = 262,
     dp_DOT = 263,
     dp_EQUAL = 264,
     dp_PARENEND = 265,
     dp_PARENSTART = 266,
     dp_SEMICOL = 267,
     dp_EXCLAIM = 268,
     dp_STRINGLITERAL = 269,
     dp_INTLITERAL = 270,
     dp_NAME = 271,
     dp_DEBUG = 272,
     dp_VERSION = 273,
     dp_IMPORT = 274,
     dp_UNITTEST = 275,
     dp_PUBLIC = 276,
     dp_PRIVATE = 277,
     dp_PACKAGE = 278,
     dp_PROTECTED = 279,
     dp_TEMPLATE = 280,
     dp_CLASS = 281,
     dp_INTERFACE = 282,
     dp_STRUCT = 283,
     dp_UNION = 284,
     dp_IF = 285,
     dp_MODULE = 286
   };
#endif
/* Tokens.  */
#define dp_SHEBANG 258
#define dp_COLON 259
#define dp_COMMA 260
#define dp_CURLYEND 261
#define dp_CURLYSTART 262
#define dp_DOT 263
#define dp_EQUAL 264
#define dp_PARENEND 265
#define dp_PARENSTART 266
#define dp_SEMICOL 267
#define dp_EXCLAIM 268
#define dp_STRINGLITERAL 269
#define dp_INTLITERAL 270
#define dp_NAME 271
#define dp_DEBUG 272
#define dp_VERSION 273
#define dp_IMPORT 274
#define dp_UNITTEST 275
#define dp_PUBLIC 276
#define dp_PRIVATE 277
#define dp_PACKAGE 278
#define dp_PROTECTED 279
#define dp_TEMPLATE 280
#define dp_CLASS 281
#define dp_INTERFACE 282
#define dp_STRUCT 283
#define dp_UNION 284
#define dp_IF 285
#define dp_MODULE 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 240 "ddepsParser.cxx"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
       && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
   || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)        \
    do                  \
      {                  \
  YYSIZE_T yynewbytes;            \
  YYCOPY (&yyptr->Stack_alloc, Stack, yysize);      \
  Stack = &yyptr->Stack_alloc;          \
  yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
  yyptr += yynewbytes / sizeof (*yyptr);        \
      }                  \
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)    \
      do          \
  {          \
    YYSIZE_T yyi;        \
    for (yyi = 0; yyi < (Count); yyi++)  \
      (To)[yyi] = (From)[yyi];    \
  }          \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   492

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  156
/* YYNRULES -- Number of states.  */
#define YYNSTATES  223

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)            \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    13,    15,    17,    20,
      23,    25,    27,    29,    31,    33,    35,    37,    39,    41,
      43,    45,    47,    51,    53,    57,    59,    61,    63,    65,
      67,    73,    78,    84,    90,    95,   101,   107,   112,   116,
     118,   120,   125,   129,   133,   136,   140,   144,   147,   152,
     156,   160,   164,   168,   171,   174,   177,   179,   183,   184,
     186,   190,   194,   196,   200,   201,   204,   207,   211,   214,
     216,   218,   220,   222,   223,   227,   229,   231,   232,   234,
     236,   238,   240,   242,   244,   246,   248,   250,   252,   254,
     256,   260,   265,   267,   269,   271,   273,   275,   277,   279,
     282,   285,   288,   291,   293,   295,   297,   299,   301,   303,
     305,   307,   309,   311,   313,   315,   317,   319,   323,   326,
     330,   333,   335,   337,   341,   343,   347,   351,   353,   357,
     359,   363,   365,   367,   371,   373,   377,   381,   384,   386,
     388,   390,   395,   400,   405,   407,   412,   417,   419,   424,
     425,   427,   429,   434,   439,   444,   449
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      33,     0,    -1,     3,    34,    -1,    34,    -1,    37,    35,
      -1,    37,    -1,    35,    -1,    36,    -1,    35,    36,    -1,
      35,    66,    -1,    67,    -1,    58,    -1,    68,    -1,    83,
      -1,    89,    -1,    61,    -1,    48,    -1,    50,    -1,    49,
      -1,    51,    -1,    39,    -1,    65,    -1,    31,    38,    12,
      -1,    92,    -1,    38,     8,    92,    -1,    40,    -1,    41,
      -1,    42,    -1,    43,    -1,    44,    -1,    25,    92,    73,
      52,    45,    -1,    25,    92,    73,    45,    -1,    26,    92,
      73,    57,    45,    -1,    28,    92,    73,    52,    45,    -1,
      28,    92,    73,    45,    -1,    27,    92,    73,    57,    45,
      -1,    29,    92,    73,    52,    45,    -1,    29,    92,    73,
      45,    -1,    46,    64,    47,    -1,     7,    -1,     6,    -1,
      26,    92,    53,    61,    -1,    26,    92,    61,    -1,    26,
      92,    12,    -1,    26,    61,    -1,    28,    92,    61,    -1,
      28,    92,    12,    -1,    28,    61,    -1,    27,    92,    53,
      61,    -1,    27,    92,    61,    -1,    27,    92,    12,    -1,
      29,    92,    61,    -1,    29,    92,    12,    -1,    29,    61,
      -1,    30,    73,    -1,     4,    54,    -1,    55,    -1,    54,
       5,    55,    -1,    -1,    56,    -1,    56,    13,    73,    -1,
      56,    13,    92,    -1,    92,    -1,    56,     8,    92,    -1,
      -1,    57,    52,    -1,    57,    53,    -1,    59,    36,    60,
      -1,    59,     4,    -1,    21,    -1,    22,    -1,    24,    -1,
      23,    -1,    -1,    62,    64,    63,    -1,     7,    -1,     6,
      -1,    -1,    35,    -1,    16,    -1,    12,    -1,     8,    -1,
       9,    -1,     5,    -1,    30,    -1,    13,    -1,    73,    -1,
      15,    -1,     4,    -1,    14,    -1,    19,    75,    12,    -1,
      19,    11,    69,    10,    -1,    14,    -1,    71,    -1,    14,
      -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,    70,
      14,    -1,    70,    72,    -1,    70,    73,    -1,    70,    74,
      -1,    16,    -1,    12,    -1,     8,    -1,     9,    -1,     5,
      -1,    28,    -1,    26,    -1,    27,    -1,    29,    -1,     4,
      -1,    13,    -1,    19,    -1,    30,    -1,    15,    -1,    11,
      70,    10,    -1,    11,    10,    -1,     7,    70,     6,    -1,
       7,     6,    -1,    76,    -1,    77,    -1,    76,     5,    75,
      -1,    81,    -1,    80,     9,    81,    -1,    76,     4,    78,
      -1,    79,    -1,    79,     5,    78,    -1,    92,    -1,    92,
       9,    92,    -1,    92,    -1,    92,    -1,    82,     8,    92,
      -1,    92,    -1,    82,     8,    92,    -1,    84,    36,    88,
      -1,    84,     4,    -1,    85,    -1,    86,    -1,    87,    -1,
      18,    11,    92,    10,    -1,    18,    11,    20,    10,    -1,
      18,    11,    15,    10,    -1,    17,    -1,    17,    11,    92,
      10,    -1,    17,    11,    15,    10,    -1,    20,    -1,    20,
      11,    92,    10,    -1,    -1,    90,    -1,    91,    -1,    18,
       9,    92,    12,    -1,    18,     9,    15,    12,    -1,    17,
       9,    92,    12,    -1,    17,     9,    15,    12,    -1,    16,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   106,   109,   110,   111,   114,   115,   116,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   133,   139,   143,   149,   150,   151,   152,   153,
     156,   157,   160,   163,   164,   167,   170,   171,   173,   176,
     183,   188,   189,   190,   191,   194,   195,   196,   199,   200,
     201,   204,   205,   206,   209,   212,   215,   216,   217,   220,
     221,   222,   225,   226,   229,   230,   231,   234,   235,   241,
     246,   251,   256,   264,   269,   272,   279,   285,   286,   289,
     293,   297,   298,   302,   306,   307,   308,   312,   315,   318,
     321,   322,   328,   333,   339,   340,   343,   344,   345,   346,
     347,   348,   349,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   368,   369,   372,
     373,   376,   377,   378,   381,   385,   391,   394,   395,   398,
     399,   402,   405,   409,   415,   419,   425,   426,   432,   433,
     434,   441,   446,   451,   459,   464,   469,   476,   477,   481,
     486,   487,   490,   494,   500,   504,   510
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"#!\"", "\":\"", "\",\"", "\"}\"",
  "\"{\"", "\".\"", "\"=\"", "\")\"", "\"(\"", "\";\"", "\"!\"",
  "\"string\"", "\"integer\"", "\"identifer\"", "\"debug\"", "\"version\"",
  "\"import\"", "\"unittest\"", "\"public\"", "\"private\"", "\"package\"",
  "\"protected\"", "\"template\"", "\"class\"", "\"interface\"",
  "\"struct\"", "\"union\"", "\"if\"", "\"module\"", "$accept", "File",
  "Module", "Declarations", "Declaration", "ModuleDeclaration",
  "ModuleName", "TemplateDeclaration", "PlainTemplate", "ClassTemplate",
  "StructTemplate", "InterfaceTemplate", "UnionTemplate",
  "TemplateContent", "TemplateBlockStart", "TemplateBlockEnd",
  "NonTemplateClass", "NonTemplateStruct", "NonTemplateInterface",
  "NonTemplateUnion", "Constraint", "SuperClasses", "ClassNames",
  "ClassName", "ClassFullyQualifiedName", "ClassAddendums",
  "ProtectionDeclaration", "Protection", "EndProtection", "Block",
  "BlockStart", "BlockEnd", "BlockContent", "Garbage", "SecondaryGarbage",
  "Literal", "ImportDeclaration", "TextImport", "Expression",
  "ComplicatedExpression", "ExprGarbage", "ParenExpr", "CurlyExpr",
  "ImportList", "Import", "ImportBindings", "ImportBindList", "ImportBind",
  "ModuleAliasIdentifier", "ModuleFullyQualifiedName", "Packages",
  "ConditionalDeclaration", "Condition", "VersionCondition",
  "DebugCondition", "UnittestCondition", "EndCondition", "Specification",
  "VersionSpecification", "DebugSpecification", "Identifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    33,    34,    34,    34,    35,    35,    35,
      36,    36,    36,    36,    36,    36,    36,    36,    36,    36,
      36,    36,    37,    38,    38,    39,    39,    39,    39,    39,
      40,    40,    41,    42,    42,    43,    44,    44,    45,    46,
      47,    48,    48,    48,    48,    49,    49,    49,    50,    50,
      50,    51,    51,    51,    52,    53,    54,    54,    54,    55,
      55,    55,    56,    56,    57,    57,    57,    58,    58,    59,
      59,    59,    59,    60,    61,    62,    63,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    66,    67,
      68,    68,    69,    69,    70,    70,    71,    71,    71,    71,
      71,    71,    71,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    73,    73,    74,
      74,    75,    75,    75,    76,    76,    77,    78,    78,    79,
      79,    80,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    85,    85,    85,    86,    86,    86,    87,    87,    88,
      89,    89,    90,    90,    91,    91,    92
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       5,     4,     5,     5,     4,     5,     5,     4,     3,     1,
       1,     4,     3,     3,     2,     3,     3,     2,     4,     3,
       3,     3,     3,     2,     2,     2,     1,     3,     0,     1,
       3,     3,     1,     3,     0,     2,     2,     3,     2,     1,
       1,     1,     1,     0,     3,     1,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       2,     1,     1,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     1,     3,     1,     3,     3,     2,     1,     1,
       1,     4,     4,     4,     1,     4,     4,     1,     4,     0,
       1,     1,     4,     4,     4,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    83,    75,    81,    82,     0,    80,    85,    89,
      87,    79,   144,     0,     0,   147,    69,    70,    72,    71,
       0,     0,     0,     0,     0,    84,     0,     0,     3,     6,
       7,     5,    20,    25,    26,    27,    28,    29,    16,    18,
      17,    19,    11,     0,    15,    77,    21,    10,    12,    86,
      13,     0,   138,   139,   140,    14,   150,   151,     2,   112,
     107,     0,   105,   106,   118,   104,   113,    94,   116,   103,
     114,   109,   110,   108,   111,   115,     0,    95,    96,    97,
      98,     0,     0,     0,     0,     0,   156,     0,   121,   122,
       0,   124,     0,   132,     0,     0,    44,     0,     0,    47,
       0,    53,     0,     0,    23,     1,    88,     8,     9,     4,
      68,    73,    78,     0,   137,   149,   120,     0,   117,    99,
     100,   101,   102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,     0,     0,    95,    90,     0,     0,     0,
       0,     0,     0,    58,    43,     0,    42,    64,    50,     0,
      49,    64,    46,    45,     0,    52,    51,     0,     0,    22,
      67,    76,    74,   136,   119,   155,   154,   146,   145,   153,
     152,   143,   142,   141,    91,   126,   127,   129,   123,   125,
     132,   133,   148,    39,     0,    31,    77,     0,    55,    56,
      59,    62,    41,     0,    48,     0,    34,     0,    37,     0,
      24,     0,     0,    54,     0,    30,     0,     0,     0,    32,
      65,    66,    35,    33,    36,   128,   130,    40,    38,    57,
      63,    60,    61
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    27,    28,    29,    30,    31,   103,    32,    33,    34,
      35,    36,    37,   185,   186,   218,    38,    39,    40,    41,
     210,   211,   188,   189,   190,   193,    42,    43,   160,    44,
      45,   162,   113,    46,   108,    47,    48,   133,    76,    77,
      78,    49,    80,    87,    88,    89,   175,   176,    90,    91,
      92,    50,    51,    52,    53,    54,   163,    55,    56,    57,
      93
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -142
static const yytype_int16 yypact[] =
{
     192,   219,  -142,  -142,  -142,  -142,   136,  -142,  -142,  -142,
    -142,  -142,    36,    39,    17,    50,  -142,  -142,  -142,  -142,
      51,    16,    51,    16,    16,  -142,    51,    84,  -142,   247,
    -142,   462,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,   274,  -142,   462,  -142,  -142,  -142,  -142,
    -142,   301,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,   328,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,   355,  -142,  -142,  -142,
    -142,     9,    44,    58,    23,   409,  -142,    59,    76,  -142,
      78,  -142,    85,    94,    51,    88,  -142,    65,    93,  -142,
      15,  -142,    71,    45,  -142,  -142,  -142,  -142,  -142,   247,
    -142,  -142,   247,    95,  -142,  -142,  -142,   382,  -142,  -142,
    -142,  -142,  -142,    98,   100,    96,    97,   101,   102,   105,
     106,   107,   109,   112,   436,   113,  -142,    51,    51,    51,
      51,   115,    14,    51,  -142,   119,  -142,  -142,  -142,   119,
    -142,  -142,  -142,  -142,    14,  -142,  -142,    14,    51,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,   122,   120,  -142,  -142,
     123,   124,  -142,  -142,    88,  -142,   462,   127,   125,  -142,
      22,  -142,  -142,    10,  -142,    10,  -142,   127,  -142,   127,
    -142,    51,    51,  -142,   129,  -142,    51,    51,    25,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -142,  -142,   135,   -25,   -14,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -141,  -142,  -142,  -142,  -142,  -142,  -142,
    -123,    11,  -142,   -64,  -142,   -13,  -142,  -142,  -142,   -12,
    -142,  -142,   -33,  -142,  -142,  -142,  -142,  -142,   -43,    69,
     -68,    -6,   -66,    18,  -142,  -142,   -44,  -142,  -142,    19,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
     -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -136
static const yytype_int16 yytable[] =
{
      79,    95,    97,    98,   100,   102,   109,   104,   120,    96,
     122,    99,   101,   196,   143,   107,   198,   183,   117,   187,
     112,   183,     3,     3,   123,    86,     6,   152,    85,   111,
     207,   197,    86,    86,   199,   208,     6,   115,   129,    86,
     184,    86,   134,   130,   184,    81,   205,    82,    83,   120,
      84,   122,   209,   158,   212,    79,   213,   159,   214,   125,
      86,    94,   124,   126,   128,   131,   120,    86,   122,   143,
     121,   136,     3,   127,    86,   141,     6,   144,     3,    79,
     137,   138,     6,   155,   105,   146,   150,   139,   153,   142,
     156,   147,   151,   140,   154,   107,   157,   143,   107,     6,
       3,   161,  -134,  -131,     6,   148,   167,   168,   145,   149,
     165,   121,   166,   169,   170,   171,   172,   173,   177,   -92,
     180,   181,   174,   -93,   191,   182,     3,   201,   121,   202,
     206,  -134,  -135,   192,   183,   217,    58,   194,   195,   200,
      59,    60,   219,    61,    62,    63,    64,     6,    65,    66,
      67,    68,    69,   204,   135,    70,   178,   215,   179,     0,
       0,   112,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   203,     0,
       0,     0,   177,   216,     0,     0,     0,   191,   220,   222,
       0,     0,     0,     0,     0,     1,     0,     2,     0,     3,
       4,     5,   221,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,     2,     0,     3,     4,     5,     0,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,   106,     2,     0,     3,     4,     5,     0,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,   110,     2,
       0,     3,     4,     5,     0,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,   114,     2,     0,     3,     4,
       5,     0,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    59,    60,   116,    61,    62,    63,     0,     6,
      65,    66,    67,    68,    69,     0,     0,    70,     0,     0,
       0,     0,     0,     0,    71,    72,    73,    74,    75,    59,
      60,     0,    61,    62,    63,   118,     6,    65,    66,   119,
      68,    69,     0,     0,    70,     0,     0,     0,     0,     0,
       0,    71,    72,    73,    74,    75,    59,    60,   164,    61,
      62,    63,     0,     6,    65,    66,   119,    68,    69,     0,
       0,    70,     0,     0,     0,     0,     0,     0,    71,    72,
      73,    74,    75,    59,    60,     0,    61,    62,    63,     0,
       6,    65,    66,   132,    68,    69,     0,     0,    70,     0,
       0,     0,     0,     0,     0,    71,    72,    73,    74,    75,
      59,    60,     0,    61,    62,    63,     0,     6,    65,    66,
     119,    68,    69,     0,     0,    70,     0,     0,     0,     0,
       0,     0,    71,    72,    73,    74,    75,     2,     0,     3,
       4,     5,     0,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-142))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       6,    20,    21,    22,    23,    24,    31,    26,    76,    21,
      76,    23,    24,   154,     4,    29,   157,     7,    61,   142,
      45,     7,     7,     7,    15,    16,    11,    12,    11,    43,
       8,   154,    16,    16,   157,    13,    11,    51,    15,    16,
      30,    16,    85,    20,    30,     9,   187,    11,     9,   117,
      11,   117,   193,     8,   195,    61,   197,    12,   199,    15,
      16,    11,    81,    82,    83,    84,   134,    16,   134,     4,
      76,    12,     7,    15,    16,    94,    11,    12,     7,    85,
       4,     5,    11,    12,     0,    97,    98,     9,   100,    95,
     102,    97,    98,     8,   100,   109,   102,     4,   112,    11,
       7,     6,     8,     9,    11,    12,    10,    10,    97,    98,
      12,   117,    12,    12,    12,    10,    10,    10,   137,    10,
     139,   140,    10,    10,   143,    10,     7,     5,   134,     9,
       5,     8,     8,   145,     7,     6,     1,   149,   151,   158,
       4,     5,   206,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,   186,    85,    19,   138,   201,   139,    -1,
      -1,   186,    26,    27,    28,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,    -1,
      -1,    -1,   201,   202,    -1,    -1,    -1,   206,   207,   208,
      -1,    -1,    -1,    -1,    -1,     3,    -1,     5,    -1,     7,
       8,     9,   208,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,     5,    -1,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,     4,     5,    -1,     7,     8,     9,    -1,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,     4,     5,
      -1,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     4,     5,    -1,     7,     8,
       9,    -1,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    16,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,     4,     5,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      28,    29,    30,     4,     5,    -1,     7,     8,     9,    -1,
      11,    12,    13,    14,    15,    16,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
       4,     5,    -1,     7,     8,     9,    -1,    11,    12,    13,
      14,    15,    16,    -1,    -1,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,     5,    -1,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    33,    34,    35,
      36,    37,    39,    40,    41,    42,    43,    44,    48,    49,
      50,    51,    58,    59,    61,    62,    65,    67,    68,    73,
      83,    84,    85,    86,    87,    89,    90,    91,    34,     4,
       5,     7,     8,     9,    10,    12,    13,    14,    15,    16,
      19,    26,    27,    28,    29,    30,    70,    71,    72,    73,
      74,     9,    11,     9,    11,    11,    16,    75,    76,    77,
      80,    81,    82,    92,    11,    92,    61,    92,    92,    61,
      92,    61,    92,    38,    92,     0,     4,    36,    66,    35,
       4,    36,    35,    64,     4,    36,     6,    70,    10,    14,
      72,    73,    74,    15,    92,    15,    92,    15,    92,    15,
      20,    92,    14,    69,    70,    71,    12,     4,     5,     9,
       8,    92,    73,     4,    12,    53,    61,    73,    12,    53,
      61,    73,    12,    61,    73,    12,    61,    73,     8,    12,
      60,     6,    63,    88,     6,    12,    12,    10,    10,    12,
      12,    10,    10,    10,    10,    78,    79,    92,    75,    81,
      92,    92,    10,     7,    30,    45,    46,    52,    54,    55,
      56,    92,    61,    57,    61,    57,    45,    52,    45,    52,
      92,     5,     9,    73,    64,    45,     5,     8,    13,    45,
      52,    53,    45,    45,    45,    78,    92,     6,    47,    55,
      92,    73,    92
};

#define yyerrok    (yyerrstatus = 0)
#define yyclearin  (yychar = YYEMPTY)
#define YYEMPTY    (-2)
#define YYEOF    0

#define YYACCEPT  goto yyacceptlab
#define YYABORT    goto yyabortlab
#define YYERROR    goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL    goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)          \
do                \
  if (yychar == YYEMPTY && yylen == 1)        \
    {                \
      yychar = (Token);            \
      yylval = (Value);            \
      YYPOPSTACK (1);            \
      goto yybackup;            \
    }                \
  else                \
    {                \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;              \
    }                \
while (YYID (0))


#define YYTERROR  1
#define YYERRCODE  256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)        \
    do                  \
      if (YYID (N))                                                    \
  {                \
    (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;  \
    (Current).first_column = YYRHSLOC (Rhs, 1).first_column;  \
    (Current).last_line    = YYRHSLOC (Rhs, N).last_line;    \
    (Current).last_column  = YYRHSLOC (Rhs, N).last_column;  \
  }                \
      else                \
  {                \
    (Current).first_line   = (Current).last_line   =    \
      YYRHSLOC (Rhs, 0).last_line;        \
    (Current).first_column = (Current).last_column =    \
      YYRHSLOC (Rhs, 0).last_column;        \
  }                \
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)      \
do {            \
  if (yydebug)          \
    YYFPRINTF Args;        \
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)        \
do {                    \
  if (yydebug)                  \
    {                    \
      YYFPRINTF (stderr, "%s ", Title);            \
      yy_symbol_print (stderr,              \
      Type, Value); \
      YYFPRINTF (stderr, "\n");              \
    }                    \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
  break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)        \
do {                \
  if (yydebug)              \
    yy_stack_print ((Bottom), (Top));        \
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
       yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
           &(yyvsp[(yyi + 1) - (yynrhs)])
                      );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)    \
do {          \
  if (yydebug)        \
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef  YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
  switch (*++yyp)
    {
    case '\'':
    case ',':
      goto do_not_strip_quotes;

    case '\\':
      if (*++yyp != '\\')
        goto do_not_strip_quotes;
      /* Fall through.  */
    default:
      if (yyres)
        yyres[yyn] = *yyp;
      yyn++;
      break;

    case '"':
      if (yyres)
        yyres[yyn] = '\0';
      return yyn;
    }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
  break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
  /* Give user a chance to reallocate the stack.  Use copies of
     these so that the &'s don't force the real ones into
     memory.  */
  YYSTYPE *yyvs1 = yyvs;
  yytype_int16 *yyss1 = yyss;

  /* Each stack pointer address is followed by the size of the
     data in use in that stack, in bytes.  This used to be a
     conditional around just the two extra args, but that might
     be undefined if yyoverflow is a macro.  */
  yyoverflow (YY_("memory exhausted"),
        &yyss1, yysize * sizeof (*yyssp),
        &yyvs1, yysize * sizeof (*yyvsp),
        &yystacksize);

  yyss = yyss1;
  yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
  goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
  yystacksize = YYMAXDEPTH;

      {
  yytype_int16 *yyss1 = yyss;
  union yyalloc *yyptr =
    (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
  if (! yyptr)
    goto yyexhaustedlab;
  YYSTACK_RELOCATE (yyss_alloc, yyss);
  YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
  if (yyss1 != yyssa)
    YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
      (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
  YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 22:

/* Line 1806 of yacc.c  */
#line 134 "ddepsParser.y"
    {
                   yyGetParser->SetModuleName();
                 }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 140 "ddepsParser.y"
    {
            yyGetParser->AppendModuleComponent((yyvsp[(1) - (1)].str));
          }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 144 "ddepsParser.y"
    {
            yyGetParser->AppendModuleComponent((yyvsp[(3) - (3)].str));
          }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 177 "ddepsParser.y"
    {
                    yyGetParser->PushScope();
                    yyGetParser->SetTemplate();
                  }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 184 "ddepsParser.y"
    {
                  yyGetParser->PopScope();
                }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 236 "ddepsParser.y"
    {
                       yyGetParser->SetEndlessScope();
                     }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 242 "ddepsParser.y"
    {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(true);
          }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 247 "ddepsParser.y"
    {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(false);
          }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 252 "ddepsParser.y"
    {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(false);
          }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 257 "ddepsParser.y"
    {
            yyGetParser->PushScope();
            yyGetParser->SetPublic(false);
          }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 264 "ddepsParser.y"
    {
              yyGetParser->PopScope();
             }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 273 "ddepsParser.y"
    {
            yyGetParser->PushScope();
            yyGetParser->MaybeFunctionTemplate();
          }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 280 "ddepsParser.y"
    {
          yyGetParser->PopScope();
        }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 290 "ddepsParser.y"
    {
         yyGetParser->BeginPossibleFunctionTemplate();
       }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 294 "ddepsParser.y"
    {
         yyGetParser->CancelFunctionTemplate();
       }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 299 "ddepsParser.y"
    {
        yyGetParser->CancelFunctionTemplate();
       }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 303 "ddepsParser.y"
    {
        yyGetParser->CancelFunctionTemplate();
       }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 309 "ddepsParser.y"
    {
        yyGetParser->HitUnclaimedParenExpr();
       }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 323 "ddepsParser.y"
    {
                  yyGetParser->AcceptTextImportIfValid();
                 }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 329 "ddepsParser.y"
    {
            // Propose match
            yyGetParser->AddPossibleTextImport((yyvsp[(1) - (1)].str));
          }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 334 "ddepsParser.y"
    {
            yyGetParser->InvalidateTextImport();
          }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 382 "ddepsParser.y"
    {
        yyGetParser->AddModuleImport();
      }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 386 "ddepsParser.y"
    {
        yyGetParser->AddModuleImport();
      }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 406 "ddepsParser.y"
    {
                          yyGetParser->AppendModuleComponent((yyvsp[(1) - (1)].str));
                        }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 410 "ddepsParser.y"
    {
                          yyGetParser->AppendModuleComponent((yyvsp[(3) - (3)].str));
                        }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 416 "ddepsParser.y"
    {
          yyGetParser->AppendModuleComponent((yyvsp[(1) - (1)].str));
        }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 420 "ddepsParser.y"
    {
          yyGetParser->AppendModuleComponent((yyvsp[(3) - (3)].str));
        }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 427 "ddepsParser.y"
    {
                        yyGetParser->SetEndlessScope();
                      }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 435 "ddepsParser.y"
    {
           yyGetParser->PushScope();
           yyGetParser->RequireVersion("unittest");
         }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 442 "ddepsParser.y"
    {
                  yyGetParser->PushScope();
                  yyGetParser->RequireVersion((yyvsp[(3) - (4)].str));
                }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 447 "ddepsParser.y"
    {
                  yyGetParser->PushScope();
                  yyGetParser->RequireVersion("unittest");
                }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 452 "ddepsParser.y"
    {
                  yyGetParser->PushScope();
                  yyGetParser->RequireVersionLevel((yyvsp[(3) - (4)].str));
                }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 460 "ddepsParser.y"
    {
                yyGetParser->PushScope();
                yyGetParser->RequireDebug("");
              }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 465 "ddepsParser.y"
    {
                yyGetParser->PushScope();
                yyGetParser->RequireDebug((yyvsp[(3) - (4)].str));
              }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 470 "ddepsParser.y"
    {
                yyGetParser->PushScope();
                yyGetParser->RequireDebugLevel((yyvsp[(3) - (4)].str));
              }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 481 "ddepsParser.y"
    {
              yyGetParser->PopScope();
            }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 491 "ddepsParser.y"
    {
                      yyGetParser->DeclareVersion((yyvsp[(3) - (4)].str));
                    }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 495 "ddepsParser.y"
    {
                      yyGetParser->DeclareVersionLevel((yyvsp[(3) - (4)].str));
                    }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 501 "ddepsParser.y"
    {
                    yyGetParser->DeclareDebug((yyvsp[(3) - (4)].str));
                  }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 505 "ddepsParser.y"
    {
                    yyGetParser->DeclareDebugLevel((yyvsp[(3) - (4)].str));
                  }
    break;



/* Line 1806 of yacc.c  */
#line 2129 "ddepsParser.cxx"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
   error, discard it.  */

      if (yychar <= YYEOF)
  {
    /* Return failure if at end of input.  */
    if (yychar == YYEOF)
      YYABORT;
  }
      else
  {
    yydestruct ("Error: discarding",
          yytoken, &yylval);
    yychar = YYEMPTY;
  }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;  /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
  {
    yyn += YYTERROR;
    if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
      {
        yyn = yytable[yyn];
        if (0 < yyn)
    break;
      }
  }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
  YYABORT;


      yydestruct ("Error: popping",
      yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
      yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 513 "ddepsParser.y"

/* End of grammar */

