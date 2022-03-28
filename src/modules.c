// Copyright [2022] <griselle, sparelis, laynadre>

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
    int len = get_records_count_in_file_modules(ptr);
    int counter = 0;
    int check_field;
    char temp[30];

    check_field = 5;
    temp[0] = '-';
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
        strcpy(temp, where[i]);
    }
    for (int i = 0; i < len; i++) {
        local = read_record_from_file_modules(ptr, i);
        if (compare_modules(&local, check_field, temp)) {
            counter++;
            if (counter == 1)
                print_mask_modules(identifier);
            print_struct_modules(&local, identifier);
        }
    }
    print_outro_modules(identifier);
    fclose(ptr);
    if (counter == 0)
        error_record_not_found();
}

void print_mask_modules(int identifier)
{
    if (identifier == 0) {
        printf(" --------\n");
        printf("| id     |\n");
        printf("|--------|\n");
    } else if (identifier == 1) {
        printf(" -------------------\n");
        printf("| module_name       |\n");
        printf("|-------------------|\n");
    } else if (identifier == 2) {
        printf(" -------------------\n");
        printf("| mem_level_modules |\n");
        printf("|-------------------|\n");
    } else if (identifier == 3) {
        printf(" ----------\n");
        printf("| cell_num |\n");
        printf("|----------|\n");
    } else if (identifier == 4) {
        printf(" ---------------\n");
        printf("| deletion_flag |\n");
        printf("|---------------|\n");
    } else if (identifier == 5) {
        printf(" ---------------------------------------------------------------------------\n");
        printf("| id     | module_name       | mem_level_modules | cell_num | deletion_flag |\n");
        printf("|---------------------------------------------------------------------------|\n");
    }
}

void print_outro_modules(int identifier)
{
    if (identifier == 0)
        printf(" --------\n");
    if (identifier == 1)
        printf(" -------------------\n");
    if (identifier == 2)
        printf(" -------------------\n");
    if (identifier == 3)
        printf(" ----------\n");
    if (identifier == 4)
        printf(" ---------------\n");
    if (identifier == 5)
        printf(" ---------------------------------------------------------------------------\n");
}

int compare_modules(modules *local, int check_field, char *temp) {
    if ((check_field == 5) && (temp[0] == '-'))
        return (1);
    if ((check_field == 0) && (local->id == atoi(temp)))
        return (1);
    if ((check_field == 1) && (strcmp(local->module_name, temp) == 0))
        return (1);
    if ((check_field == 2) && (local->mem_level_modules == atoi(temp)))
        return (1);
    if ((check_field == 3) && (local->cell_num == atoi(temp)))
        return (1);
    if ((check_field == 4) && (local->deletion_flag == atoi(temp)))
        return (1);
    return (0);
}

modules read_record_from_file_modules(FILE *pfile, int index) {
    int offset;
    
    offset = index * sizeof(modules);
    fseek(pfile, offset, SEEK_SET);
    modules record;
    fread(&record, sizeof(modules), 1, pfile);
    rewind(pfile);
    return (record);
}

void print_struct_modules(modules *local, int identifier)
{
    if (identifier == 0)
        printf("| %-6d |\n", local->id);
    if (identifier == 1)
        printf("| %-17s |\n", local->module_name);
    if (identifier == 2)
        printf("| %-17d |\n", local->mem_level_modules);
    if (identifier == 3)
        printf("| %-8d |\n", local->cell_num);
    if (identifier == 4)
        printf("| %-13d |\n", local->deletion_flag);
    if (identifier == 5)
    {
        printf("| %-7d", local->id);
        printf("| %-18s", local->module_name);
        printf("| %-18d", local->mem_level_modules);
        printf("| %-9d", local->cell_num);
        printf("| %-13d |", local->deletion_flag);
        printf("\n");
    }
}

void insert_for_modules(char **new_line)
{
    FILE *ptr;
    int len;

    ptr = fopen(MODULES_PATH, "a");
    len = get_records_count_in_file_modules(ptr);
    modules local;
    if (check_id_modules(new_line[0]) == 0)
        return (invalid_id_error());
    local.id = atoi(new_line[0]);
    strcpy(local.module_name, new_line[1]);
    local.mem_level_modules = atoi(new_line[2]);
    local.cell_num = atoi(new_line[3]);
    local.deletion_flag = atoi(new_line[4]);
    write_record_in_file_modules(ptr, &local, len);
    fclose(ptr);
}

int check_id_modules(char *id)
{
    modules local;
    FILE *ptr;
    int len;

    ptr = fopen(MODULES_PATH, "r");
    len = get_records_count_in_file_modules(ptr);
    for (int i = 0; i < len; i++)
    {
        local = read_record_from_file_modules(ptr, i);
        if (local.id == atoi(id))
        {
            fclose(ptr);
            return (0);
        }
    }
    fclose(ptr);
    return (1);
}

void write_record_in_file_modules(FILE *pfile, modules *record_to_write, int index) {
    int offset;
    
    offset = index * sizeof(modules);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(modules), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

void update_for_modules(char **old, char **new) {
    modules where;

    if (strcmp(new[0], "") != 0)
        return (invalid_id_error());
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
    int len = get_records_count_in_file_modules(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file_modules(ptr, i);
        if (compare_for_update(&local, &where) == 1) {
            update_record_modules(ptr, &local, &change, i);
        }
    }
    fclose(ptr);
}

void update_record_modules(FILE *pfile, modules *local, modules *change, int index) {
    int offset = index * sizeof(modules);
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
    fwrite(local, sizeof(modules), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}


int compare_for_update(modules *local, modules *where) {
    if ((where->id != -1) && (local->id == where->id)) {
        return 1;
    }
    if ((where->module_name[0] != '\0') && (strcmp(local->module_name, where->module_name) == 0)) {
        return 1;
    }
    if ((where->mem_level_modules != -1) && (local->mem_level_modules == where->mem_level_modules)) {
        return 1;
    }
    if ((where->cell_num != -1) && (local->cell_num == where->cell_num)) {
        return 1;
    }
    if ((where->deletion_flag != -1) && (local->deletion_flag == where->deletion_flag)) {
        return 1;
    }
    return 0;
}

int get_records_count_in_file_modules(FILE *pfile) {
    return get_file_size_in_bytes_modules(pfile) / sizeof(modules);
}

int get_file_size_in_bytes_modules(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return (size);
}

void delete_for_modules(char **array) 
{
    FILE *stream;
    int check_field = 5;
    char temp[30];
    temp[0] = '-';
    temp[1] = '\0';
    for (int i = 0; i < 5; i++) {
        if (strlen(array[i]) == 0) {
            continue;
        } else if (!strcmp(array[i], "*")) {
            continue;
        } else {
            check_field = i;
            strcpy(temp, array[i]);
        }
    }
    stream = fopen(MODULES_PATH, "rb+");
    int size = get_records_count_in_file_modules(stream);
    int counter = 0;
    int top_index;
    modules previous, local;
    for (int i = 0; i < size; i++) {
        local = read_record_from_file_modules(stream, i);
        if (compare_modules(&local, check_field, temp) == 1) {
            top_index = get_records_count_in_file_modules(stream);
            for (int j = i; j < top_index - 1; j++) {
                previous = read_record_from_file_modules(stream, j + 1);
                write_record_in_file_modules(stream, &previous, j);
            }
            counter++;
            size--;
        }
    }
    fclose(stream);
}
