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

// Essa função precisa returnar String e não print
void printTokenCategory (enum TokenCategory category){
    switch (category) {
        case IDENTIFICATION: printf("IDENTIFICATION"); break;
        case ENVIRONMENT: printf("ENVIRONMENT"); break;
        case DATA: printf("DATA"); break;
        case PROCEDURE: printf("PROCEDURE"); break;
        case DIVISION: printf("DIVISION"); break;
        case SECTION: printf("SECTION"); break;
        case DISPLAY: printf("DISPLAY"); break;
        case ACCEPT: printf("ACCEPT"); break;
        case PERFORM: printf("PERFORM"); break;
        case STOP: printf("STOP"); break;
        case RUN: printf("RUN"); break;
        case IF: printf("IF"); break;
        case ELSE: printf("ELSE"); break;
        case MOVE: printf("MOVE"); break;
        case PLUS: printf("PLUS"); break;
        case MINUS: printf("MINUS"); break;
        case DOT: printf("DOT"); break;
        case SINGLE_QUOTATION: printf("SINGLE_QUOTATION"); break;
        case DOUBLE_QUOTATION: printf("DOUBLE_QUOTATION"); break;
        case IDENTIFIER: printf("IDENTIFIER"); break;
        case ALPHANUMERIC: printf("ALPHANUMERIC"); break;
        case NUMERIC: printf("NUMERIC"); break;
        case COMMA: printf("COMMA"); break;
        case SEMICOLON: printf("SEMICOLON"); break;
        case L_PARENTHESIS: printf("L_PARENTHESIS"); break;
        case R_PARENTHESIS: printf("R_PARENTHESIS"); break;
        case SLASH: printf("SLASH"); break;
        case ASTERISK: printf("ASTERISK"); break;
        case DEPURATION: printf("DEPURATION"); break;
        default: printf("Error"); break;
    }
}

typedef struct {
    enum TokenCategory tokencategory;
    char lexeme;

} Token;

void addToken(enum TokenCategory character, char lexeme) { 
    enum TokenCategory category = character;
    // 
    printTokenCategory(category);
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
            break;

        case '(':
            addToken(L_PARENTHESIS, c);
            break;

        case ')':
            addToken(R_PARENTHESIS, c);
            break;

        default:
            printf("erro");
            break;

    }
}

void readCharByChar(char * file) {
    FILE *filePointer = NULL;
    
    int thisCharacter; // hold the value of current character

    filePointer = fopen(file, "r");

    if (filePointer == NULL) {
        perror("Error in file pointer ");
        // return -1;
    }

    while ((thisCharacter = fgetc(filePointer)) != EOF) {
        // if (thisCharacter == '\n') {
        //     printf("encontrado new line");
        // }
        printf("%c", thisCharacter);

    }

}

int main() {
    // char slash = '/';
    // scanLine4Token(slash);
    
    
    // char *line = NULL;
    // size_t len = 0;
    // ssize_t read;
    
    // printf("Enter a line: ");
    // read = getline(&line, &len, stdin);
    
    // if (read != -1) {
    //     printf("you entered: %ld", read);
    // } else {
    //     printf("error to read");
    // }
    
    // free(line);
    
    readCharByChar("cobol_code.cbl");
    return 0;
    

}
