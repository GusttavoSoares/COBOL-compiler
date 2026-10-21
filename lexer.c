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

char * remove_space(char * lexeme) {
    char *output = lexeme;
    do {
        while(*output == ' ') {
            ++output;
        }
    } while (*lexeme++ = *output++);
    
    return output;

}
// Error Handling 
// Inspiration - https://www.lowlevelcraft.com/tasks/lexer-error-handling

bool isInvalidCharacter(char *lexeme) {
    // printf("entrou aqui");
    for (int i = 0; lexeme[i] != '\0'; i++) {
        if (!isalnum(lexeme[i]));
        return false;
    }
    return true;
}

bool isUnderterminatedString(char *lexeme) {}

bool isInvalidNumber(char *lexeme) {}

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
        char* output = remove_space(lexeme);
        if (isInvalidCharacter(output)) {

        for (int i = 1; lexeme[i] != '\0'; i++) {
            if (!isalnum(lexeme[i])) {
                printf("erro no caractere %c\n", lexeme[i]);  // esta identificando - como errado, mas deve permitir
                return false;
            }
        }
        return false;
        } 
    }
    return true;
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
    if (strcmp(lexeme, "(") == 0) {
        return true;
    }
    return false;
}


bool isRightParenthesis (char * lexeme) {
    if (strcmp(lexeme, ")") == 0) {
        return true;
    }
    return false;
}

bool isMinus (char * lexeme) {
    if (strcmp(lexeme, "-") == 0) {
        return true;
    }
    return false;
}

bool isEqual (char * lexeme) {
    if (strcmp(lexeme, "=") == 0) {
        return true;
    }
    return false;
}

bool isLess (char * lexeme) {
    if (strcmp(lexeme, "<" ) == 0) {
        return true;
    }
    return false;
}

bool isEqualOrLess (char * lexeme) {
    if (strcmp(lexeme, "<=") == 0) {
        return true;
    }
    return false;
}

bool isEqualOrGreater (char * lexeme) {
    if (strcmp(lexeme, ">=") == 0) {
        return true;
    }
    return false;
}

bool isGreater (char * lexeme) {
    if (strcmp(lexeme, ">") == 0) {
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
    } else if (strcmp(lexeme, "ENVIRONMENT") == 0) {
        return "ENVIRONMENT";
    } else if (strcmp(lexeme, "DATA") == 0) {
        return "DATA";
    } else if (strcmp(lexeme, "PROCEDURE") == 0) {
        return "PROCEDURE";
    } else if (strcmp(lexeme, "DIVISION") == 0) {
        return "DIVISION";
    } else if (strcmp(lexeme, "SECTION") == 0) {
        return "SECTION";
    } else if (strcmp(lexeme, "DISPLAY") == 0) {
        return "DISPLAY";
    } else if (strcmp(lexeme, "ACCEPT") == 0) {
        return "ACCEPT";
    } else if (strcmp(lexeme, "PERFORM") == 0) {
        return "PERFORM";
    } else if (strcmp(lexeme, "STOP") == 0) {
        return "STOP";
    } else if (strcmp(lexeme, "RUN") == 0) {
        return "RUN";
    } else if (strcmp(lexeme, "IF") == 0) {
        return "IF";
    } else if (strcmp(lexeme, "ELSE") == 0) {
        return "ELSE";
    } else if (strcmp(lexeme, "MOVE") == 0) {
        return "MOVE";
    } else {
        return NULL;
    }
}

void addToken(char* tokencategory, char* lexeme) { 
    // enum TokenCategory category = character;
   struct Token t = { tokencategory, lexeme};
   printf("Token category: %s ", t.tokencategory);
   printf("Token lexeme: %s\n", t.lexeme);
}

