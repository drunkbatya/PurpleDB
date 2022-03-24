// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "shared.h"
#include "levels.h"
#include "binary.h"
#include "main.h"

void select_for_levels(char **field, char **where) {
    int identifier;
    for (int i = 0; i < 3; i++) {
        if (field[i][0] == '*') {
            identifier = 3;
        } else if (field[i][0] == '1') {
            identifier = i;
            break;
        }
    }
    char temp[30] = "-";
    int check_field = 5;
    for (int i = 0; i < 3; i++) {
        if (strcmp(where[i], "") == 0) {
            continue;
        } else {
            check_field = i;
            for (int j = 0; j < (int)strlen(where[i]); j++) {
                temp[j] = where[i][j];
            }
        }
    }
    levels local;
    int counter = 0;
    FILE *ptr = fopen(LEVELS_PATH, "r");
    int len = get_records_count_in_file(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file_levels(ptr, i);
        if (compare_levels(&local, check_field, temp) == 1) {
            counter++;
            if (counter == 1) print_mask_levels(identifier);
            print_struct_levels(&local, identifier);
        }
    }
    print_outro_levels(identifier);
    fclose(ptr);
    if (counter == 0) error_record_not_found();
}

void print_mask_levels(int identifier) {
    if (identifier == 0) {
        printf(" ------------------\n");
        printf("| mem_level_levels |\n");
        printf("|------------------|\n");
    } else if (identifier == 1) {
        printf(" -------------\n");
        printf("| cell_amount |\n");
        printf(" -------------\n");
    } else if (identifier == 2) {
        printf(" --------------\n");
        printf("| protect_flag |\n");
        printf(" --------------\n");
    } else if (identifier == 3) {
        printf(" -----------------------------------------------\n");
        printf("| mem_level_levels | cell_amount | protect_flag |\n");
        printf("|-----------------------------------------------|\n");
    }
}

void print_outro_levels(int identifier) {
    if (identifier == 0)
        printf(" ------------------\n");
    if (identifier == 1)
        printf(" -------------\n");
    if (identifier == 2)
        printf(" --------------\n");
    if (identifier == 3)
        printf(" -----------------------------------------------\n");
}

int compare_levels(levels *local, int check_field, char *temp) {
    if ((check_field == 5) && (temp[0] == '-')) return 1;
    if ((check_field == 0) && (local->mem_level_levels == atoi(temp))) {
        return 1;
    }
    if ((check_field == 1) && (local->cell_amount == atoi(temp))) {
        return 1;
    }
    if ((check_field == 2) && (local->protect_flag == atoi(temp))) {
        return 1;
    }
    return 0;
}

levels read_record_from_file_levels(FILE *pfile, int index) {
    int offset = index * sizeof(levels);
    fseek(pfile, offset, SEEK_SET);
    levels record;
    fread(&record, sizeof(levels), 1, pfile);
    rewind(pfile);
    return record;
}

// printf("| %-6d |\n", local->id);
void print_struct_levels(levels *local, int identifier) {
    if (identifier == 0) {
        printf("| %-16d |\n", local->mem_level_levels);
    } else if (identifier == 1) {
        printf("| %-11d |\n", local->cell_amount);
    } else if (identifier == 2) {
        printf("| %-12d |\n", local->protect_flag);
    } else if (identifier == 3) {
        printf("| %-16d ", local->mem_level_levels);
        printf("| %-11d ", local->cell_amount);
        printf("| %-12d |", local->protect_flag);
        printf("\n");
    }
}

void insert_for_levels(char **new_line) {
    levels local;
    local.mem_level_levels = atoi(new_line[0]);
    local.cell_amount = atoi(new_line[1]);
    local.protect_flag = atoi(new_line[2]);
    FILE *ptr = fopen(LEVELS_PATH, "a");
    int len = get_records_count_in_file(ptr);
    write_record_in_file_levels(ptr, &local, len);
    fclose(ptr);
    
//    levels local;
//    local.mem_level_levels = atoi(new_line[0]);
//    local.cell_amount = atoi(new_line[1]);
//    local.protect_flag = atoi(new_line[2]);
//    FILE *ptr = fopen(LEVELS_PATH, "a");
//    int len = get_records_count_in_file(ptr);
//    write_record_in_file_levels(ptr, &local, len);
//    fclose(ptr);
}


// Function of writing a record of the specified type to the file at the specified serial number.
void write_record_in_file_levels(FILE *pfile, levels *record_to_write, int index) {
    // Calculation of the offset at which the required record should be located from the beginning of the file.
    int offset = index * sizeof(levels);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(levels), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

void update_for_levels(char **old, char **new) {
    levels where;
    if (strcmp(old[0], "") != 0) {
        where.mem_level_levels = atoi(old[0]);
    } else {
        where.mem_level_levels = -1;
    }
    if (strcmp(old[1], "") != 0) {
        where.cell_amount = atoi(old[1]);
    } else {
        where.cell_amount = -1;
    }
    if (strcmp(old[2], "") != 0) {
        where.protect_flag = atoi(old[2]);
    } else {
        where.protect_flag = -1;
    }

    levels change;
    if (strcmp(new[0], "") != 0) {
        change.mem_level_levels = atoi(new[0]);
    } else {
        change.mem_level_levels = -1;
    }
    if (strcmp(new[1], "") != 0) {
        change.cell_amount = atoi(new[1]);
    } else {
        change.cell_amount = -1;
    }
    if (strcmp(new[2], "") != 0) {
        change.protect_flag = atoi(new[2]);
    } else {
        change.protect_flag = -1;
    }

    FILE *ptr = fopen(LEVELS_PATH, "r+b");
    levels local;
    int len = get_records_count_in_file(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file_levels(ptr, i);
        if (compare_for_update_levels(&local, &where) == 1) {
            update_record_levels(ptr, &local, &change, i);
        }
    }
    fclose(ptr);
}

void update_record_levels(FILE *pfile, levels *local, levels *change, int index) {
    int offset = index * sizeof(levels);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);
    if (change->mem_level_levels != -1) {
        local->mem_level_levels = change->mem_level_levels;
    }
    if (change->cell_amount != -1) {
        local->cell_amount = change->cell_amount;
    }
    if (change->protect_flag != -1) {
        local->protect_flag = change->protect_flag;
    }
    // Write a record of the specified type to a file.
    fwrite(local, sizeof(levels), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}


int compare_for_update_levels(levels *local, levels *where) {
    if ((where->mem_level_levels != -1) && (local->mem_level_levels != where->mem_level_levels)) {
        return 0;
    }
    if ((where->cell_amount != -1) && (local->cell_amount != where->cell_amount)) {
        return 0;
    }
    if ((where->protect_flag != -1) && (local->protect_flag != where->protect_flag)) {
        return 0;
    }
    return 1;
}
