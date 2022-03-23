#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "shared.h"

int select(char *table_name, char *column, char *where, char *where_val);
int check_if_table_exists(char *table_name);


// MOCK

int main() {
    char *filename = calloc(150, sizeof(char));
    int i = 0;
    while (1) {
        int c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        } else {
            *(filename + i) = c;
            i++;
        }
    }
    select(filename,"col", "col", "val");
    free(filename);
    return 0;
}

// MOCK

int check_if_table_exists(char *table_name) {
    if (strcmp(table_name, LEVELS) == 0 || strcmp(table_name, MODULES) == 0
           || strcmp(table_name, STATUS) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int select(char *table_name, char *column, char *where, char *where_val) {
    if (check_if_table_exists(table_name) == 0) {
        error_unknown_db(table_name);
        return 0;
    }
    column = "i";
    where = "i";
    where_val = "8";
    return 1;
}

