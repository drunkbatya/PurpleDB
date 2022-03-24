#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "shared.h"
#include "modules.h"

void select_for_modules(char **field, char **where) {
    modules local;
    FILE *ptr = fopen(MODULES_PATH, "r");
    int identifier;
    int len = get_records_count_in_file(ptr);
    int counter = 0;
    int check_field;
    char temp[30];

    for (int i = 0; i < 5; i++) {
        if (field[i][0] == '*')
            identifier = 5;
        if (field[i][0] == '1') {
            identifier = i;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (!strlen(where[i]))
            continue;
        check_field = i;
        for (int j = 0; j < (int)strlen(where[i]); j++)
            temp[j] = where[i][j];
    }
    for (int i = 0; i < len; i++) {
        local = read_record_from_file(ptr, i);
        if (compare(&local, check_field, temp)) {
            print_struct(&local, identifier);
            counter++;
            if (counter == 1) print_mask(identifier);
            print_struct(&local, identifier);
        }
    }
    fclose(ptr);
    if (counter == 0)
        error_record_not_found();
}

void print_mask(int identifier) {
    if (identifier == 0) {
        printf("ID\n");
    } else if (identifier == 1) {
        printf("MODULE NAME\n");
    } else if (identifier == 2) {
        printf("MEMORY LEVEL MODULES\n");
    } else if (identifier == 3) {
        printf("CELL NUMBER\n");
    } else if (identifier == 4) {
        printf("DELETION FLAG\n");
    } else if (identifier == 5) {
        printf("| ID | MODULE NAME | MEMORY LEVEL MODULES | CELL NUMBER | DELETION FLAG |\n");
    }
}


int compare(modules *local, int check_field, char *temp) {
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

void print_struct(modules *local, int identifier) {
    if (identifier == 0) {
        printf("| %d |\n", local->id);
    } else if (identifier == 1) {
        printf("| %s |\n", local->module_name);
    } else if (identifier == 2) {
        printf("| %d |\n", local->mem_level_modules);
    } else if (identifier == 3) {
        printf("| %d |\n", local->cell_num);
    } else if (identifier == 4) {
        printf("| %d |\n", local->deletion_flag);
    } else if (identifier == 5) {
        printf("| %d ", local->id);
        printf("| %s ", local->module_name);
        printf("| %d ", local->mem_level_modules);
        printf("| %d ", local->cell_num);
        printf("| %d |", local->deletion_flag);
        printf("\n");
    }
}

void insert_for_modules(char **new_line) {
    int flag = check_id(new_line[0]);
    if (flag == 0) {
        invalid_id_error();
        return;
    }
    modules local;
    local.id = atoi(new_line[0]);
    int i;
    for (i = 0; i < (int)strlen(new_line[1]); i++) {
        local.module_name[i] = new_line[1][i];
    }
    local.module_name[i] = '\0';
    local.mem_level_modules = atoi(new_line[2]);
    local.cell_num = atoi(new_line[3]);
    local.deletion_flag = atoi(new_line[4]);
    FILE *ptr = fopen(MODULES_PATH, "a");
    int len = get_records_count_in_file(ptr);
    write_record_in_file(ptr, &local, len);
    fclose(ptr);
}


int check_id(char * id) {
    modules local;
    FILE *ptr = fopen(MODULES_PATH, "r");
    int len = get_records_count_in_file(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file(ptr, i);
        if (local.id == atoi(id)) {
            fclose(ptr);
            return 0;
        }
    }
    fclose(ptr);
    return 1;
}


// Function of writing a record of the specified type to the file at the specified serial number.
void write_record_in_file(FILE *pfile, modules *record_to_write, int index) {
    // Calculation of the offset at which the required record should be located from the beginning of the file.
    int offset = index * sizeof(modules);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(modules), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

// Function to get file size in bytes.
int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);    // Move the position pointer to the end of the file.
    size = ftell(pfile);          // Read the number of bytes from the beginning of the file to the current position pointer.
    rewind(pfile);                // For safety reasons, move the position pointer back to the beginning of the file.
    return size;
}


void update_for_modules(char **old, char **new) {
    if (strcmp(new[0], "") != 0) {
        invalid_id_error();
        return;
    }
    modules where;
    if (strcmp(old[0], "") != 0) {
        where.id = atoi(old[0]);
    } else {
        where.id = -1;
    }
    if (strcmp(old[1], "") != 0) {
        int i;
        for (i = 0; i < (int)strlen(old[1]); i++) {
            where.module_name[i] = old[1][i];
        }
        where.module_name[(int)strlen(old[1])] = '\0';
    } else {
        where.module_name[0] = '\0';
    }
    if (strcmp(old[2], "") != 0) {
        where.mem_level_modules = atoi(old[2]);
    } else {
        where.mem_level_modules = -1;
    }
    if (strcmp(old[3], "") != 0) {
        where.cell_num = atoi(old[3]);
    } else {
        where.cell_num = -1;
    }
    if (strcmp(old[4], "") != 0) {
        where.deletion_flag = atoi(old[4]);
    } else {
        where.deletion_flag = -1;
    }

    modules change;
    if (strcmp(new[0], "") != 0) {
        change.id = atoi(new[0]);
    } else {
        change.id = -1;
    }
    if (strcmp(new[1], "") != 0) {
        int i;
        for (i = 0; i < (int)strlen(new[1]); i++) {
            change.module_name[i] = new[1][i];
        }
        change.module_name[(int)strlen(new[1])] = '\0';
    } else {
        change.module_name[0] = '\0';
    }
    if (strcmp(new[2], "") != 0) {
        change.mem_level_modules = atoi(new[2]);
    } else {
        change.mem_level_modules = -1;
    }
    if (strcmp(new[3], "") != 0) {
        change.cell_num = atoi(new[3]);
    } else {
        change.cell_num = -1;
    }
    if (strcmp(new[4], "") != 0) {
        change.deletion_flag = atoi(new[4]);
    } else {
        change.deletion_flag = -1;
    }

    FILE *ptr = fopen(MODULES_PATH, "r+b");
    modules local;
    int len = get_records_count_in_file(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file(ptr, i);
        if (compare_for_update(&local, &where) == 1) {
            update_record(ptr, &local, &change, i);
        }
    }
    fclose(ptr);
}

void update_record(FILE *pfile, modules *local, modules *change, int index) {
    // Calculation of the offset at which the required record should be located from the beginning of the file.
    int offset = index * sizeof(modules);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);
    if (change->id != -1) {
        local->id = change->id;
    }
    if (change->module_name[0] != '\0') {
        int i;
        for (i = 0; i < (int)strlen(change->module_name); i++) {
            local->module_name[i] = change->module_name[i];
        }
        local->module_name[i] = '\0';
    }
    if (change->mem_level_modules != -1) {
        local->mem_level_modules = change->mem_level_modules;
    }
    if (change->cell_num != -1) {
        local->cell_num = change->cell_num;
    }
    if (change->deletion_flag != -1) {
        local->deletion_flag = change->deletion_flag;
    }
    // Write a record of the specified type to a file.
    fwrite(local, sizeof(modules), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}


int compare_for_update (modules *local, modules *where) {
    if ((where->id != -1) && (local->id != where->id)) {
        return 0;
    }
    if ((where->module_name[0] != '\0') && (strcmp(local->module_name, where->module_name) != 0)) {
        return 0;
    }
    if ((where->mem_level_modules != -1) && (local->mem_level_modules != where->mem_level_modules)) {
        return 0;
    }
    if ((where->cell_num != -1) && (local->cell_num != where->cell_num)) {
        return 0;
    }
    if ((where->deletion_flag != -1) && (local->deletion_flag != where->deletion_flag)) {
        return 0;
    }
    return 1;
}