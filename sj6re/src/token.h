
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

#define REPEAT 301
#define WHILE 302
#define PROCEDURE 303
#define IF 304
#define ELSE 305
#define THEN 306
#define COMP_OP_lt 307
#define COMP_OP_le 308
#define COMP_OP_gt 309
#define COMP_OP_ge 310
#define COMP_OP_ne 311 
#define COMP_OP_eq 312
#define BEG_BLOCK 313
#define END_BLOCK 314
#define BEG_LIST 315
#define END_LIST 316

#define COMMA 317
#define LOGIC_OP 318
#define PARAM 319
#define CALL 320
#define KEYWORD 330

typedef union YYSTYPE
{ int i; node *n; double d;}
        YYSTYPE;
extern YYSTYPE yylval;

