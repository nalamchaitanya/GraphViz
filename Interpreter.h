/*
    Nalam V S S Krishna Chaitanya
    Interpreter
*/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#ifndef INTERPRETER_H
#define INTERPRETER_H

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

typedef struct _Statement Statement;

typedef void (*ExecFn)(Context* context,Statement* st);


struct _Statement
{
    Symbol *s1;
    Symbol *s2;
    Graph* graph;
    Statement *next;
    Statement *block;
    int type;
    ExecFn  execFn;
};

void StmtExecFn(Context* context,Statement* stmt);

void IfExecFn(Context* context,Statement* stmt);

void ForExecFn(Context* context,Statement* stmt);

Statement* createStatement(char* name1,char* name2,Graph* graph);

Symbol* getSymbol(char* name, Graph* graph);

Symbol* checkSymbol(char* name,Context *context);

#endif
