
/* Tokens.  */
#define GO 258
#define TURN 259
#define VAR 260
#define JUMP 261
#define FOR 262
#define STEP 263
#define TO 264
#define DO 265
#define COPEN 266
#define CCLOSE 267
#define SIN 268
#define COS 269
#define SQRT 270
#define FLOAT 271
#define ID 272
#define NUMBER 273
#define SEMICOLON 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define DIV 278
#define OPEN 279
#define CLOSE 280
#define ASSIGN 281

#define KEYWORD 300
#define IF 301
#define THEN 302
#define ELSE 303
#define PROCEDURE 304
#define REPEAT 305
#define WHILE 306

#define COMP_OP 350
#define COMMA 351
#define LOGIC_OP 352
#define BEG_BLOCK 353
#define END_BLOCK 354
#define BEG_LIST 355
#define END_LIST 356
typedef union YYSTYPE
{ int i; node *n; double d;}
        YYSTYPE;
YYSTYPE yylval;

