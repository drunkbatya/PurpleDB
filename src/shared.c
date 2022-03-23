#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "shared.h"

int select(char **lecs);
int check_if_table_exists(char *table_name);
void assign_modules_structure(char **lecs);
void assign_modules_select(char **lecs, char **select);
void assign_modules_where(char **lecs, char **where);
void print_mock(char **select, char **where);

// MOCK
/*
int main() {
    // MOCK
    char *lecs[4];
    char *col = "id";
    char *name = "modules";
    char *where = "id";
    char *val = "5";
    lecs[0] = col;
    lecs[1] = name;
    lecs[2] = where;
    lecs[3] = val;

    select(lecs);
    return 0;
}
*/
// MOCK

int check_if_table_exists(char *table_name) {
    if (strcmp(table_name, LEVELS) == 0 || strcmp(table_name, MODULES) == 0
           || strcmp(table_name, STATUS) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void assign_modules_select(char **lecs, char **select) {
    if (strcmp(lecs[0], "*") == 0) {  // To select all columns
        for (int i = 0; i < 5; i++) {
            select[i] = lecs[0];
            return;
        }
    }
    for (int i = 0; i < 5; i++) {
        select[i] = "";
    }

    if (strcmp(lecs[0], "id") == 0) {
        select[0] = "1";
    } else if (strcmp(lecs[0], "name") == 0) {
        select[1] = "1";
    } else if (strcmp(lecs[0], "mem_level_modules") == 0) {
        select[2] = "1";
    } else if (strcmp(lecs[0], "cell_num") == 0) {
        select[3] = "1";
    } else if (strcmp(lecs[0], "deletion_flag") == 0) {
        select[4] = "1";
    }
}

void assign_modules_where(char **lecs, char **where) {
    if (strcmp(lecs[2], "*") == 0) {  // if no WHERE
        for (int i = 0; i < 5; i++) {
            where[i] = lecs[2];
            return;
        }
    }
    for (int i = 0; i < 5; i++) {
        where[i] = "";
    }

    if (strcmp(lecs[2], "id") == 0) {
        where[0] = lecs[3];
    } else if (strcmp(lecs[2], "name") == 0) {
        where[1] = lecs[3];
    } else if (strcmp(lecs[2], "mem_level_modules") == 0) {
        where[2] = lecs[3];
    } else if (strcmp(lecs[2], "cell_num") == 0) {
        where[3] = lecs[3];
    } else if (strcmp(lecs[2], "deletion_flag") == 0) {
        where[4] = lecs[3];
    } 
}

void print_mock(char **select, char **where) {
    printf("select ");
    for (int i= 0; i < 5; i++) {
        printf("%s ", select[i]);
    }
    printf("\n");
    printf("where ");
    for (int i= 0; i < 5; i++) {
        printf("%s ", where[i]);
    }
    printf("\n");
}

int select(char **lecs) {
    if (check_if_table_exists(lecs[1]) == 0) {
        error_unknown_db(lecs[1]);
        return 0;
    }

  //  if (strcmp(lecs[1], LEVELS) == 0) {
  //      select_for_levels();
 //   }

    if (strcmp(lecs[1], MODULES) == 0) {
        char *select[5];
        char *where[5];
        assign_modules_select(lecs, select);
        assign_modules_where(lecs, where);
      //  print_mock(select, where);
        select_for_modules(select, where);
    }

  //  if (strcmp(lecs[1], STATUS) == 0) {
  //      select_for_statuses();
  //  }
    
    return 1;
}
