void  defineTokenCategory(char* lexeme ){
    char* keyword = isKeyword(lexeme);

    if (keyword != NULL) {
        addToken(keyword, lexeme);
    } else {
        bool isUserDefinedWord_bool = isUserDefinedWord(lexeme);

        if (isUserDefinedWord_bool) {
            addToken("IDENTIFIER", lexeme);
        } else if (isAlphaNumeric(lexeme)) {
            addToken("ALPHANUMERIC", lexeme);            
        } else if (isEqual(lexeme)) {
            addToken("EQUAL", lexeme);
        } else if (isLess(lexeme)) {
            addToken("LESS", lexeme);
        } else if (isEqualOrLess(lexeme)) {
            addToken("EQUALORLESS", lexeme);
        } else if (isEqualOrGreater(lexeme)) {
            addToken("EQUALORGREATER", lexeme);
        } else if (isGreater(lexeme)) {
            addToken("GREATERTHAN", lexeme);
        } else if (isLeftParenthesis(lexeme)) {
            addToken("LPARENTHESIS", lexeme);
        } else if (isRightParenthesis(lexeme)) {
            addToken("RPARENTHESIS", lexeme);
        } else if (isMinus(lexeme)) {
            addToken("MINUS", lexeme);
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
        }
    }
}

void readCharByChar(char * file) {
    FILE *filePointer = NULL;
    int columnCounterPosition = 0;
    int lineCounter = 1;
    bool isInQuotationMarks = false; // check if is in a quotation mark, like DISPLAY "===== start =======".
    
    int thisCharacter; // hold the value of current character
    char s[30];
    memset(s, 0, sizeof(s)); // importante
    filePointer = fopen(file, "r");
    fseek(filePointer, 6, SEEK_CUR);
    columnCounterPosition = ftell(filePointer) + 1;
    
    if (filePointer == NULL) {
        perror("Error in file pointer ");
        // return -1;
    }
    
    while ((thisCharacter = fgetc(filePointer)) != EOF) {

        if (columnCounterPosition > 72) {
            while ((thisCharacter = fgetc(filePointer)) != '\n') {}
            fseek(filePointer, 5, SEEK_CUR); 
            thisCharacter = fgetc(filePointer);
            lineCounter++;
            columnCounterPosition = 6;
            continue;
        }
        
        if (columnCounterPosition == 6) {
            if (thisCharacter == '*' || thisCharacter == '/' || thisCharacter == 'd') {
                while ((thisCharacter = fgetc(filePointer)) != '\n') {}
                lineCounter++;
            }

            if (thisCharacter == '-') {
                thisCharacter = fgetc(filePointer);
                columnCounterPosition++;
            }
        }
        

        if (thisCharacter == '\n') {
            fseek(filePointer, 5, SEEK_CUR); // avanca apenas 5 para conseguir somente na proxima interacao pegar o * e realziar as coisas necessarfias
            thisCharacter = fgetc(filePointer);
            lineCounter++;
            columnCounterPosition = 6;
            continue;
        }

        if (thisCharacter == '"') {
            if (isInQuotationMarks == true) {
                isInQuotationMarks = false;
            } else { 
                isInQuotationMarks = true;
            }
        }
        
        if (isInQuotationMarks) {
            char cToStr[2];
            cToStr[1] = '\0';

            if (thisCharacter != '\n') {
                cToStr[0] = (char) thisCharacter;
                strcat(s, cToStr);
            }

        } else if (thisCharacter != ' ' && thisCharacter != '.' && thisCharacter != '*' && thisCharacter != '(' && thisCharacter != ')' && !isInQuotationMarks) {
            // while (*s++);
            char cToStr[2];
            cToStr[1] = '\0';

            if (thisCharacter != '\n') {
                cToStr[0] = (char) thisCharacter;
                strcat(s, cToStr);
            }

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
        }

        columnCounterPosition++;
        // Apenas teste
        if (thisCharacter == '@') {
            columnCounterPosition++;
            printf("@ está na coluna %d\n", columnCounterPosition);
            printf("@ está na linha %d\n", lineCounter);
        }
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
