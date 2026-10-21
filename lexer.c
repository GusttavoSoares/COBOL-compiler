#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>

// Error Handling 
// Inspiration - https://www.lowlevelcraft.com/tasks/lexer-error-handling
bool isInvalidCharInColumn7 (char character) {
    if (character != ' ' && character != 'd' && character != '*' && character != '/' && character != '-') {
        printf("caracter invalido na coluna 7: %c\n", character);
        return true;
    }
    return false;
}

bool isUserDefinedWord(char* lexeme) {
    int length = strlen(lexeme);
    bool hasLetter = false;

    if (length == 0 || length > 30)
        return false;

    char first = lexeme[0];
    char last = lexeme[length - 1];

    if (first == '-' || last == '-')
        return false;

    for (int i = 0; lexeme[i] != '\0'; i++) {
        if (isalpha(lexeme[i])) {
            hasLetter = true;
        } else if (!isdigit(lexeme[i]) && lexeme[i] != '-') {
            return false;
        }
    }

    return hasLetter;
}

bool isNumberWithSigned(char* lexeme) {
    if (lexeme[0] == '-' || lexeme[0] == '+' )
        return true;
    return false;
}

bool isNumber(char* lexeme) {
    int start = 0;
    bool hasDecimalPoint = false;

    // Se tiver sinal na frente, comeca a checar depois dele
    if (isNumberWithSigned(lexeme))
        start = 1;

    if (lexeme[start] == '\0')
        return false;

    // ??
    for (int i = start; lexeme[i] != '\0'; i++) {
        char c = lexeme[i];

        if (isdigit(c))
            continue;

        if (c == '.') {
            if (hasDecimalPoint)
                return false; // segundo ponto

            if (lexeme[i + 1] == '\0')
                return false; // ponto no final ex: 3.

            hasDecimalPoint = true;
            continue;
        }

        return false;
    }
    return true;
}

bool isAlphaNumeric(char* lexeme) {
    char first = lexeme[0];
    char last;

    if (first != '"' || strlen(lexeme) < 2)
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

bool isDot (char * lexeme) {
    if (strcmp(lexeme, ".") == 0) {
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
    int line;
    int column;
};

struct TokenList {
    struct Token* items;
    size_t length;
    size_t capacity;
};

struct TokenList tokens = { NULL, 0, 0 };

void exit_nomem(void) {
    fprintf(stderr, "out of memory\n");
    exit(1);
}

static char* keywords[] = {
    "IDENTIFICATION", "ENVIRONMENT", "DATA", "PROCEDURE", "DIVISION", "SECTION",
    "PROGRAM-ID", "CONFIGURATION", "INPUT-OUTPUT", "FILE",
    "WORKING-STORAGE", "LOCAL-STORAGE", "LINKAGE", "SCREEN",
    "SOURCE-COMPUTER", "OBJECT-COMPUTER", "SPECIAL-NAMES", "FILE-CONTROL", "I-O-CONTROL",
    "SELECT", "ASSIGN", "END", "PROGRAM",

    "PIC", "PICTURE", "VALUE", "VALUES",

    "ZERO", "ZEROS", "ZEROES", "SPACE", "SPACES",

    "DISPLAY", "ACCEPT", "MOVE", "TO", "PERFORM", "VARYING", "FROM", "BY",
    "UNTIL", "TIMES", "END-PERFORM", "IF", "THEN", "ELSE", "END-IF",
    "ADD", "SUBTRACT", "MULTIPLY", "DIVIDE", "COMPUTE", "GIVING",
    "STOP", "RUN", "GOBACK",

    NULL // fim da lista
};

char* isKeyword(char* lexeme) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcasecmp(lexeme, keywords[i]) == 0) { 
            return keywords[i];
        }
    }
    return NULL;
}

void addToken(char* tokencategory, char* lexeme, int line, int column) { 
    if (tokens.length == tokens.capacity) {
        size_t new_capacity = tokens.capacity == 0 ? 16 : tokens.capacity * 2;
        struct Token* new_items = realloc(tokens.items, new_capacity * sizeof(struct Token));
        if (new_items == NULL) {
            exit_nomem();
        }
        tokens.items = new_items;
        tokens.capacity = new_capacity;
    }

    char* lexeme_copy = strdup(lexeme);
    if (lexeme_copy == NULL) {
        exit_nomem();
    }

    tokens.items[tokens.length].tokencategory = tokencategory;
    tokens.items[tokens.length].lexeme = lexeme_copy;
    tokens.items[tokens.length].line = line;
    tokens.items[tokens.length].column = column;
    tokens.length++;
}

