/* File: ast.cc
 * ------------
 */

#include "ast.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> // strdup
#include <stdio.h>  // printf
#include "errors.h"
#include "scope.h"

#include "ast_stmt.h"
Node::Node(yyltype loc) {
    location = new yyltype(loc);
    parent = NULL;
    nodeScope = NULL;//remove?
}

Node::Node() {
    location = NULL;
    parent = NULL;
    nodeScope = NULL;//?
}

/*Decl *Node::FindDecl(Identifier *idToFind, lookup l) {
    Decl *mine;
    if (!nodeScope) PrepareScope();
    if (nodeScope && (mine = nodeScope->Lookup(idToFind)))
        return mine;
    if (l == kDeep && parent)
        return parent->FindDecl(idToFind, l);
    return NULL;
}*/
	 
Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
    name = strdup(n);
    cached = NULL;
} 
	 


// look for declaration from inner most scope to global scope
Decl *Identifier::CheckIdDecl() {
  Decl *decl = NULL;
  Node *parent = this->GetParent();
  while (parent)
    {
      Hashtable<Decl*> *sym_table = parent->GetSymTable();
      if (sym_table != NULL)
	{
	  if ((decl = sym_table->Lookup(this->name)) != NULL)
	    return decl;
	}
      parent = parent->GetParent();
    }

  decl = Program::sym_table->Lookup(this->name);

  return decl;
}

// look for declaration in the provided scope
Decl *Identifier::CheckIdDecl(Hashtable<Decl*> *sym_table, const char *name)
{
  Decl *decl = NULL;
  if (sym_table)
    decl = sym_table->Lookup(name);
  return decl;
}

