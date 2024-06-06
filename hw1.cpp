#include <stdio.h>
#include <stdlib.h>
#include "tokens.hpp"

void showToken(const char * name)
{
    printf("<%d> <%s> <%s>\n",yylineno, name, yytext);
}

int main()
{
	int token;
	while(token = yylex()) {
		
		if (token == NUM){
			showToken("NUM");
		}
		
	}

	return 0;
}