void freeTokens(void) {
    for (size_t i = 0; i < tokens.length; i++) {
        free(tokens.items[i].lexeme);
    }
    free(tokens.items);
    tokens.items = NULL;
    tokens.length = 0;
    tokens.capacity = 0;
}

void  defineTokenCategory(char* lexeme, int line, int column){
    char* keyword = isKeyword(lexeme);

    if (keyword != NULL) {
        addToken(keyword, lexeme, line, column);
    } else {
        bool isUserDefinedWord_bool = isUserDefinedWord(lexeme);

        if (isUserDefinedWord_bool) {
            addToken("IDENTIFIER", lexeme, line, column);
        } else if (isAlphaNumeric(lexeme)) {
            addToken("ALPHANUMERIC", lexeme, line, column);            
        } else if (isEqual(lexeme)) {
            addToken("EQUAL", lexeme, line, column);
        } else if (isLess(lexeme)) {
            addToken("LESS", lexeme, line, column);
        } else if (isEqualOrLess(lexeme)) {
            addToken("EQUALORLESS", lexeme, line, column);
        } else if (isEqualOrGreater(lexeme)) {
            addToken("EQUALORGREATER", lexeme, line, column);
        } else if (isGreater(lexeme)) {
            addToken("GREATERTHAN", lexeme, line, column);
        } else if (isLeftParenthesis(lexeme)) {
            addToken("LPARENTHESIS", lexeme, line, column);
        } else if (isRightParenthesis(lexeme)) {
            addToken("RPARENTHESIS", lexeme, line, column);
        } else if (isDot(lexeme)) {
            addToken("DOT", lexeme, line, column);
        } else if (isMinus(lexeme)) {
            addToken("MINUS", lexeme, line, column);
        } else if (isNumber(lexeme)) {
            if (isNumberWithSigned(lexeme)) {
                if (lexeme[0] == '-') {
                    addToken("MINUS", "-", line, column);
                } else {
                    addToken("PLUS", "+", line, column);
                }

                addToken("NUMERIC", lexeme + 1, line, column + 1);

            } else {
            addToken("NUMERIC", lexeme, line, column);
            }
        } else {
            printf("token invalido: %s (linha %d)\n", lexeme, line);
            addToken("TOK_ERROR", lexeme, line, column);
        }
    }
}

void appendToLexeme(char* s, size_t size, int character, int line, int column, int* startLine, int* startColumn) {
    size_t length = strlen(s);

    if (length == 0) {
        *startLine = line;
        *startColumn = column;
    }

    if (length < size - 1) {
        s[length] = (char) character;
        s[length + 1] = '\0';
    } else {
        printf("lexema muito longo na linha %d, coluna %d\n", *startLine, *startColumn);
    }
}

// Paragrafos que sao so documentacao e sao ignorados como comentario (ex: AUTHOR. Enio Basso.)
static char* commentEntryKeywords[] = {
    "AUTHOR", "INSTALLATION", "DATE-WRITTEN", "DATE-COMPILED", "SECURITY", "REMARKS",
    NULL // fim da lista
};

bool isCommentEntry(char* lexeme) {
    for (int i = 0; commentEntryKeywords[i] != NULL; i++) {
        if (strcasecmp(lexeme, commentEntryKeywords[i]) == 0)
            return true;
    }
    return false;
}

