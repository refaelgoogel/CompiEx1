%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap

Digits            ([0-9])
DigitsNoZero        ([1-9])
Alphabet           ([a-zA-Z])
AlphabetAndDigits      ([a-zA-Z0-9])

    /* hw1 defined that every hex digit that can be ascii char - so first is 0-7 and second is 0-9A-Fa-f */

HexDigit              ([0-7][0-9A-Fa-f])

    /* not allowed in STRING \, ", \n, \r, \0 so by order of ASCII this is the seq */
    /* ascii table https://simple.wikipedia.org/wiki/File:ASCII-Table-wide.svg */
    /* space then tab then ! then # to [ then ] (excluded ") then to ~ */
    /* tab is inside by hw definition */
    /* should work by https://regex101.com/r/qEVaCB/1 */

String           ([ 	!#-\[\]-~])

    /* this escaped sequence are OK: \\, \", \n, \r, \t, \0 */
    /* there will be outer \\ to the regular expression so it will be escaped */
    /* so inside the [] will be the escapsed sequence without the outer \\ */
    /* the escaped sequence without the outer \(meaning \\) are : \(so \\), "(so \"), n, r, t, 0 */
    /* should work by https://regex101.com/r/QJPdNM/1 */

StringAllowedEscapeSequence         ([\\\"nrt0])

    /* WS: blank space ( ) then \t is tab and replaceble with (	). then \n and \r by hw1 definition */

WhiteSpaces       ([ \t\n\r])

StringUndefinedEscapeSequence       ([^\\\"nrt0])

UnDefinedHexDigit ([^0-7][0-9A-Fa-f]|[0-7][^0-9A-Fa-f]|[^0-7][^0-9A-Fa-f]|[^0-9A-Fa-f])


    /* --------------------------------------------------------------------------------------- */
    /* ---------------------------------- Rules section -------------------------------------- */
    /* --------------------------------------------------------------------------------------- */

%%


    /* Refael: Notice that comments must have tab before them */
    /* Comments without tab will be unrecognized by the lexer and will make error */

    /* Refael: Notice that the order of the rules is important: */
    /* 1. longer rules would win shorter rules */
    /* 2. if rules are of the same size then the first by order that the rules written will win */ 

    /* first page of HW1 */  

int                                                                                 return INT;
byte                                                                                return BYTE;
b                                                                                   return B;
bool                                                                                return BOOL;
and                                                                                 return AND;
or                                                                                  return OR;
not                                                                                 return NOT;
true                                                                                return TRUE;
false                                                                               return FALSE;
return                                                                              return RETURN;
if                                                                                  return IF;
else                                                                                return ELSE;
while                                                                               return WHILE;
break                                                                               return BREAK;
continue                                                                            return CONTINUE;
;                                                                                   return SC;

    /* So far - trivial */  

    /* second page of HW1 */  

    /* Refael: notice that lex is translated to C, so speical characters must be escaped with \ */
    /* WhiteSpace: BlankSpace (space), Tab, NewLine(\n), CarriageReturn(CR - \r) */
    /* Some of the special characters are: \,/, [, ], {, }, (, ), *, +, ?, |, ., ^, $, (, ), -, #, and space */ 


\(                                                                                  return LPAREN;
\)                                                                                  return RPAREN;
\{                                                                                  return LBRACE;
\}                                                                                  return RBRACE;
=                                                                                   return ASSIGN;

((==)|(!=)|(<)|(>)|(<=)|(>=))                                                       return RELOP;
(\+)|(\-)|(\*)|(\/)                                                                 return BINOP;

    /* // (so \/\/) then every char except LF(\n), CR(\r), CRLF(\r\n) */
    /* this will work by https://regex101.com/r/tLiqrc/1 */

(\/\/)([^\r\n]*)                                                                    return COMMENT;

    /* Id shuold be just english alphabet with digits and should start with at least 1 letter */

({Alphabet}{AlphabetAndDigits}*)                                                    return ID;

    /* NUM shuold be or one single 0 or number with un-zero leading digit */
    /* from piazza: https://piazza.com/class/lwj3hm8j9le622/post/29, sequence of zeros will be interpreted */
    /* as sequence of sequence of single unique tokens that each one is NUM with value that is single 0 */
    /* should work by https://regex101.com/r/hsjgmQ/1 */

(({DigitsNoZero}{Digits}*)|0)                                                          return NUM;

    /* STRING shuold be in size of 0 or more, could be any printable character or WhiteSpaces except these: */
    /* \, ", \n, \r, \0, except the cases in which they are escaped: */
    /* this escaped sequence are OK: \\, \", \n, \r, \t, \0, \xdd when dd is hex number */
    /* any other escape sequence is not OK*/

    /* for muhammed, the string also include \xdd where dd is hex number, so notice that when you *\
    /* handle this special case in cpp code */

\"({String}|{AlphabetAndDigits}|\\{StringAllowedEscapeSequence}|\\x{HexDigit})*\"               return STRING;

    /* this case is for the case that line end in the middle of string (unclosed from the right) */

\"({String}|\\{StringAllowedEscapeSequence}|\\x{HexDigit})*                                      return UNCLOSED_STRING;

    /* this case is for the case that the string has an undefined (un-allowed) escape sequence */
    /* the OK escape sequence are: \\, \", \n, \r, \t, \0, \xdd when dd is hex number */
    /* the undefined escape sequence are any other escape sequence */
    /* so string with un-defined escape sequence is string of the form: */
    /* "string\StringUndefinedEscapeSequence" */
    /* the extream case with noth undefine sequence and unclosed string, */
    /* can be handled by both cases as the hw1 defined */
    /* so no difference if string closed or not, the lexer will identified un-defined escape sequence */
    /* and will return the token UNDEFINED_ESCAPE_SEQUENCE that will be handled as error in the cpp code */

\"({String}|\\{StringAllowedEscapeSequence}|\\x{HexDigit})*\\({StringUndefinedEscapeSequence}|{UnDefinedHexDigit})       return UNDEFINED_ESCAPE_SEQUENCE;

    /* this case if for escape-sequence of the form \xdd that is undefined */
    /* for Muhammed: i added to hpp this speciel case for more comfortable handling this special case */
    /* 2 cases: 1. x followd by non-hex digit. 2. string end before the second hex digit */
    /* so this 2 forms: \x (so \\x) and 2chars that is not hex digit and \x and 1 char that is not hex digit, */
    /* including the case when the string is ended, i mean the char " is not valid first or second hex digit */

\"({String}|\\{StringAllowedEscapeSequence}|\\x{HexDigit})*\\x{UnDefinedHexDigit} return UNDEFINED_ESCAPE_SEQUENCE_HEX;

    /* WhiteSpaces shuold be ignored by lexer by hw definition */

{WhiteSpaces}                                                                       ;

    /* this . (end) case is for the case that the input is not recognized by any of the rules */
    /* this is an error case so the lexer will return an error */
    /* in hw1 said the should print every un-valid char. if we got here, we have */
    /* un-valid string that it's first char is not valid, */
    /* (otherwise it will be recognized by the rules above as ID,or by other rule) */
    /* so we will return ERROR and should print the first char of yytext in cpp code*/

.                     return ERROR;

    /* --------------------------------------------------------------------------------------- */
    /* ---------------------------------- End of Rules section ------------------------------- */
    /* --------------------------------------------------------------------------------------- */

%%

