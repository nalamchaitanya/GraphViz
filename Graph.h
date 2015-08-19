/**
	Graph
**/

#include <stdio.h>
#include <stdlib.h>

#ifndef GRAPH_H
#define GRAPH_H

typedef struct _GNode GNode;

typedef struct _GNode
{
	char *name;
	GNode **neighbours;
	int length;
	int check;
};

typedef struct _Graph
{
	char* relation;
	GNode *arr;
	int index;
} Graph;

//Creates a new Graph
Graph* createGraph(char* relation);

//Gets a node for given name
GNode* getNode(char* name,Graph* graph);

//Add a new Node to graph
void addEdge(GNode* node1,GNode* node2,Graph* graph);

//Check whether a name in Array
GNode* checkInArray(Graph *graph,char *name);

//Check whether a name in neighbours.
GNode* checkInNeigh(GNode *node,char *name);

//Create a node.
GNode* createNode(char* name,Graph *graph);

//Prints the graph.
void printGraph(Graph *graph);

//checks is Relation or not.
int isRelation(Graph *graph,char *name1,char *name2);

// constructs string to put in table.
char* constructStr(char *name1,char *relation,char *name2);

#endif
