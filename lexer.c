#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include <ctype.h>
#include <stdbool.h>

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

// Problematica se colocar @ no meio, ajeitar depois
bool isUserDefinedWord(char* lexeme) {
    char first = lexeme[0];
    char last;

    if (first == '-' || first == '"')
        return false;

    for (int i = 0; lexeme[i] != '\0'; i++) {
        if (lexeme[i+1] == '\0') {
            last = lexeme[i];
            if (last == '-' || first == '"') 
            return false;
        } 
    }

    for (int i = 0; lexeme[i] != '\0'; i++) {
        if (isalpha(lexeme[i])) 
        return true;
    } 
    return false;
}

bool isNumber(char* lexeme) {
    for (int i = 1; lexeme[i] != '\0'; i++) {
        if (!isdigit(lexeme[i])) 
        return false;
    } 
    return true;
}

bool isNumberWithSigned(char* lexeme) {
    if (lexeme[0] == '-' || lexeme[0] == '+' )
        return true;
    return false;
}

bool isAlphaNumeric(char* lexeme) {
    char first = lexeme[0];
    char last;

    if (first != '"')
    return false;


    for (int i = 0; lexeme[i] != '\0'; i++) {
        if (lexeme[i+1] == '\0') {
            last = lexeme[i];
            if (last != '"') 
            return false;
        } 
    }

    return true;

}

bool isLeftParenthesis (char * lexeme) {
    if (strcmp(lexeme, "(")) {
        return true;
    }
    return false;
}


bool isRightParenthesis (char * lexeme) {
    if (strcmp(lexeme, ")")) {
        return true;
    }
    return false;
}

bool isMinus (char * lexeme) {
    if (strcmp(lexeme, "-")) {
        return true;
    }
    return false;
}


struct Token{
    char* tokencategory;
    char* lexeme;
};

void exit_nomem(void) {
    fprintf(stderr, "out of memory\n");
    exit(1);
}

char* isKeyword(char* lexeme) {
    //printf("lexeme que chegou %s\n", lexeme);

    if (strcmp(lexeme, "IDENTIFICATION") == 0) {
       return "IDENTIFICATION";
    }
    else if (strcmp(lexeme, "ENVIRONMENT") == 0) {
        return "ENVIRONMENT";
    }
    else if (strcmp(lexeme, "DATA") == 0) {
        return "DATA";
    }
    else if (strcmp(lexeme, "PROCEDURE") == 0) {
        return "PROCEDURE";
    }
    else if (strcmp(lexeme, "DIVISION") == 0) {
        return "DIVISION";
    }
    else if (strcmp(lexeme, "SECTION") == 0) {
        return "SECTION";
    }
    else if (strcmp(lexeme, "DISPLAY") == 0) {
        return "DISPLAY";
    }
    else if (strcmp(lexeme, "ACCEPT") == 0) {
        return "ACCEPT";
    }
    else if (strcmp(lexeme, "PERFORM") == 0) {
        return "PERFORM";
    }
    else if (strcmp(lexeme, "STOP") == 0) {
        return "STOP";
    }
    else if (strcmp(lexeme, "RUN") == 0) {
        return "RUN";
    }
    else if (strcmp(lexeme, "IF") == 0) {
        return "IF";
    }
    else if (strcmp(lexeme, "ELSE") == 0) {
        return "ELSE";
    }
    else if (strcmp(lexeme, "MOVE") == 0) {
        return "MOVE";
    }
    else {
        return NULL;
    }
}

void addToken(char* tokencategory, char* lexeme) { 
    // enum TokenCategory category = character;
   struct Token t = { tokencategory, lexeme};
   printf("Token category: %s ", t.tokencategory);
   printf("Token lexeme: %s\n", t.lexeme);
    // 
    // printTokenCategory(category);
}

