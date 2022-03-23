#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "shared.h"
#include "select.h"

/*
int main() {
    char *select[5];
    char *id = "*";
    char *name = "";
    char *mem_level_modules = "";
    char *cell_num = "";
    char *deletion_flag = "";
    select[0] = id;
    select[1] = name;
    select[2] = mem_level_modules;
    select[3] = cell_num;
    select[4] = deletion_flag;
    char *where[5];
    char *idw = "89";
    char *namew = "";
    char *mem_level_modulesw = "";
    char *cell_numw = "";
    char *deletion_flagw = "";
    where[0] = idw;
    where[1] = namew;
    where[2] = mem_level_modulesw;
    where[3] = cell_numw;
    where[4] = deletion_flagw;
    select_for_modules(select, where);
    return 0;
}
*/

void select_for_modules(char **field, char **where) {
    int identifier;
    for (int i = 0; i < 5; i++) {
        if (field[i][0] == '*') {
            identifier = 5;
        } else if (field[i][0] == '1') {
            identifier = i;
            break;
        }
    }
    char temp[30];
    int check_field;
    for (int i = 0; i < 5; i++) {
        if (strcmp(where[i], "") == 0) {
            continue;
        } else {
            check_field = i;
            for (int j = 0; j < (int)strlen(where[i]); j++) {
                temp[j] = where[i][j];
            }
        }
    }
    modules local;
    int counter = 0;
    FILE *ptr = fopen(MODULES_PATH, "r");
    int len = get_records_count_in_file(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file(ptr, i);
        if (compare(&local, check_field, temp) == 1) {
            print_struct(&local, identifier);
            counter++;
        }
    }
    fclose(ptr);
    if (counter == 0) error_record_not_found();
}


int compare (modules *local, int check_field, char *temp) {
    if ((check_field == 0) && (local->id == atoi(temp))) {
        return 1;
    }
    if ((check_field == 1) && (strcmp(local->module_name, temp) == 0)) {
        return 1;
    }
    if ((check_field == 2) && (local->mem_level_modules == atoi(temp))) {
        return 1;
    }
    if ((check_field == 3) && (local->cell_num == atoi(temp))) {
        return 1;
    }
    if ((check_field == 4) && (local->deletion_flag == atoi(temp))) {
        return 1;
    }

    return 0;
}


int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(modules);
}

// Function of reading a record of a given type from a file by its serial number.
modules read_record_from_file(FILE *pfile, int index) {
    // Calculation of the offset at which desired entry should be located from the beginning of the file.
    int offset = index * sizeof(modules);          // оффсет - сдвиг??
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Reading a record of the specified type from a file.
    modules record;
    fread(&record, sizeof(modules), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

// Function to get file size in bytes.
int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);    // Move the position pointer to the end of the file.
    size = ftell(pfile);          // Read the number of bytes from the beginning of the file to the current position pointer.
    rewind(pfile);                // For safety reasons, move the position pointer back to the beginning of the file.
    return size;
}

void print_struct(modules *local, int identifier) {
    if (identifier == 0) {
        printf("ID\n");
        printf("| %d |\n", local->id);
    } else if (identifier == 1) {
        printf("MODULE NAME\n");
        printf("| %s |\n", local->module_name);
    } else if (identifier == 2) {
        printf("MEMORY LEVEL MODULES\n");
        printf("| %d |\n", local->mem_level_modules);
    } else if (identifier == 3) {
        printf("CELL NUMBER\n");
        printf("| %d |\n", local->cell_num);
    } else if (identifier == 4) {
        printf("DELETION FLAG\n");
        printf("| %d |\n", local->deletion_flag);
    } else if (identifier == 5) {
        printf("| ID | MODULE NAME | MEMORY LEVEL MODULES | CELL NUMBER | DELETION FLAG |\n");
        printf("| %d ", local->id);
        printf("| %s ", local->module_name);
        printf("| %d ", local->mem_level_modules);
        printf("| %d ", local->cell_num);
        printf("| %d |", local->deletion_flag);
        printf("\n");
    }
}

