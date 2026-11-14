%{

#include <stdio.h>
#include <stdlib.h>
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
    int ival;
    float fval;
}

%token IDENTIFICATION
%token ENVIRONMENT
%token DATA
%token PROCEDURE
%token DIVISION
%token SECTION
%token PROGRAM-ID
%token CONFIGURATION
%token INPUT-OUTPUT
%token FILE
%token WORKING-STORAGE

%token DOT

%token STRING

%type <name> STRING

%start prog

%%



prog: 
    | divisions
;

divisions: identification_division
;


identification_division: IDENTIFICATION DIVISION PROGRAM-ID DOT STRING DOT { printf("\tResult");}
;


%%

int yyparse (char const *file)
{
  yyin = fopen (file, "r");
  if (!yyin)
    {
      perror ("fopen");
      exit (EXIT_FAILURE);
    }
}

int main() {
    yyparse ("test_cobol.txt");
    return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}