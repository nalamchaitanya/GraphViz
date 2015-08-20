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
	Graph **mainGraph;
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
		statement program 											{$1->next=$2;$$ = $1;head = $$;}
		| IF NAME RELATION NAME program ENDIF program				{$$ = createIfStatement($2,$4,$5,mainGraph[$3]);$$->next = $7;}
		| IF VARIABLE RELATION NAME program ENDIF program			{$$ = createIfStatement($2,$4,$5,mainGraph[$3]);$$->next = $7;}
		| IF NAME RELATION VARIABLE program ENDIF program			{$$ = createIfStatement($2,$4,$5,mainGraph[$3]);$$->next = $7;}
		| FOREACH VARIABLE RELATION NAME program ENDFOREACH	program {$$ = createForStatement($2,$4,$5,mainGraph[$3]);$$->next = $7;}
		| FOREACH VARIABLE RELATION VARIABLE program ENDFOREACH program	{$$ = createForStatement($2,$4,$5,mainGraph[$3]);$$->next = $7;}
		|															{$$ = NULL;}
		;


statement:
		NAME RELATION NAME 			{ $$ = createStatement($1,$3,mainGraph[$2]);}
		| VARIABLE RELATION NAME	{ $$ = createStatement($1,$3,mainGraph[$2]);}
		| NAME RELATION VARIABLE	{ $$ = createStatement($1,$3,mainGraph[$2]);}
		| VARIABLE RELATION VARIABLE{ $$ = createStatement($1,$3,mainGraph[$2]);}
		;

%%


void yyerror(char *text)
{
	fprintf(stderr,"%s\n",text);
}

int main(int argc,char *argv[])
{
	yyin = fopen(argv[1],"r");
	mainGraph = (Graph**)malloc(sizeof(Graph*)*3);
	context = (Context*)malloc(sizeof(Context));
	context->symbols = (Symbol*)malloc(sizeof(Symbol)*100);
	context->index = 0;
	mainGraph[0] = createGraph("classmateof");
	mainGraph[1] = createGraph("friendof");
	mainGraph[2] = createGraph("roommateof");
	printf("graph\n{\n");
	yyparse();
	head->execFn(context,head);
	fclose(yyin);
	int i;
	for(i=0;i<3;i++)
	{
		printGraph(mainGraph[i]);
		printf("\n");
	}
	printf("}\n");
	return 0;
}
