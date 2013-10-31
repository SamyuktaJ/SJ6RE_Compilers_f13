/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
//------------------------------

int Scope::AddDecl(Decl *d) {
    Decl *lookup = table->Lookup(d->Name());

    if (lookup != NULL) {
            ReportError::DeclConflict(d, lookup);
            return 1;
    }

    table->Enter(d->Name(), d);
    return 0;
}

ostream& operator<<(ostream& out, Scope *s) {
    out << "========== Scope ==========" << std::endl;
    Iterator<Decl*> iter = s->table->GetIterator();
    Decl *d;
    while ((d = iter.GetNextValue()) != NULL)
        out << d << std::endl;
    return out;
}

Scope *Program::gScope = new Scope();


//------------------------------
Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    BuildScope();

    for (int i = 0, n = decls->NumElements(); i < n; ++i)
        decls->Nth(i)->Check();
}

void Program::BuildScope() {
    for (int i = 0, n = decls->NumElements(); i < n; ++i)
        gScope->AddDecl(decls->Nth(i));

    for (int i = 0, n = decls->NumElements(); i < n; ++i)
        decls->Nth(i)->BuildScope(gScope);
}

void Stmt::BuildScope(Scope *parent) {
    scope->SetParent(parent);
}


/*void Program::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    printf("\n");
}*/

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}
void StmtBlock::BuildScope(Scope *parent) {
    scope->SetParent(parent);

    for (int i = 0, n = decls->NumElements(); i < n; ++i)
        scope->AddDecl(decls->Nth(i));

    for (int i = 0, n = decls->NumElements(); i < n; ++i)
        decls->Nth(i)->BuildScope(scope);

    for (int i = 0, n = stmts->NumElements(); i < n; ++i)
        stmts->Nth(i)->BuildScope(scope);
}

void StmtBlock::Check() {
    for (int i = 0, n = decls->NumElements(); i < n; ++i)
        decls->Nth(i)->Check();

    for (int i = 0, n = stmts->NumElements(); i < n; ++i)
        stmts->Nth(i)->Check();
}

/*void StmtBlock::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}*/

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

void ConditionalStmt::BuildScope(Scope *parent) {
    scope->SetParent(parent);

    test->BuildScope(scope);
    body->BuildScope(scope);
}

void ConditionalStmt::Check() {
    test->Check();
    body->Check();

    if (!test->GetType()->IsEquivalentTo(Type::boolType))
        ReportError::TestNotBoolean(test);
}

void LoopStmt::BuildScope(Scope *parent) {
    scope->SetParent(parent);
    scope->SetLoopStmt(this);

    test->BuildScope(scope);
    body->BuildScope(scope);
}
//--------------------
ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

/*void ForStmt::PrintChildren(int indentLevel) {
    init->Print(indentLevel+1, "(init) ");
    test->Print(indentLevel+1, "(test) ");
    step->Print(indentLevel+1, "(step) ");
    body->Print(indentLevel+1, "(body) ");
}*/

/*void WhileStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(body) ");
}*/

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::BuildScope(Scope *parent) {
    scope->SetParent(parent);

    test->BuildScope(scope);
    body->BuildScope(scope);

    if (elseBody != NULL)
        elseBody->BuildScope(scope);
}

void IfStmt::Check() {
    test->Check();
    body->Check();

    if (!test->GetType()->IsEquivalentTo(Type::boolType))
        ReportError::TestNotBoolean(test);

    if (elseBody != NULL)
        elseBody->Check();
}


/*void IfStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(then) ");
    if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}*/


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

/*void ReturnStmt::PrintChildren(int indentLevel) {
    expr->Print(indentLevel+1);
}*/
void ReturnStmt::BuildScope(Scope *parent) {
    scope->SetParent(parent);

    expr->BuildScope(scope);
}

void ReturnStmt::Check() {
    expr->Check();

    FnDecl *d = NULL;
    Scope *s = scope;
    while (s != NULL) {
        if ((d = s->GetFnDecl()) != NULL)
            break;

        s = s->GetParent();
    }

    if (d == NULL) {
        ReportError::Formatted(location,
                               "return is only allowed inside a function");
        return;
    }

    Type *expected = d->GetReturnType();
    Type *given = expr->GetType();

    if (!given->IsEquivalentTo(expected))
        ReportError::ReturnMismatch(this, given, expected);
}


  
void BreakStmt::Check() {
    Scope *s = scope;
    while (s != NULL) {
        if (s->GetLoopStmt() != NULL)
            return;

        s = s->GetParent();
    }

    ReportError::BreakOutsideLoop(this);
}


PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}
void PrintStmt::BuildScope(Scope *parent) {
    scope->SetParent(parent);

    for (int i = 0, n = args->NumElements(); i < n; ++i)
        args->Nth(i)->BuildScope(scope);
}

void PrintStmt::Check() {
    for (int i = 0, n = args->NumElements(); i < n; ++i) {
        Type *given = args->Nth(i)->GetType();

        if (!(given->IsEquivalentTo(Type::intType) ||
              given->IsEquivalentTo(Type::boolType) ||
              given->IsEquivalentTo(Type::stringType)))
            ReportError::PrintArgMismatch(args->Nth(i), i+1, given);
    }

    for (int i = 0, n = args->NumElements(); i < n; ++i)
        args->Nth(i)->Check();
}

/*void PrintStmt::PrintChildren(int indentLevel) {
    args->PrintAll(indentLevel+1, "(args) ");
}
*/
SwitchLabel::SwitchLabel(IntConstant *l, List<Stmt*> *s) {
    Assert(l != NULL && s != NULL);
    (label=l)->SetParent(this);
    (stmts=s)->SetParentAll(this);
}

SwitchLabel::SwitchLabel(List<Stmt*> *s) {
    Assert(s != NULL);
    label = NULL;
    (stmts=s)->SetParentAll(this);
}

/*void SwitchLabel::PrintChildren(int indentLevel) {
    if (label) label->Print(indentLevel+1);
    if (stmts) stmts->PrintAll(indentLevel+1);
}
*/
SwitchStmt::SwitchStmt(Expr *e, List<Case*> *c, Default *d) {
    Assert(e != NULL && c != NULL && c->NumElements() != 0 );
    (expr=e)->SetParent(this);
    (cases=c)->SetParentAll(this);
    def = d;
    if (def) def->SetParent(this);
}

//-----
void SwitchStmt::BuildScope(Scope *parent) {
    scope->SetParent(parent);

    test->BuildScope(scope);
    body->BuildScope(scope); 
//for (int i = 0, n = cases->NumElements(); i < n; ++i)
//        cases->Nth(i)->BuildScope(scope);

//also build and check for expr, cases and d?
}
//Odd errors
/*void SwitchStmt::Check() {
    test->Check();
    body->Check();

    if (!test->GetType()->IsEquivalentTo(Type::intType))
        ReportError::TestNotInteger(test);

    for (int i = 0, n = cases->NumElements(); i < n; ++i)
        cases->Nth(i)->Check();


}*/


/*void SwitchStmt::PrintChildren(int indentLevel) {
    if (expr) expr->Print(indentLevel+1);
    if (cases) cases->PrintAll(indentLevel+1);
    if (def) def->Print(indentLevel+1);
}
*/

