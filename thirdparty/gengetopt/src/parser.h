/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TOK_PACKAGE = 258,
     TOK_VERSION = 259,
     TOK_OPTION = 260,
     TOK_DEFGROUP = 261,
     TOK_GROUPOPTION = 262,
     TOK_YES = 263,
     TOK_NO = 264,
     TOK_ON = 265,
     TOK_OFF = 266,
     TOK_FLAG = 267,
     TOK_PURPOSE = 268,
     TOK_DESCRIPTION = 269,
     TOK_USAGE = 270,
     TOK_DEFAULT = 271,
     TOK_GROUP = 272,
     TOK_GROUPDESC = 273,
     TOK_MULTIPLE = 274,
     TOK_ARGOPTIONAL = 275,
     TOK_TYPESTR = 276,
     TOK_SECTION = 277,
     TOK_SECTIONDESC = 278,
     TOK_TEXT = 279,
     TOK_ARGS = 280,
     TOK_VALUES = 281,
     TOK_HIDDEN = 282,
     TOK_DEPENDON = 283,
     TOK_STRING = 284,
     TOK_MLSTRING = 285,
     TOK_CHAR = 286,
     TOK_ARGTYPE = 287,
     TOK_SIZE = 288
   };
#endif
/* Tokens.  */
#define TOK_PACKAGE 258
#define TOK_VERSION 259
#define TOK_OPTION 260
#define TOK_DEFGROUP 261
#define TOK_GROUPOPTION 262
#define TOK_YES 263
#define TOK_NO 264
#define TOK_ON 265
#define TOK_OFF 266
#define TOK_FLAG 267
#define TOK_PURPOSE 268
#define TOK_DESCRIPTION 269
#define TOK_USAGE 270
#define TOK_DEFAULT 271
#define TOK_GROUP 272
#define TOK_GROUPDESC 273
#define TOK_MULTIPLE 274
#define TOK_ARGOPTIONAL 275
#define TOK_TYPESTR 276
#define TOK_SECTION 277
#define TOK_SECTIONDESC 278
#define TOK_TEXT 279
#define TOK_ARGS 280
#define TOK_VALUES 281
#define TOK_HIDDEN 282
#define TOK_DEPENDON 283
#define TOK_STRING 284
#define TOK_MLSTRING 285
#define TOK_CHAR 286
#define TOK_ARGTYPE 287
#define TOK_SIZE 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 118 "parser.yy"
{
    char   *str;
    char    chr;
    int	    argtype;
    int	    boolean;
    class AcceptedValues *ValueList;
    struct gengetopt_option *gengetopt_option;
    struct multiple_size *multiple_size;
}
/* Line 1489 of yacc.c.  */
#line 125 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
