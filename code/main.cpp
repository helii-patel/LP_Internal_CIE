#include <stdio.h>
#include <stdlib.h>

extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;

void write_symbol_table();

// declare tacFile from parser
extern FILE *tacFile;

int main() {
    yyin = fopen("../input.txt", "r");
    yyout = fopen("../output/tokens.txt", "w");

    // 🔥 FIX: open TAC file
    tacFile = fopen("../output/tac.txt", "w");

    if (!yyin || !yyout || !tacFile) {
        printf("File opening error\n");
        return 1;
    }

    yyparse();

    fclose(yyin);
    fclose(yyout);
    fclose(tacFile);

    write_symbol_table();

    system("g++ optimizer.cpp -o optimizer");
#ifdef _WIN32
    system("optimizer.exe");
#else
    system("./optimizer");
#endif

    printf("Execution Completed.\n");

    return 0;
}