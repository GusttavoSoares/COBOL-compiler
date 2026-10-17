#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

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

void exit_nomem(void) {
    fprintf(stderr, "out of memory\n");
    exit(1);
}


// Essa função precisa returnar String e não print
void printTokenCategory (enum TokenCategory category, hash_table* table, char* lexeme ){

 
    switch (category) {
        case IDENTIFICATION: lexeme; break;
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
    char* lexeme;

} Token;

void addToken(enum TokenCategory character, char lexeme) { 
    enum TokenCategory category = character;
    // 
    // printTokenCategory(category);
}

void addtohash(hash_table *table, char* lexeme) { 

    void* value = ht_get(table, lexeme);

    if (value != NULL) {
        int* pcount = (int*) value;
        (*pcount)++;
        
        if (ht_set(table, lexeme, pcount) == NULL) {
            exit_nomem();
        }

    } else {

    int* pcount = malloc(sizeof(int));

    if (pcount == NULL) {
        exit_nomem();
    }

    *pcount = 1;

    if (ht_set(table, lexeme, pcount) == NULL) {
        exit_nomem();
    }

    }

  
}

void isKeyword(char* lexeme, hash_table* table) {
    printf("lexeme que chegou %s\n", lexeme);

    if (strcmp(lexeme, "IDENTIFICATION") == 0) {
       addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "ENVIRONMENT") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "DATA") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "PROCEDURE") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "DIVISION") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "SECTION") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "DISPLAY") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "ACCEPT") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "PERFORM") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "STOP") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "RUN") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "IF") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "ELSE") == 0) {
        addtohash(table, lexeme);
    }
    else if (strcmp(lexeme, "MOVE") == 0) {
        addtohash(table, lexeme);
    }
    else {
        printf(lexeme, "\n");
    }



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

// str_append(char *s, char buffer) {

// }

void readCharByChar(char * file, hash_table* table) {
    FILE *filePointer = NULL;
    
    int thisCharacter; // hold the value of current character
    char s[126];
    memset(s, 0, sizeof(s)); // importante
    filePointer = fopen(file, "r");
    fseek(filePointer, 7, SEEK_CUR);

    if (filePointer == NULL) {
        perror("Error in file pointer ");
        // return -1;
    }

    while ((thisCharacter = fgetc(filePointer)) != EOF) {

        if (thisCharacter == '\n') {
            fseek(filePointer, 6, SEEK_CUR);
            
        }

            // KEYWORDS OR IDENTIFICATION
            // printf("thischaraacter: %c\n", thisCharacter);
        if (thisCharacter != ' ' && thisCharacter != '.') {
            // while (*s++);
            char cToStr[2];
            cToStr[1] = '\0';

            if (thisCharacter != '\n') {
            cToStr[0] = (char) thisCharacter;
            
            // printf("ASCIC %s\n", cToStr);
            // char* teste = asciC[0];
            strcat(s, cToStr);
            }

            // s eh a palavrfa final
            // printf("%s\n", s);

            // if (thisCharacter == ' ') {
            //     memset(s, 0, sizeof(s));    
            // }         

            

            // *s = '\0';

            // printf("s retornado 1: %s\n", s);
        } else {

            // KEYWORDS
            if (*s != 0) {
                isKeyword(s, table);
                memset(s, 0, sizeof(s));
            }
                        

            // printf("%s\n", s);


            // }

        }
            // printf("s retornado: %s\n", s);
        // printf("%c", thisCharacter);

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

    hash_table* symbol_table = hashTableCreate();
    
    readCharByChar("cobol_code.cbl", symbol_table);

    hti it = ht_iterator(symbol_table);
    printf("---------------------\n");
    while (ht_next(&it)) {
        printf("---------------------\n");
        printf("%s %d\n", it.key, *(int*)it.value);
        free(it.value);

    }

    printf("len: %d\n", (int)ht_length(symbol_table));
    return 0;

    

}
