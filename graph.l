letter		[a-z]
digit		[0-9]

%{
    #include <stdlib.h>
    #include <string.h>
    #include "Graph.h"
    #include "Interpreter.h"
    #include "y.tab.h"
    extern YYSTYPE yylval;
    void yyerror(char *);
%}

%%

	/* if condition */
("if")			{return IF;}

("endif")			{return ENDIF;}

	/* for loop */
("foreach")		{return FOREACH;}

("endforeach")	{return ENDFOREACH;}

($(letter)+)	{
                    yylval.string = strdup(yytext);
                    return VARIABLE;
				}

	/* relations */
("friendof"|"classmateof"|"roommateof")	{
                                        yylval.number = sgn(strcmp(yytext,"friendof"))+1;
                                        return RELATION;
									}

	/* matches any word */
({letter})+		{
					yylval.string = strdup(yytext);
                    return NAME;
				}

	/* ignore whitespace */
[ \t\n]			;

	/* gives error */
.				yyerror("Invalid");

%%

int yywrap(void)
{
	return 1;
}

int sgn(int a)
{
    if(a<0)
        return -1;
    else if(a>0)
        return 1;
    else return 0;
}
