
%{
#include "symtab.h"
#include "token.h"
#include "math.h"
%}

LOGIC_OP ["&"|"&&"|"AND"|"|"|"||"|"OR"|"!"|"NOT"]
ID [a-z][a-z0-9]*
KEYWORDS_ONE_ARG [FORWARD|FD|BACK|"BK"|"LEFT"|"LT"|"RIGHT"|RT|"SETX"|"SETY"|"SETHEADING"|"SETH"|"LABEL"|"SETLABELHEIGHT"|"SETWIDTH"|"SETCOLOR"]
ws {[:space:]}*{\t}*
%%

\/\/.*          ;
[[:space:]]     ;

GO              return GO;
TURN            return TURN; 
VAR             return VAR;
JUMP            return JUMP;
FOR             return FOR;
STEP            return STEP;
TO              return TO;
DO              return DO;
BEGIN           return COPEN;
END             return CCLOSE;

sin             return SIN;
cos             return COS;
sqrt            return SQRT;

"FORWARD"|"FD"|"BACK"|"BK"|"LEFT"|"LT"|"RIGHT"|"RT"|"SETX"|"SETY"|"SETHEADING"|"SETH"|"LABEL"|"SETLABELHEIGHT"|"SETWIDTH"|"SETCOLOR"	{//printf("DRAWING KEYWORD \n");
			return KEYWORD;
		}

"PENUP"|"PU"|"PENDOWN"|"PD"|"CLEARSCREEN"|"CS"|"HIDETURTLE"|"HT"|"SHOWTURTLE"|"ST"|"HOME"|"PRINT"|"POS"|"HEADING"	{ 	//printf("TURTLE CONTROL and MANIPULATION \n");
			return KEYWORD;
		}

"TOWARDS LIST"|"RANDOM"|"ARC"|"FILL"|"FILLED" { 	//printf("OTHER COMMANDS \n");
			return KEYWORD;
		}


"&"|"&&"|"AND"|"|"|"||"|"OR"|"!"|"NOT"	{	printf("LOGIC OPERATOR \n");
			return LOGIC_OP;
		}

REPEAT		{	//printf("REPEAT\n");
			return REPEAT;
		}

WHILE		{	//printf("WHILE\n");
			return WHILE;
		}

PROCEDURE	{	//printf("PROCEDURE\n");
			return PROCEDURE;
		}

IF		{	//printf("IF\n");
			return IF;
		}
THEN		{	//printf("THEN\n");
			return THEN;
		}
ELSE		{	//printf("ELSE\n");
			return ELSE;
		}

"<"|"<="|">"|">="|"!="|"=="	{
			printf("Comparison Operator, %s \t \n", yytext);
			return COMP_OP;
		}
\{		{//printf("Begin Block \n");
		return BEG_BLOCK;}
"["		{//printf("Begin List \n");
		return BEG_LIST;}
\}		{//printf("End Block \n");
		return END_BLOCK;}
"]"		{//printf("End List \n"); 
		return END_LIST;}
","		{//printf("COMMA \n");
		return COMMA;}

;               return SEMICOLON;
\+              return PLUS;
-               return MINUS;
\*              return TIMES;
\/              return DIV;
\(              return OPEN;
\)              return CLOSE;
=               return ASSIGN;


[a-z][a-z0-9]*             { yylval.n = lookup(yytext); 
                  if (yylval.n==NULL)
		    yylval.n = insert(yytext);
		printf("ID \n");
                  return ID;
		}
    
[0-9]+\.[0-9]+  yylval.d = atof(yytext);  return FLOAT;
[0-9]+          yylval.i = atoi(yytext);  return NUMBER;

.               fprintf(stderr,"Unexpected character %c (%2X)\n",yytext[0],yytext[0]);

%%
