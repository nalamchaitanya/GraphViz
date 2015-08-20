#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

//Creates a new Graph.
Graph* createGraph(char* relation)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->relation = relation;
	graph->arr = (GNode*)malloc(sizeof(GNode)*100);
	graph->index = 0;
	return graph;
}

//Gets a node for given name
GNode* getNode(char* name,Graph* graph)
{
	GNode* node = checkInArray(graph,name);
	if(node->name==NULL)
	{
		node = createNode(name,graph);
	}
	return node;
}

//Add a new Edge to graph
void addEdge(GNode* node1,GNode* node2,Graph* graph)
{
	if(checkInNeigh(node1,node2->name)==NULL)
	{
		node1->neighbours[node1->length]=node2;
		node1->length++;
	}
	if(checkInNeigh(node2,node1->name)==NULL)
	{
		node2->neighbours[node2->length]=node1;
		node2->length++;
	}
	return;
}

GNode* createNode(char* name,Graph *graph)
{
	GNode* node;
	node = graph->arr+graph->index;
	node->name = name;
	node->neighbours = (GNode**)malloc(sizeof(GNode*)*100);
	node->length = 0;
	node->check = 0;
	graph->index++;
	return node;
}


//Check whether a name in Array
GNode* checkInArray(Graph *graph,char *name)
{
	int i =0;
	while(i<graph->index)
	{
		if(strcmp(graph->arr[i].name,name)!=0)
		{
			i++;
			continue;
		}
		else
			break;
	}
	return graph->arr+i;
}


//Check whether a name in neighbours.
GNode* checkInNeigh(GNode *node,char *name)
{
	int i = 0;
	GNode **arr = node->neighbours;
	while(i<node->length)
	{
		if(strcmp(arr[i]->name,name)!=0)
		{
			i++;
			continue;
		}
		else
			break;
	}
	return arr[i];
}

int isRelation(Graph *graph,char *name1,char *name2)
{
	int i;
	GNode *node1 = checkInArray(graph,name1);
	if(checkInNeigh(node1,name2)!=NULL)
		return 1;
	if(strcmp(graph->relation,"friendof")!=0)
	{
		node1->check = 1;
		for(i=0;i<node1->length;i++)
		{
			if(node1->neighbours[i]->check==0)
			{
				if(isRelation(graph,node1->neighbours[i]->name,name2)==1)
				{
					node1->check = 0;
					return 1;
				}
			}
		}
		node1->check = 0;
	}
	return 0;
}

void printGraph(Graph *graph)
{
	int i,j;
	for(i=0;i<graph->index;i++)
	{
		for(j=i+1;j<graph->index;j++)
		{
			if(isRelation(graph,graph->arr[i].name,graph->arr[j].name)==1)
				printf("%s\n",constructStr(graph->arr[i].name,graph->relation,graph->arr[j].name));
		}
	}
	return;
}

void printNode(GNode *node,char *relation)
{
	int i;
	char *str;
	for(i=0;i<node->length;i++)
	{
		if(node->neighbours[i]->check!=1)
			printf("%s\n",constructStr(node->name,relation,node->neighbours[i]->name));
	}
	node->check = 1;
	return;
}

char* constructStr(char *name1,char *relation,char *name2)
{
	char* str = (char*)malloc(sizeof(char)*100);
	str[0]='\0';
	strcat(str,name1);
	strcat(str," -- ");
	strcat(str,name2);
	strcat(str,"[label=\"");
	strcat(str,relation);
	strcat(str,"\"];");
	//printf("%s\n",str );
	return str;
}

GNode** getList(GNode* node,Graph* graph,int* len)
{
	GNode** list = (GNode**)malloc(sizeof(GNode)*100);
	int i;
	*len = 0;
	for(i=0;i<graph->index;i++)
	{
		if(strcmp(node->name,graph->arr[i].name)!=0)
		{
			if(isRelation(graph,node->name,graph->arr[i].name)==1)
			{
				list[*len] = graph->arr+i;
				(*len)++;
			}
		}
	}
	return list;
}
