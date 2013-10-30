/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "list.h"

class Type;
class NamedType;
class Identifier;
class Stmt;

class Decl : public Node 
{
  protected:
    Identifier *id;
//new
 Scope *scope;
  
  public:
    Decl(Identifier *name);
friend ostream& operator<<(ostream& out, Decl *d) { return out << d->id; }

    virtual bool IsEquivalentTo(Decl *other);

    const char* Name() { return id->Name(); }
    Scope* GetScope() { return scope; }

    virtual void BuildScope(Scope *parent);
    virtual void Check() = 0;

};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);
//    const char *GetPrintNameForNode() { return "VarDecl"; }
//    void PrintChildren(int indentLevel);

bool IsEquivalentTo(Decl *other);

    Type* GetType() { return type; }
    void Check();

  private:
    void CheckType();

};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;

  public:
    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
//    const char *GetPrintNameForNode() { return "ClassDecl"; }
//    void PrintChildren(int indentLevel);
void BuildScope(Scope *parent);
    void Check();

    NamedType* GetType() { return new NamedType(id); }
    NamedType* GetExtends() { return extends; }
    List<NamedType*>* GetImplements() { return implements; }

  private:
    void CheckExtends();
    void CheckImplements();

    void CheckExtendedMembers(NamedType *extType);
    void CheckImplementedMembers(NamedType *impType);
    void CheckAgainstScope(Scope *other);
    void CheckImplementsInterfaces();

};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
//    const char *GetPrintNameForNode() { return "InterfaceDecl"; }
//    void PrintChildren(int indentLevel);
void BuildScope(Scope *parent);
    void Check();

    Type* GetType() { return new NamedType(id); }
    List<Decl*>* GetMembers() { return members; }

};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
//    const char *GetPrintNameForNode() { return "FnDecl"; }
//    void PrintChildren(int indentLevel);
bool IsEquivalentTo(Decl *other);

    Type* GetReturnType() { return returnType; }
    List<VarDecl*>* GetFormals() { return formals; }

    void BuildScope(Scope *parent);
    void Check();

};

#endif
