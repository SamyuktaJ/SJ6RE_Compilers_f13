/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include <iostream>

#include <string.h>
#include <string>

class Type : public Node 
{
  protected:
    char *typeName;
//
virtual void print(std::ostream &out) const { out << typeName;}

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
//
virtual Type *GetElemType() { return this; }
    virtual const char *GetTypeName() { return typeName; }
    virtual bool HasSameType(Type *t);
    virtual void CheckTypeError() {}
    friend std::ostream& operator<<(std::ostream &out, Type *type) { if (type) type->print(out); return out; }
    
//    virtual void PrintToStream(std::std::ostream& out) { out << typeName; }
//    friend std::std::ostream& operator<<(std::std::ostream& out, Type *t) { t->PrintToStream(out); return out; }
//    virtual bool IsEquivalentTo(Type *other) { return this == other; }
};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    Decl *cachedDecl; // either class or inteface
    bool isError;
//
 virtual void print(std::ostream &out) const { out << id; }

    
  public:
    NamedType(Identifier *i);
//
 Identifier *GetID() { return id; }
    Type *GetElemType() { return this; }
    const char *GetTypeName() { if (id) return id->GetName(); else return NULL; }
    bool HasSameType(Type *nt);
    void CheckTypeError();
    
/*    void PrintToStream(std::std::ostream& out) { out << id; }
    void Check();
    Decl *GetDeclForType();
    bool IsInterface();
    bool IsClass();
    Identifier *GetId() { return id; }
    bool IsEquivalentTo(Type *other);
*/
};

class ArrayType : public Type 
{
  protected:
    Type *elemType;
//
 virtual void print(std::ostream &out) const { out << elemType; }
  public:
    ArrayType(yyltype loc, Type *elemType);
//
Type *GetElemType() { return elemType; }
    const char *GetTypeName();
    bool HasSameType(Type *at);
    void CheckTypeError();
    
/*    void PrintToStream(std::std::ostream& out) { out << elemType << "[]"; }
    void Check();
    bool IsEquivalentTo(Type *other);
*/
};

 
#endif
