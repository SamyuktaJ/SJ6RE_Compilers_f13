/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     GO = 258,
     TURN = 259,
     VAR = 260,
     JUMP = 261,
     FOR = 262,
     STEP = 263,
     TO = 264,
     DO = 265,
     COPEN = 266,
     CCLOSE = 267,
     SIN = 268,
     COS = 269,
     SQRT = 270,
     FLOAT = 271,
     ID = 272,
     NUMBER = 273,
     SEMICOLON = 274,
     PLUS = 275,
     MINUS = 276,
     TIMES = 277,
     DIV = 278,
     OPEN = 279,
     CLOSE = 280,
     ASSIGN = 281,
     REPEAT = 282,
     WHILE = 283,
     PROCEDURE = 284,
     IF = 285,
     THEN = 286,
     ELSE = 287,
     COMP_OP_lt = 288,
     COMP_OP_le = 289,
     COMP_OP_gt = 290,
     COMP_OP_ge = 291,
     COMP_OP_ne = 292,
     COMP_OP_eq = 293,
     BEG_BLOCK = 294,
     END_BLOCK = 295,
     BEG_LIST = 296,
     END_LIST = 297,
     COMMA = 298,
     LOGIC_OP = 299,
     KEYWORD = 300
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 6 "turtle-sj6re.y"
 int i; node *n; double d;


/* Line 2068 of yacc.c  */
#line 99 "turtle-sj6re.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


