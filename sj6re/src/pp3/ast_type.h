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
#include "errors.h"
using namespace std;

class Type : public Node
{
  protected:
    char *typeName;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type() : Node() {}
    Type(const char *str);

    virtual void PrintToStream(ostream& out) { out << typeName; }
    friend ostream& operator<<(ostream& out, Type *t) { t->PrintToStream(out); return out; }
    virtual bool IsEqualTo(Type *other) { return this == other; }
    virtual bool IsEquivalentTo(Type *other);
    virtual void ReportNotDeclaredIdentifier(reasonT reason) { return; }

    virtual const char* Name() { return typeName; }
    virtual bool IsPrimitive() { return true; }
};

class NamedType : public Type
{
  protected:
    Identifier *id;

  public:
    NamedType(Identifier *i);

    void PrintToStream(ostream& out) { out << id; }
    void ReportNotDeclaredIdentifier(reasonT reason);
    bool IsEqualTo(Type *other);
    bool IsEquivalentTo(Type *other);

    const char* Name() { return id->Name(); }
    bool IsPrimitive() { return false; }
    Identifier* GetId() { return id; }
};

class ArrayType : public Type
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    ArrayType(Type *elemType);

    void PrintToStream(ostream& out) { out << elemType << "[]"; }
    void ReportNotDeclaredIdentifier(reasonT reason);
    bool IsEqualTo(Type *other);
    bool IsEquivalentTo(Type *other);

    const char* Name() { return elemType->Name(); }
    bool IsPrimitive() { return false; }

    Type* GetElemType() { return elemType; }
};

#endif
