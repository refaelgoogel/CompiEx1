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

void showToken(const char * nameS)
{
    cout << yylineno << " " << nameS << " " << yytext <<endl;
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
				cout << "Error unclosed string\n";
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
        else if(character == '\\' && next_character == 'x'){
            std::stringstream spars;
            spars << std::hex << strprint.substr(i+2, 2);
            int x;
            spars >> x;
            cout << char(x);
            i += 3;
        } 
		else if(character == '\\' && next_character == 'n'){
            cout << '\n';
            i++;
			continue;
        } 
		else if(character == '\\' && next_character == 't'){
            cout << '\t';
            i++;
			continue;
        }
		else if(character == '\\' && next_character == 'r') {
            cout << '\r';
            i++;
			continue;
        } 
        else if(character == '\\' && next_character == '\"'){
            cout << '\"';
            i++;
			continue;
        }  
		else if(character == '\\'){
            cout << '\\';
            i++;
			continue;
        } else {
            cout << character;
        }
    }
    cout << endl;
}


void undefinedEscape(){

    std::string strescape(yytext); 
	
	int sizeofstr = strescape.size();

	int backslash_index = -1;

	for (int i = sizeofstr - 1; i >= 0; i--) {

		if (strescape[i] == '\\') {

			backslash_index = i;
			break;
		}
	}

	if (backslash_index == -1) {exit(0);}

	if (backslash_index == (sizeofstr - 1)) {cout << "Error undefined escape sequence" << endl; exit(0);}

	cout << "Error undefined escape sequence " << strescape[backslash_index + 1] << endl;
	exit(0);
    
}

void undefinedHex(){

    std::string hexstr(yytext);
    int sizeofstr = hexstr.size();

    cout << "Error undefined escape sequence ";

	// print the undefined hex sequence

	int x_index = -1;

	for (int i = sizeofstr-1; i >= 0; i--) {

		if (hexstr[i] == 'x') {
			x_index = i;
			break;
		}
	}

	if (x_index == -1) {return;}

	cout << "x";

	if (hexstr[x_index + 1] != '"') {

		cout << hexstr[x_index + 1];
	}else{
		
		cout << "\n";
		return;
	}

	if (hexstr[x_index + 2] != '"') {
		cout << hexstr[x_index + 2];
	}
	else{
		
		cout << "\n";
		return;
	}
	
	cout << "\n";
	return;

}



