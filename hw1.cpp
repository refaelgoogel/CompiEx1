<<<<<<< HEAD
/*#include "tokens.hpp"
=======
>>>>>>> 5121d70e8b511945cf301c06f4e54a31550efc3e

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "tokens.hpp"
using namespace std;

void showToken(const char * name)
{
<<<<<<< HEAD
	int token;
	while(token = yylex()) { 
=======
	if (name == "ERROR"){

		cout << "----------------THIS IS AN ERROR---------------" << endl;
>>>>>>> 5121d70e8b511945cf301c06f4e54a31550efc3e

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
}*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "tokens.hpp"
#include <sstream>

using namespace std;


void printStr();
void undefinedEscape();

void undefinedHex();

void showToken(const char * name)
{
	if (name == "ERROR"){

	//	cout << "----------------THIS IS AN ERROR---------------" << endl;

	}
    cout << yylineno << " " << name << " " << yytext <<endl;

    //printf("%d %s %s\n",yylineno, name, yytext);
	
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
            	cout << yylineno << " COMMENT //" <<endl;
				break;
			case ID:
				showToken("ID");
				break;
			case NUM:
				showToken("NUM");
				break;
			case STRING:
				printStr();
				break;
			case UNCLOSED_STRING:
				showToken("UNCLOSED_STRING");
				exit(0);
				break;
			case UNDEFINED_ESCAPE_SEQUENCE:
				undefinedEscape();
				exit(0);
				break;
			case UNDEFINED_ESCAPE_SEQUENCE_HEX:
				undefinedHex();
				exit(0);
				break;
			case ERROR:
				//showToken("ERROR");
				cout<< "ERROR" << yytext <<endl;
				exit(0);
				break;
			default:
				cout << "ERROR " << yytext <<endl;
            	exit(0);
				break;
		}
		
	}

	return 0;
}



void printStr() {
    std::string strprint(yytext);
    cout << yylineno << " STRING " ;
    for(int i = 0; i < strprint.size(); i++){
        char character = strprint[i];
        char next_character = strprint[i + 1];
        if(character == '"') {
			 continue;
		}
        if(character == '\\' && next_character == 'x'){
            std::stringstream spars;
            spars << std::hex << strprint.substr(i+2, 2);
            int x;
            spars >> x;
            cout << char(x);
            i += 3;
        } 
		if(character == '\\' && next_character == 'n'){
            cout << '\n';
            i++;
        } 
		if(character == '\\' && next_character == 't'){
            cout << '\t';
            i++;
        }
		if(character == '\\' && next_character == 'r') {
            cout << '\r';
            i++;
        } 
        if(character == '\\' && next_character == '\"'){
            cout << '\"';
            i++;
        }  
		if(character == '\\'){
            cout << '\\';
            i++;
        } else {
            cout << character;
        }
    }
    cout << endl;
}


void undefinedEscape(){
    std::string strescape(yytext);
	int sizeofstr = strescape.size();
    char charachter = strescape[sizeofstr - 1];
    cout << "Error undefined escape sequence " << charachter << endl;
    exit(0);
}

void undefinedHex(){
    std::string hexstr(yytext);
    int sizeofstr = hexstr.size();
    cout << "Error undefined escape sequence ";
    if(hexstr[sizeofstr-2] == 'x'){
        cout << hexstr[sizeofstr - 2] << endl;
        return;
    }
    cout << "x" << hexstr[sizeofstr - 2];
    if(hexstr[sizeofstr - 1] != '"')
        cout << hexstr[sizeofstr-1];
    cout << endl;
}





