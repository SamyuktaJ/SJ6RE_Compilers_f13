/*
 * File: ast.h
 * ----------- 
 * This file defines the abstract base class Node and the concrete 
 * Identifier and Error node subclasses that are used through the tree as 
 * leaf nodes. A parse tree is a hierarchical collection of ast nodes (or, 
 * more correctly, of instances of concrete subclassses such as VarDecl,
 * ForStmt, and AssignExpr).
 */

#ifndef _H_ast
#define _H_ast

#include <stdlib.h>   // for NULL
#include "location.h"
#include <iostream>
using namespace std;

class Scope;//new

class Node  {
  protected:
    yyltype *location;
    Node *parent;
    Scope *scope;//new

  public:
    Node(yyltype loc);
    Node();
    virtual ~Node() {}

    Scope *GetScope()	     { return scope;}
	//new GetScope
    yyltype *GetLocation()   { return location; }
    void SetParent(Node *p)  { parent = p; }
    Node *GetParent()        { return parent; }
};

class Identifier : public Node 
{
  protected:
    char *name;

  public:
    Identifier(yyltype loc, const char *name);
    friend ostream& operator<<(ostream& out, Identifier *id) { return out << id->name; }
    //bool operator==(const Identifier &rhs);
    const char* Name() { return name; }
};

// This node class is designed to represent a portion of the tree that 
// encountered syntax errors during parsing. The partial completed tree
// is discarded along with the states being popped, and an instance of
// the Error class can stand in as the placeholder in the parse tree
// when your parser can continue after an error.
class Error : public Node
{
  public:
    Error() : Node() {}
};

#endif