// Essa função precisa returnar String e não print
void  defineTokenCategory(char* lexeme ){
    char* keyword = isKeyword(lexeme);

    if (keyword != NULL) {
        addToken(keyword, lexeme);
 
    } else {
    // printf("erro aaa");

        bool isUserDefinedWord_bool = isUserDefinedWord(lexeme);

        if (isUserDefinedWord_bool) {
            addToken("IDENTIFIER", lexeme);

        } else if (isAlphaNumeric(lexeme)) {
            addToken("ALPHANUMERIC", lexeme);
        


        } else if (isNumber(lexeme)) {
            char* numericlexeme;
            if (isNumberWithSigned(lexeme)) {

                if (lexeme[0] == '-') {
                    addToken("MINUS", "-");
                } else {
                    addToken("PLUS", "+");
                }

               
                strcpy(numericlexeme, lexeme + 1);
                addToken("NUMERIC", numericlexeme);
            } else {
            addToken("NUMERIC", lexeme);
            }

        } else if (isLeftParenthesis(lexeme)) {
            addToken("LPARENTHESIS", lexeme);
        } else if (isRightParenthesis(lexeme)) {
            addToken("RPARENTHESIS", lexeme);
        } else if (isMinus(lexeme)) {
            addToken("MINUS", lexeme);
        }

    // switch (keyword) {
    //     case IDENTIFICATION: lexeme; break;
    //     case ENVIRONMENT: printf("ENVIRONMENT"); break;
    //     case DATA: printf("DATA"); break;
    //     case PROCEDURE: printf("PROCEDURE"); break;
    //     case DIVISION: printf("DIVISION"); break;
    //     case SECTION: printf("SECTION"); break;
    //     case DISPLAY: printf("DISPLAY"); break;
    //     case ACCEPT: printf("ACCEPT"); break;
    //     case PERFORM: printf("PERFORM"); break;
    //     case STOP: printf("STOP"); break;
    //     case RUN: printf("RUN"); break;
    //     case IF: printf("IF"); break;
    //     case ELSE: printf("ELSE"); break;
    //     case MOVE: printf("MOVE"); break;
    //     case PLUS: printf("PLUS"); break;
    //     case MINUS: printf("MINUS"); break;
    //     case DOT: printf("DOT"); break;
    //     case SINGLE_QUOTATION: printf("SINGLE_QUOTATION"); break;
    //     case DOUBLE_QUOTATION: printf("DOUBLE_QUOTATION"); break;
    //     case IDENTIFIER: printf("IDENTIFIER"); break;
    //     case ALPHANUMERIC: printf("ALPHANUMERIC"); break;
    //     case NUMERIC: printf("NUMERIC"); break;
    //     case COMMA: printf("COMMA"); break;
    //     case SEMICOLON: printf("SEMICOLON"); break;
    //     case L_PARENTHESIS: printf("L_PARENTHESIS"); break;
    //     case R_PARENTHESIS: printf("R_PARENTHESIS"); break;
    //     case SLASH: printf("SLASH"); break;
    //     case ASTERISK: printf("ASTERISK"); break;
    //     case DEPURATION: printf("DEPURATION"); break;
    //     default: printf("Error"); break;
    // }

}
}

 



// void addtohash(hash_table *table, struct Token token) { 

//     void* value = ht_get(table, token);

//     if (value != NULL) {
//         int* pcount = (int*) value;
//         (*pcount)++;
        
//         if (ht_set(table, token, pcount) == NULL) {
//             exit_nomem();
//         }

//     } else {

//     int* pcount = malloc(sizeof(int));

//     if (pcount == NULL) {
//         exit_nomem();
//     }

//     *pcount = 1;

//     if (ht_set(table, token, pcount) == NULL) {
//         exit_nomem();
//     }

//     }

  
// }




// void scanLine4Token(char c) {
//     switch (c) {
//         case '+': 
//             addToken(PLUS, c);
//             break;

//         case '-':
//             addToken(MINUS, c);
//             break;

//         case '.':
//             addToken(DOT, c);
//             break;

//         case ',':
//             addToken(COMMA, c);
//             break;

//         case ';':
//             addToken(SEMICOLON, c);
//             break;

//         case '*':
//             addToken(ASTERISK, c);
//             break;

//         case '/':
//             addToken(SLASH, c);
//             break;

