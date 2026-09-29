#include <stdio.h>
#include <stdlib.h>

enum TokenCategory {
    // Reserved Keywords
    IDENTIFICATION,
    ENVIRONMENT,
    DATA, 
    PROCEDURE, 
    DIVISION,
    SECTION,
    DISPLAY,
    ACCEPT,
    PERFORM,
    STOP,
    RUN,
    IF, 
    ELSE, 
    MOVE,


    // Literals
    PLUS,
    MINUS,
    DOT,
    SINGLE_QUOTATION,
    DOUBLE_QUOTATION,

    // Identifiers
    IDENTIFIER,
    ALPHANUMERIC, 
    NUMERIC,

    // Special Symbols
    COMMA, 
    SEMICOLON, // ;
    L_PARENTHESIS,
    R_PARENTHESIS,
    SLASH,
    ASTERISK,
    DEPURATION,

};

typedef struct {
    enum TokenCategory tokencategory;
    char lexeme;

} Token;

void addToken(enum TokenCategory character, char lexeme) { 
    enum TokenCategory category = character;
    printf("character %d e lexeme %c\n", character, lexeme);
}


void scanLine4Token(char c) {
    switch (c) {
        case '+': 
        addToken(PLUS, c);
        break;

        case '-':
        addToken(MINUS, c);
        break;

        case '.':
        addToken(DOT, c);
        break;

        case ',':
        addToken(COMMA, c);
        break;

        case ';':
        addToken(SEMICOLON, c);
        break;

        case '*':
        addToken(ASTERISK, c);
        break;

        case '/':
        addToken(SLASH, c);

        case '(':
        addToken(L_PARENTHESIS, c);
        break;

        case ')':
        addToken(R_PARENTHESIS, c);
        break;

        default:
        printf("erro");

    }
}

int main() {
    char slash = '/';
    scanLine4Token(slash);
    return 0;
}
