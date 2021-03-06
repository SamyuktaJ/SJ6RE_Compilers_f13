/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 *
 * pp3: You will need to extend the Type classes to implement
 * the type system and rules for type equivalency and compatibility.
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include <iostream>
#include "errors.h"

class Type : public Node 
{
  protected:
    char *typeName;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
//new
Type() : Node() {}
    
    virtual void PrintToStream(std::ostream& out) { out << typeName; }
//    friend std::ostream& operator<<(std::ostream& out, Type *t) { t->PrintToStream(out); return out; }
 friend std::ostream& operator<<(std::ostream& out, Type *t) { t->PrintToStream(out); return out; }
    virtual bool IsEqualTo(Type *other) { return this == other; }

//new
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
    
    void PrintToStream(std::ostream& out) { out << id; }
    bool IsEquivalentTo(Type *other);
    bool IsEqualTo(Type *other);
    void ReportNotDeclaredIdentifier(reasonT reason);

    const char* Name() { return id->Name(); }
    bool IsPrimitive() { return false; }
    Identifier* GetId() { return id;}

};

class ArrayType : public Type 
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    ArrayType(Type *elemType);//new

    void PrintToStream(std::ostream& out) { out << elemType << "[]"; }
   
    void ReportNotDeclaredIdentifier(reasonT reason);
    bool IsEqualTo(Type *other);
    bool IsEquivalentTo(Type *other);

    const char* Name() { return elemType->Name(); }
    bool IsPrimitive() { return false; }

    Type* GetElemType() { return elemType; }
};

 
#endif
