/*
    Nalam V S S Krishna Chaitanya
    Interpreter
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H
typedef void (*ExecFn)(Symbol* context,Statement* st);

typedef struct _Symbol
{
    int type;
    int valid;
    GNode* gnode;
}Symbol;

typedef struct _Statement
{
    Symbol *s1;
    Symbol *s2;
    int relation;
    Statement *next;
    Statement *block;
    int type;
    ExecFn  execFn;
}Statement;

void StmtExecFn(Symbol* context,Statement* stmt);

void IfExecFn(Symbol* context,Statement* stmt);

void ForExecFn(Symbol* context,Statement* stmt);

#endif
