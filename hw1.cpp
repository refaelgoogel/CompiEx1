
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "tokens.hpp"
using namespace std;

void showToken(const char * name)
{
	if (name == "ERROR"){

		cout << "----------------THIS IS AN ERROR---------------" << endl;

	}

    printf("%d %s %s\n",yylineno, name, yytext);
	
}

int main(){

	int token;

	while(token = yylex()) {

		switch(token) {

			case INT:
				showToken("INT");
				break;
			case BYTE:
				showToken("BYTE");
				break;
			case B:
				showToken("B");
				break;
			case BOOL:
				showToken("BOOL");
				break;
			case AND:
				showToken("AND");
				break;
			case OR:
				showToken("OR");
				break;
			case NOT:
				showToken("NOT");
				break;
			case TRUE:
				showToken("TRUE");
				break;
			case FALSE:
				showToken("FALSE");
				break;
			case RETURN:
				showToken("RETURN");
				break;
			case IF:
				showToken("IF");
				break;
			case ELSE:
				showToken("ELSE");
				break;
			case WHILE:
				showToken("WHILE");
				break;
			case BREAK:
				showToken("BREAK");
				break;
			case CONTINUE:
				showToken("CONTINUE");
				break;
			case SC:
				showToken("SC");
				break;
			case LPAREN:
				showToken("LPAREN");
				break;
			case RPAREN:
				showToken("RPAREN");
				break;
			case LBRACE:
				showToken("LBRACE");
				break;
			case RBRACE:
				showToken("RBRACE");
				break;
			case ASSIGN:
				showToken("ASSIGN");
				break;
			case RELOP:
				showToken("RELOP");
				break;
			case BINOP:
				showToken("BINOP");
				break;
			case COMMENT:
				showToken("COMMENT");
				break;
			case ID:
				showToken("ID");
				break;
			case NUM:
				showToken("NUM");
				break;
			case STRING:
				showToken("STRING");
				break;
			case UNCLOSED_STRING:
				showToken("UNCLOSED_STRING");
				break;
			case UNDEFINED_ESCAPE_SEQUENCE:
				showToken("UNDEFINED_ESCAPE_SEQUENCE");
				break;
			case UNDEFINED_ESCAPE_SEQUENCE_HEX:
				showToken("UNDEFINED_ESCAPE_SEQUENCE_HEX");
				break;
			case ERROR:
				showToken("ERROR");
				break;
			default:
				showToken("UNKNOWN");
				break;
		}
		
	}

	return 0;
}