//         case '(':
//             addToken(L_PARENTHESIS, c);
//             break;

//         case ')':
//             addToken(R_PARENTHESIS, c);
//             break;

//         default:
//             printf("erro");
//             break;

//     }
// }

// str_append(char *s, char buffer) {

// }

void readCharByChar(char * file) {
    FILE *filePointer = NULL;
    int columnCounterPosition = 0;
    bool isInQuotationMarks = false; // check if is in a quotation mark, like DISPLAY "===== start =======".
    
    int thisCharacter; // hold the value of current character
    char s[30];
    memset(s, 0, sizeof(s)); // importante
    filePointer = fopen(file, "r");
    fseek(filePointer, 6, SEEK_CUR);
    columnCounterPosition = ftell(filePointer);
    // printf("columncounter position %d", columnCounterPosition);

    
    
    if (filePointer == NULL) {
        perror("Error in file pointer ");
        // return -1;
    }
    
    while ((thisCharacter = fgetc(filePointer)) != EOF) {
        // long position = ftell(filePointer);
        // printf("columnCounterPosition %d\n", columnCounterPosition);

        // if (columnCounterPosition % 6 == 0) {
            // printf("character que entrou %d\n", thisCharacter);
            if (thisCharacter == '*') {
                // printf("aqui nunca entrou");
                
                while ((thisCharacter = fgetc(filePointer)) != '\n') {
                    // printf("character atual %c\n", thisCharacter);
                    // fseek(filePointer, 6, SEEK_CUR);
                }

                // printf("character atual chegou %c", thisCharacter);
                // if (thisCharacter == '\n') {
                //     fseek(filePointer, 6, SEEK_CUR);
                // }

            }
        // }

        if (thisCharacter == '\n') {
            // columnCounterPosition =+ 6;
            fseek(filePointer, 5, SEEK_CUR); // avanca apenas 5 para conseguir somente na proxima interacao pegar o * e realziar as coisas necessarfias
            thisCharacter = fgetc(filePointer);
            continue;
        }


        if (thisCharacter == '"') {
            // printf("entreou aqui %d\n", thisCharacter);
            if (isInQuotationMarks == true) {
                isInQuotationMarks = false;
            } else { 
                isInQuotationMarks = true;
            }

            printf("bool value %d", isInQuotationMarks);
        }
        
        if (isInQuotationMarks) {
            char cToStr[2];
            cToStr[1] = '\0';

            if (thisCharacter != '\n') {
            cToStr[0] = (char) thisCharacter;
            
            // printf("ASCIC %s\n", cToStr);
            // char* teste = asciC[0];
            strcat(s, cToStr);
            }
        } else if (thisCharacter != ' ' && thisCharacter != '.' && thisCharacter != '*' && thisCharacter != '(' && thisCharacter != ')' && !isInQuotationMarks) {
            // while (*s++);
            char cToStr[2];
            cToStr[1] = '\0';

            if (thisCharacter != '\n') {
            cToStr[0] = (char) thisCharacter;
            
            // printf("ASCIC %s\n", cToStr);
            // char* teste = asciC[0];
            strcat(s, cToStr);

            // printf("character atual %c\n", thisCharacter);
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

                defineTokenCategory(s);

                if (thisCharacter == '(')
                defineTokenCategory("(");

                if (thisCharacter == ')')
                defineTokenCategory(")");

                memset(s, 0, sizeof(s));
            }
                        
            // }

        }
            // printf("s retornado: %s\n", s);
        // printf("%c", thisCharacter);

    }
    fclose(filePointer);
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

    // hash_table* symbol_table = hashTableCreate();
    
    readCharByChar("cobol_code.cbl");

    // hti it = ht_iterator(symbol_table);
    // printf("---------------------\n");
    // while (ht_next(&it)) {
    //     printf("---------------------\n");
    //     printf("%s %d\n", it.key, *(int*)it.value);
    //     free(it.value);

    // }

    // printf("len: %d\n", (int)ht_length(symbol_table));
    return 0;

    

}
