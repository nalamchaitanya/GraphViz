#include <stdio.h>
#include <stdlib.h>
#include "Interpreter.h"
#include "Graph.h"
extern Context *context;

void StmtExecFn(Context* context,Statement* stmt)
{
    addEdge(stmt->s1->gnode,stmt->s2->gnode,stmt->graph);
    stmt->next->execFn(context,stmt->next);
    return;
}

void IfExecFn(Context* context,Statement* stmt);

void ForExecFn(Context* context,Statement* stmt);

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
            sy->node = node;
            context->index++;
    	}
        else
        {
            sy = checkSymbol(name,context);
        }
    }
    else
    {
        sy = checkSymbol(name,context);
        if(sy->name==NULL)
        {
            sy->type = 1;
            sy->valid = 1;
            sy->name = name;
            sy->node = NULL;
            context->index++;
        }
    }
    return sy;
}

Symbol* checkSymbol(char* name,Context *context)
{
    int i =0;
	while(i<context->index)
	{
		if(strcmp(context->symbols[i].name,name)!=0)
		{
			i++;
			continue;
		}
		else
			break;
	}
	return context->symbols+i;
}
