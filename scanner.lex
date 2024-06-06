%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap

zero            ([0])
num             ([1-9][0-9]*)
digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])

%%

{zero}                      return NUM;
{num}                       return NUM;
{digit}+          			;/*return NUM;*/
{letter}+					;/*return WORD;*/
{letter}+@{letter}+\.com	;/*return EMAIL;*/
{whitespace}				;
.		printf("Lex doesn't know what that is!\n");

%%

