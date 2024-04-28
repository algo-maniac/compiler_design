
#include <bits/stdc++.h>
using namespace std;
unordered_map<string, char> expr_symbol_variable;
unordered_map<string, char> expr_symbol_terminal;
void createMapping()
{
    expr_symbol_variable["data_type"] = 'A';
    expr_symbol_variable["condition"] = 'B';
    expr_symbol_variable["declaration"] = 'C';
    expr_symbol_variable["return_type"] = 'D';
    expr_symbol_variable["declaration_in_for"] = 'E';
    expr_symbol_variable["relop"] = 'F';
    expr_symbol_variable["expression"] = 'G';
    expr_symbol_variable["expression_float"] = 'H';
    expr_symbol_variable["expression_float_prefix"] = 'I';
    expr_symbol_variable["expression_string"] = 'J';
    expr_symbol_variable["return_value"] = 'K';
    expr_symbol_variable["main_body"] = 'L';
    expr_symbol_variable["declaration_in_argument_list"] = 'M';
    expr_symbol_variable["statement"] = 'N';
    expr_symbol_variable["body"] = 'O';
    expr_symbol_variable["declaration_in_argument"] = 'P';
    expr_symbol_variable["expression_string"] = 'Q';
    expr_symbol_terminal["INT"] = 'a';
    expr_symbol_terminal["FLOAT"] = 'b';
    expr_symbol_terminal["VOID"] = 'c';
    expr_symbol_terminal["CHAR_PTR"] = 'd';
    expr_symbol_terminal["STRING"] = 'e';
    expr_symbol_terminal["STRING_EXP"] = 'f';
    expr_symbol_terminal["ID"] = 'g';
    expr_symbol_terminal["FOR"] = 'h';
    expr_symbol_terminal["NUMBER"] = 'i';
    expr_symbol_terminal["FLOAT_NUMBER"] = 'j';
    expr_symbol_terminal["LT"] = 'k';
    expr_symbol_terminal["GT"] = 'l';
    expr_symbol_terminal["GE"] = 'm';
    expr_symbol_terminal["LE"] = 'n';
    expr_symbol_terminal["NE"] = 'o';
    expr_symbol_terminal["EQ"] = 'p';
    expr_symbol_terminal["OPEN_PAREN"] = 'q';
    expr_symbol_terminal["CLOSE_PAREN"] = 'r';
    expr_symbol_terminal["OPEN_BRACE"] = 's';
    expr_symbol_terminal["CLOSE_BRACE"] = 't';
    expr_symbol_terminal["COMMA"] = 'u';
    expr_symbol_terminal["UNARY"] = 'v';
    expr_symbol_terminal["ADD"] = 'w';
    expr_symbol_terminal["SUBTRACT"] = 'x';
    expr_symbol_terminal["MULTIPLY"] = 'y';
    expr_symbol_terminal["DIVIDE"] = 'z';
    expr_symbol_terminal["MODULO"] = '0';
    expr_symbol_terminal["TRUE"] = '1';
    expr_symbol_terminal["FALSE"] = '2';
    expr_symbol_terminal["ASSIGNMENT"] = '3';
    expr_symbol_terminal["SEMICOLON"] = '4';
    expr_symbol_terminal["MAIN"] = '5';
    expr_symbol_terminal["RETURN"] = '6';
}