void readCharByChar(char * file) {
    FILE *filePointer = NULL;

    int columnCounterPosition = 0;
    int lineCounter = 1;
    bool isInQuotationMarks = false;
    bool isInPictureString = false; // logo depois de PIC ou PICTURE

    int startLine = 0;
    int startColumn = 0;
    
    int thisCharacter;
    char s[256];
    memset(s, 0, sizeof(s)); // importante
    filePointer = fopen(file, "r");
    
    if (filePointer == NULL) {
        perror("Error in file pointer ");
        return;
    }

    fseek(filePointer, 6, SEEK_CUR);
    columnCounterPosition = 6;
    
    while ((thisCharacter = fgetc(filePointer)) != EOF) {

        if (columnCounterPosition >= 72 && thisCharacter != '\n') {
            while ((thisCharacter = fgetc(filePointer)) != '\n' && thisCharacter != EOF) {}
            if (thisCharacter == EOF) {
                break;
            }
        }
        
        if (columnCounterPosition == 6 && thisCharacter != '\n') {
            if (isInvalidCharInColumn7(thisCharacter)) {
                char invalid[2] = { (char) thisCharacter, '\0' };
                addToken("TOK_ERROR", invalid, lineCounter, 7);
                columnCounterPosition++;
                continue;
            }
            if (thisCharacter == '*' || thisCharacter == '/' || thisCharacter == 'd') {
                while ((thisCharacter = fgetc(filePointer)) != '\n' && thisCharacter != EOF) {}
                if (thisCharacter == EOF) {
                    break;
                }
            }

            if (thisCharacter == '-') {
                thisCharacter = fgetc(filePointer);
                columnCounterPosition++;
            }
        }
        

        if (thisCharacter == '\n') {
            lineCounter++;
            columnCounterPosition = 6;

            for (int skipped = 0; skipped < 6; skipped++) {
                thisCharacter = fgetc(filePointer);
                if (thisCharacter == EOF)
                    break;
                if (thisCharacter == '\n') {
                    lineCounter++;
                    skipped = -1;
                }
            }
            continue;
        }

        int column = columnCounterPosition + 1;

        if (isInPictureString) {
            int nextCharacter = fgetc(filePointer);
            ungetc(nextCharacter, filePointer);

            bool nextIsBlank = nextCharacter == ' ' || nextCharacter == '\n' || nextCharacter == EOF;
            bool endsPicture = thisCharacter == ' ' || ((thisCharacter == '.' || thisCharacter == ',') && nextIsBlank);

            if (!endsPicture) {
                appendToLexeme(s, sizeof(s), thisCharacter, lineCounter, column, &startLine, &startColumn);
                columnCounterPosition++;
                continue;
            }

            if (*s != 0 && strcasecmp(s, "IS") != 0) {
                addToken("PIC_STRING", s, startLine, startColumn);
                memset(s, 0, sizeof(s));
                isInPictureString = false;
            }
        }

        if (thisCharacter == '"') {
            if (isInQuotationMarks == true) {
                isInQuotationMarks = false;
            } else { 
                isInQuotationMarks = true;
            }
        }
        
        if (thisCharacter == '.' && !isInQuotationMarks && *s != 0 && isNumber(s)) {
            int nextCharacter = fgetc(filePointer);
            ungetc(nextCharacter, filePointer);

            if (isdigit(nextCharacter)) {
                appendToLexeme(s, sizeof(s), thisCharacter, lineCounter, column, &startLine, &startColumn);
                columnCounterPosition++;
                continue;
            }
        }

        if (isInQuotationMarks) {
            appendToLexeme(s, sizeof(s), thisCharacter, lineCounter, column, &startLine, &startColumn);

        } else if (thisCharacter != ' ' && thisCharacter != ',' && thisCharacter != '.' && thisCharacter != '*' && thisCharacter != '(' && thisCharacter != ')' && !isInQuotationMarks) {
            appendToLexeme(s, sizeof(s), thisCharacter, lineCounter, column, &startLine, &startColumn);

        } else {
            // KEYWORDS
            if (*s != 0) {
                if (isCommentEntry(s)) {
                    memset(s, 0, sizeof(s));
                    while ((thisCharacter = fgetc(filePointer)) != '\n' && thisCharacter != EOF) {}
                    ungetc(thisCharacter, filePointer); // devolve o \n para ser tratado no inicio do loop
                    continue;
                }

                defineTokenCategory(s, startLine, startColumn);

                if (strcasecmp(s, "PIC") == 0 || strcasecmp(s, "PICTURE") == 0)
                    isInPictureString = true;

                memset(s, 0, sizeof(s));
            }

            if (thisCharacter == '.') {
                defineTokenCategory(".", lineCounter, column);
            }

            if (thisCharacter == '(') {
                defineTokenCategory("(", lineCounter, column);
            }

            if (thisCharacter == ')') {
                defineTokenCategory(")", lineCounter, column);
            }
        }

        columnCounterPosition++;
    }

    if (*s != 0) {
        defineTokenCategory(s, startLine, startColumn);
    }
    
    fclose(filePointer);
}

int main(int argc, char* argv[]) {
    char* file = "cobol_code.cbl";
    if (argc > 1)
        file = argv[1];

    readCharByChar(file);

    printf("LINHA  COLUNA  CATEGORIA        LEXEMA\n");
    for (size_t i = 0; i < tokens.length; i++) {
        struct Token t = tokens.items[i];
        printf("%5d  %6d  %-15s  %s\n", t.line, t.column, t.tokencategory, t.lexeme);
    }

    freeTokens();
    return 0;

}
