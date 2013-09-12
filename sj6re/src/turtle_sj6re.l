
%{
#include "symtab.h"
#include "token.h"
#include "math.h"
%}

COMP_OP ["<"|">"|"<="|">="|"!="|"=="]
LOGIC_OP ["&"|"&&"|"AND"|"|"|"||"|"OR"|"!"|"NOT"]
ID [a-z][a-z0-9]*
KEYWORDS_ONE_ARG ["forward"|"fd"|"back"|"bk"|"left"|"lt"|"right"|"rt"|"setx"|"sety"|"setheading"|"seth"|"label"|"setlabelheight"|"setwidth"|"setcolor"]
ws [[:space:]]*[\t]*
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

[KEYWORDS_ONE_ARG][[:space:]]*[0-9]+	printf("legal DRAW COMMAND, %s \t",yytext);

REPEAT[ws][0-9]+[\[][[ws].]*[\]]	printf("REPEAT");

PROCEDURE[ws][ID][ws][\(][ws][[ID]*[ws][","]*[ws]]*[ws][\)]	printf("Procedure");

IF		{printf("IF");//return IF;
		}
THEN		{printf("THEN");//return THEN;
		}
ELSE		{printf("ELSE");//return ELSE;
		}

;               return SEMICOLON;
\+              return PLUS;
-               return MINUS;
\*              return TIMES;
\/              return DIV;
\(              return OPEN;
\)              return CLOSE;
=               return ASSIGN;


ID             { yylval.n = lookup(yytext); 
                  if (yylval.n==NULL)
		    yylval.n = insert(yytext);
                  return ID;
		}
    
[0-9]+\.[0-9]+  yylval.d = atof(yytext);  return FLOAT;
[0-9]+          yylval.i = atoi(yytext);  return NUMBER;

.               fprintf(stderr,"Unexpected character %c (%2X)\n",yytext[0],yytext[0]);

%%
