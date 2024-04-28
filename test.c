#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define token types
typedef enum
{
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN,
    TOKEN_STRING,

} TokenType;

// Define token structure
typedef struct
{
    TokenType type;
    char *value;
} Token;

// Define structure for symbol table entry
typedef struct SymbolEntry
{
    char *name;
    TokenType type;
    struct SymbolEntry *next;
} SymbolEntry;

// Define size of symbol table hash table
#define TABLE_SIZE 100

// Define symbol table hash table
SymbolEntry *symbolTable[TABLE_SIZE];

// Hash function for symbol table
unsigned int hash(char *str)
{
    unsigned int hash = 0;
    while (*str)
    {
        hash = (hash * 31) + *str++;
    }
    return hash % TABLE_SIZE;
}

// Function to insert entry into symbol table
void insertIntoSymbolTable(char *name, TokenType type)
{
    unsigned int index = hash(name);
    SymbolEntry *newEntry = (SymbolEntry *)malloc(sizeof(SymbolEntry));
    newEntry->name = strdup(name);
    newEntry->type = type;
    newEntry->next = symbolTable[index];
    symbolTable[index] = newEntry;
}

// Function to search for entry in symbol table
SymbolEntry *searchSymbolTable(char *name)
{
    unsigned int index = hash(name);
    SymbolEntry *entry = symbolTable[index];
    while (entry != NULL)
    {
        if (strcmp(entry->name, name) == 0)
        {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

// Function to check if a string is a keyword
int isKeyword(char *str)
{
    const char *keywords[] = {"if", "else", "while", "for", "int", "float", "char", "return"}; // Add more keywords as needed
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; ++i)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

// Function to print tokens
void printToken(Token token)
{
    switch (token.type)
    {
    case TOKEN_IDENTIFIER:
        printf("Identifier: %s\n", token.value);
        break;
    case TOKEN_KEYWORD:
        printf("Keyword: %s\n", token.value);
        break;
    case TOKEN_NUMBER:
        printf("Number: %s\n", token.value);
        break;
    case TOKEN_OPERATOR:
        printf("Operator: %s\n", token.value);
        break;
    case TOKEN_STRING:
        printf("String: %s\n", token.value);
        break;
    case TOKEN_UNKNOWN:
        printf("Unknown: %s\n", token.value);
        break;
    }
}

// Function to tokenize input
Token getNextToken(FILE *fp)
{
    char ch;
    char buffer[100];
    int bufferIndex = 0;

    // Skip whitespace characters
    while ((ch = fgetc(fp)) != EOF && isspace(ch))
        ;

    // Handle identifier or keyword
    if (isalpha(ch) || ch == '_')
    {
        buffer[bufferIndex++] = ch;
        while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
        {
            buffer[bufferIndex++] = ch;
        }
        buffer[bufferIndex] = '\0';
        ungetc(ch, fp);
        Token token;
        token.value = strdup(buffer);
        token.type = isKeyword(buffer) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        insertIntoSymbolTable(buffer, token.type);
        return token;
    }

    // Handle numbers
    if (isdigit(ch))
    {
        buffer[bufferIndex++] = ch;
        while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.'))
        {
            buffer[bufferIndex++] = ch;
        }
        buffer[bufferIndex] = '\0';
        ungetc(ch, fp);
        Token token;
        token.value = strdup(buffer);
        token.type = TOKEN_NUMBER;
        return token;
    }

    // Handle opening and closing braces
    if (ch == '{' || ch == '}')
    {
        buffer[bufferIndex++] = ch;
        buffer[bufferIndex] = '\0';
        Token token;
        token.value = strdup(buffer);
        token.type = TOKEN_OPERATOR; // Change to TOKEN_OPERATOR if needed
        return token;
    }

    // Handle operators
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>')
    {
        buffer[bufferIndex++] = ch;
        ch = fgetc(fp); // Read the next character
        if ((ch == '=' || ch == '<' || ch == '>'))
        {
            buffer[bufferIndex++] = ch;
        }
        else
        {
            ungetc(ch, fp); // Put the character back into the stream
        }
        buffer[bufferIndex] = '\0';
        Token token;
        token.value = strdup(buffer);
        token.type = TOKEN_OPERATOR;
        return token;
    }

    if (ch == ',')
    {
        buffer[bufferIndex++] = ch;
        buffer[bufferIndex] = '\0';
        Token token;
        token.value = strdup(buffer);
        token.type = TOKEN_OPERATOR;
        return token;
    }

    // Handle parenthesis and semicolon
    if (ch == '(' || ch == ')' || ch == ';')
    {
        buffer[bufferIndex++] = ch;
        buffer[bufferIndex] = '\0';
        Token token;
        token.value = strdup(buffer);
        token.type = TOKEN_OPERATOR;
        return token;
    }
    //
    // Handle strings
    if (ch == '"')
    {
        buffer[bufferIndex++] = ch;
        while ((ch = fgetc(fp)) != EOF && ch != '"')
        {
            buffer[bufferIndex++] = ch;
        }
        if (ch == EOF)
        {
            printf("Error: Unterminated string.\n");
            exit(1);
        }
        buffer[bufferIndex++] = ch; // Include the closing double quotation mark
        buffer[bufferIndex] = '\0';
        Token token;
        token.value = strdup(buffer);
        token.type = TOKEN_STRING; // Change to TOKEN_STRING if needed
        return token;
    }

    // Handle end of file
    if (ch == EOF)
    {
        Token token;
        token.value = NULL;
        token.type = TOKEN_UNKNOWN;
        return token;
    }

    // Handle unknown characters
    buffer[bufferIndex++] = ch;
    buffer[bufferIndex] = '\0';
    Token token;
    token.value = strdup(buffer);
    token.type = TOKEN_UNKNOWN;
    return token;
}

int main()
{
    // Initialize symbol table
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        symbolTable[i] = NULL;
    }

    FILE *fp = fopen("example.c", "r"); // Replace "example.c" with the name of your input file
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    Token token;
    do
    {
        token = getNextToken(fp);
        printToken(token);
    } while (token.type != TOKEN_UNKNOWN && token.type != EOF);

    // Print symbol table
    printf("\nSymbol Table:\n");
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        SymbolEntry *entry = symbolTable[i];
        while (entry != NULL)
        {
            printf("%-15s %-10s\n", entry->name, (entry->type == TOKEN_KEYWORD) ? "Keyword" : "Identifier");
            entry = entry->next;
        }
    }

    fclose(fp);
    return 0;
}
