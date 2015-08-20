#include <stdio.h>
#include <stdlib.h>
#include "Interpreter.h"

extern Context *context;
extern Graph** mainGraph;

void synchroniseVariable(char* name,GNode* node,Context* context)
{
    int i,index;
    for(i=0;i<context->index;i++)
    {
        if(strcmp(name,context->symbols[i].name)==0)
        {
            index = sgn(strcmp(context->symbols[i].relation,"friendof"))+1;
            context->symbols[i].gnode = getNode(node->name,mainGraph[index]);
        }
    }
    return;
}

void StmtExecFn(Context* context,Statement* stmt)
{
    addEdge(stmt->s1->gnode,stmt->s2->gnode,stmt->graph);
    if(stmt->next!=NULL)
        stmt->next->execFn(context,stmt->next);
    return;
}

void IfExecFn(Context* context,Statement* stmt)
{
    if(isRelation(stmt->graph,stmt->s1->gnode->name,stmt->s2->gnode->name)==1)
    {
        if(stmt->block!=NULL)
            stmt->block->execFn(context,stmt->block);
    }
    if(stmt->next!=NULL)
        stmt->next->execFn(context,stmt->next);
    return;
}

void ForExecFn(Context* context,Statement* stmt)
{
    int len;
    GNode** list = getList(stmt->s2->gnode,stmt->graph,&len);
    int i;
    for(i=0;i<len;i++)
    {
        synchroniseVariable(stmt->s1->name,list[i],context);
        stmt->block->execFn(context,stmt->block);
    }
    if(stmt->next!=NULL)
        stmt->next->execFn(context,stmt->next);
    return;
}

Statement* createIfStatement(char* name1,char* name2,Statement* block,Graph* graph)
{
    Statement *stmt = (Statement*)malloc(sizeof(Statement));
    stmt->s1 = getSymbol(name1,graph);
    stmt->s2 = getSymbol(name2,graph);
    stmt->graph = graph;
    stmt->block = block;
    stmt->type = 1;
    stmt->execFn = (ExecFn)(IfExecFn);
    return stmt;
}

Statement* createForStatement(char* name1,char* name2,Statement* block,Graph* graph)
{
    Statement *stmt = (Statement*)malloc(sizeof(Statement));
    stmt->s1 = getSymbol(name1,graph);
    stmt->s2 = getSymbol(name2,graph);
    stmt->graph = graph;
    stmt->block = block;
    stmt->type = 2;
    stmt->execFn = (ExecFn)(ForExecFn);
    return stmt;
}

Statement* createStatement(char* name1,char* name2,Graph* graph)
{
    Statement *stmt = (Statement*)malloc(sizeof(Statement));
    stmt->s1 = getSymbol(name1,graph);
    stmt->s2 = getSymbol(name2,graph);
    stmt->graph = graph;
    stmt->type = 0;
    stmt->execFn = (ExecFn)(StmtExecFn);
    return stmt;
}

Symbol* getSymbol(char* name, Graph* graph)
{
    Symbol *sy;
    if(name[0]!='$')
    {
        GNode* node = checkInArray(graph,name);
    	if(node->name==NULL)
    	{
    		node = createNode(name,graph);
            sy = context->symbols+context->index;
            sy->type = 0;
            sy->valid = 1;
            sy->name = name;
            sy->gnode = node;
            sy->relation = graph->relation;
            context->index++;
    	}
        else
        {
            sy = checkSymbol(name,graph,context);
        }
    }
    else
    {
        sy = checkSymbol(name,graph,context);
        if(sy->name==NULL)
        {
            sy->type = 1;
            sy->valid = 1;
            sy->name = name;
            sy->gnode = NULL;
            sy->relation= graph->relation;
            context->index++;
        }
    }
    return sy;
}

Symbol* checkSymbol(char* name,Graph* graph,Context *context)
{
    int i =0;
	while(i<context->index)
	{
		if(strcmp(context->symbols[i].name,name)!=0
            ||strcmp(context->symbols[i].relation,graph->relation)!=0)
		{
			i++;
			continue;
		}
		else
			break;
	}
	return context->symbols+i;
}
