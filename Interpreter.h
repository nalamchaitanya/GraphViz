/*
    Nalam V S S Krishna Chaitanya
    Interpreter
*/

#ifndef INTERPRETER_H
#define INTERPRETER_H
typedef void (*ExecFn)(Context* context,Statement* st);

typedef struct _Symbol
{
    int type;
    int valid;
    char *name;
    GNode* gnode;
}Symbol;

typedef struct _Context
{
    Symbol* symbols;
    int index;
}Context;

typedef struct _Statement
{
    Symbol *s1;
    Symbol *s2;
    Graph* graph;
    Statement *next;
    Statement *block;
    int type;
    ExecFn  execFn;
}Statement;

void StmtExecFn(Context* context,Statement* stmt);

void IfExecFn(Context* context,Statement* stmt);

void ForExecFn(Context* context,Statement* stmt);

#endif
