
#include "ExpressionToCharMapping.h";
using namespace std;
const int width = 25;
vector<string> inputString;
unordered_map<string, string> lexemeToken;
unordered_map<string, pair<string, pair<string, int>>> lexemeType;
int lineCount = 1;
void insertLexemeToken()
{
    lexemeToken["int"] = "INT";
    lexemeToken["float"] = "FLOAT";
    lexemeToken["void"] = "VOID";
    lexemeToken["string"] = "STRING";

    lexemeToken["for"] = "FOR";
    lexemeToken["<"] = "LT";
    lexemeToken[">"] = "GT";
    lexemeToken[">="] = "GE";
    lexemeToken["<="] = "LE";
    lexemeToken["!="] = "NE";
    lexemeToken["=="] = "EQ";
    lexemeToken["("] = "OPEN_PAREN";
    lexemeToken[")"] = "CLOSE_PAREN";
    lexemeToken["{"] = "OPEN_BRACE";
    lexemeToken["}"] = "CLOSE_BRACE";
    lexemeToken[","] = "COMMA";
    lexemeToken["++"] = "UNARY";
    lexemeToken["--"] = "UNARY";
    lexemeToken["+"] = "ADD";
    lexemeToken["-"] = "SUBTRACT";
    lexemeToken["*"] = "MULTIPLY";
    lexemeToken["/"] = "DIVIDE";
    lexemeToken["%"] = "MODULO";
    lexemeToken["true"] = "TRUE";
    lexemeToken["false"] = "FALSE";
    lexemeToken["="] = "ASSIGNMENT";
    lexemeToken[";"] = "SEMICOLON";
    lexemeToken["main"] = "MAIN";
    lexemeToken["return"] = "RETURN";
}

// Returns 'true' if the character is a DELIMITER. bool isDelimiter (char ch)
bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '<' || ch == ',' || ch == '=' ||
        ch == ';' || ch == '(' || ch == ')' || ch == '[' ||
        ch == ']' || ch == '\n' || ch == '{' || ch == '}' || ch == '"' || ch == '%')
    {
        return true;
    }
    return false;
}

pair<bool, string> isoperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == '%')
    {
        string op = "";
        op += ch;
        return {true, op};
    }
    return make_pair(false, " ");
}
