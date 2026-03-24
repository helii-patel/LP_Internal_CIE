#include <stdio.h>
#include <string.h>

struct Symbol {
    char name[50];
    char type[20];
    int count;
};

struct Symbol table[100];
int indexST = 0;

void insert_symbol(char *name, char *type) {
    for(int i = 0; i < indexST; i++) {
        if(strcmp(table[i].name, name) == 0) {
            table[i].count++;
            return;
        }
    }

    strcpy(table[indexST].name, name);
    strcpy(table[indexST].type, type);
    table[indexST].count = 1;
    indexST++;
}

void write_symbol_table() {
    FILE *fp = fopen("../output/symbol_table.txt", "w");

    for(int i = 0; i < indexST; i++) {
        fprintf(fp, "%s\t%s\t%d\n",
            table[i].name,
            table[i].type,
            table[i].count);
    }

    fclose(fp);
}