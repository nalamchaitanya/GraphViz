%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include "Interpreter.h"
	#include "Graph.h"
	void yyerror(char *);
	int yylex(void);
	Statement* head;
	Context *context;
	Graph **graph;
	extern FILE *yyin;
	extern FILE *yyout;
%}

%union
{
	int number;
	char* string;
	Statement* stmt;
};

%token <string> NAME
%token <number> RELATION
%token <string> VARIABLE
%token IF ENDIF FOREACH ENDFOREACH
%type <stmt> statement
%type <stmt> program

%%

program:
		statement program 											{
																		$1->next=$2;
																		$$ = $1;
																		head = $$;
																	}
		| IF NAME RELATION NAME program ENDIF					{;}
		| FOREACH VARIABLE RELATION NAME program ENDFOREACH	{;}
		|	{$$=NULL;}
		;


statement:
		NAME RELATION NAME 			{ $$ = createStatement($1,$3,graph[$2]);}
		;

%%


void yyerror(char *text)
{
	fprintf(stderr,"%s\n",text);
}

int main(int argc,char *argv[])
{
	yyin = fopen(argv[1],"r");
	graph = (Graph**)malloc(sizeof(Graph*)*3);
	context = (Context*)malloc(sizeof(Context));
	context->symbols = (Symbol*)malloc(sizeof(Symbol)*100);
	context->index = 0;
	graph[0] = createGraph("classmateof");
	graph[1] = createGraph("friendof");
	graph[2] = createGraph("roommateof");
	printf("graph\n{\n");
	yyparse();
	while(head!=NULL)
	{
		head->execFn(context,head);
		head=head->next;
	}
	fclose(yyin);
	int i;
	for(i=0;i<3;i++)
	{
		printGraph(graph[i]);
		printf("\n");
	}
	printf("}\n");
	return 0;
}
