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
//#include "errors.h"
#include "codegen.h"//new
using namespace std;

class Type : public Node
{
  protected:
    char *typeName;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
    Type() : Node() {}

    virtual const char* GetName() { return typeName; }

    virtual void PrintToStream(ostream& out) { out << typeName; }
    friend ostream& operator<<(ostream& out, Type *t) { t->PrintToStream(out); return out; }
    virtual bool IsEquivalentTo(Type *other) { return this == other; }
    virtual BuiltIn GetPrint();
};

class NamedType : public Type
{
  protected:
    Identifier *id;

  public:
    NamedType(Identifier *i);

    const char* GetName() { return id->GetName(); }

    void PrintToStream(ostream& out) { out << id; }
    BuiltIn GetPrint();
};

class ArrayType : public Type
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    ArrayType(Type *elemType);

    const char* GetName() { return elemType->GetName(); }

    void PrintToStream(ostream& out) { out << elemType << "[]"; }
    BuiltIn GetPrint();
};

#endif
