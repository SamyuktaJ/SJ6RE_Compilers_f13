/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"

#include "hashtable.h"

class Decl;
class VarDecl;
class Expr;

class IntConstant;
  
class Program : public Node
{
  protected:
     List<Decl*> *decls;
     
  public:
     Program(List<Decl*> *declList);
//     void Check();
void CheckStatements();
     void CheckDeclError();
     static Hashtable<Decl*> *sym_table; // global symbol table
//
};

class Stmt : public Node
{
  public:
     Stmt() : Node() {}
     Stmt(yyltype loc);// : Node(loc) {}
};

class StmtBlock : public Stmt 
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
    Hashtable<Decl*> *sym_table; // keep a symbol table for every local scope& not removing on scope exit

  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
//    void Check();
    void CheckStatements();
    void CheckDeclError();
    Hashtable<Decl*> *GetSymTable() { return sym_table; }
//
};

  
class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;
  
  public:
    ConditionalStmt(Expr *testExpr, Stmt *body);
  //  void Check();
void CheckStatements();
    void CheckDeclError();

//
};

class LoopStmt : public ConditionalStmt 
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
//
void CheckStatements();
};

class WhileStmt : public LoopStmt 
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
//
void CheckStatements();
};

class IfStmt : public ConditionalStmt 
{
  protected:
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
//    void Check();
void CheckStatements();
void CheckDeclError();
};

class BreakStmt : public Stmt 
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
//
void CheckStatements();
};

class ReturnStmt : public Stmt  
{
  protected:
    Expr *expr;
  
  public:
    ReturnStmt(yyltype loc, Expr *expr);
//
void CheckStatements();
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;
    
  public:
    PrintStmt(List<Expr*> *arguments);
//
void CheckStatements();
};


#endif
