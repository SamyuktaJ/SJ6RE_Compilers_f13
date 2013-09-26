%{
#include <stdio.h>
#include "symtab.h"
%}

%union { int i; node *n; double d;}

%token GO TURN VAR JUMP
%token FOR STEP TO DO
%token COPEN CCLOSE
%token SIN COS SQRT
%token <d> FLOAT
%token <n> ID               
%token <i> NUMBER       
%token SEMICOLON PLUS MINUS TIMES DIV OPEN CLOSE ASSIGN

%token REPEAT WHILE PROCEDURE IF THEN ELSE
%token COMP_OP_lt COMP_OP_le COMP_OP_gt COMP_OP_ge COMP_OP_ne COMP_OP_eq
%token BEG_BLOCK END_BLOCK
%token BEG_LIST END_LIST
%token COMMA LOGIC_OP KEYWORD


%type <n> decl
%type <n> decllist

%%
program: head decllist stmtlist tail;

head: { printf("%%!PS Adobe\n"
               "\n"
	       "newpath \n 0 0 moveto\n"
	       );
      };

tail: { printf("stroke\n"); };

decllist:;
decllist: decllist decl;

decl: VAR ID SEMICOLON { printf("/tlt%s 0 def\n",$2->symbol);} ;


stmtlist: ;
stmtlist: stmtlist stmt ;

stmt: ID ASSIGN expr SEMICOLON {printf("/tlt%s exch store\n",$1->symbol);} ;
stmt: GO expr SEMICOLON {printf("0 rlineto\n");};
stmt: JUMP expr SEMICOLON {printf("0 rmoveto\n");};
stmt: TURN expr SEMICOLON {printf("rotate\n");};

stmt: FOR ID ASSIGN expr 
          STEP expr
	  TO expr
	  DO {printf("{ /tlt%s exch store\n",$2->symbol);} 
	     stmt {printf("} for\n");};

stmt: COPEN stmtlist CCLOSE;	 
stmt: IF OPEN catomic CLOSE then exec_array {printf("if \n closepath ");};
stmt: IF OPEN catomic CLOSE then exec_array ELSE exec_array { printf("ifelse \n closepath ");};

expr: expr PLUS term { printf("add ");};
expr: expr MINUS term { printf("sub ");};
expr: term;

term: term TIMES factor { printf("mul ");};
term: term DIV factor { printf("div ");};
term: factor;

factor: MINUS atomic { printf("neg ");};
factor: PLUS atomic;
factor: SIN factor { printf("sin ");};
factor: COS factor { printf("cos ");};
factor: SQRT factor { printf("sqrt ");};
factor: atomic;


atomic: OPEN expr CLOSE;
atomic: NUMBER {printf("%d ",$1);};
atomic: FLOAT {printf("%f ",$1);};
atomic: ID {printf("tlt%s ", $1->symbol);};

condition: expr COMP_OP_lt expr {printf("lt");};
condition: expr COMP_OP_le expr {printf("le");};
condition: expr COMP_OP_gt expr {printf("gt");};
condition: expr COMP_OP_ge expr {printf("ge");};
condition: expr COMP_OP_ne expr {printf("ne");};
condition: expr COMP_OP_eq expr {printf("eq");};
catomic: OPEN condition CLOSE;
catomic: condition;

then: THEN;
then:;
exec_array: beg_block stmtlist end_block;
beg_block: BEG_BLOCK {printf(" { ");};
end_block: END_BLOCK {printf(" } ");};

stmt: WHILE OPEN catomic CLOSE exec_array {printf("loop ");};
stmt: PROCEDURE ID proc {printf("/proc%s",$2->symbol);};
proc: exec_array {printf("def ");};

%%
int yyerror(char *msg)
{  fprintf(stderr,"Error: %s\n",msg);
   return 0;
}

int main(void)
{   yyparse();
    return 0;
}

