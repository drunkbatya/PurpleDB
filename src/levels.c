// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "shared.h"
#include "levels.h"

void select_for_levels(char **field, char **where)
{
    int identifier;
    int counter;
    int check_field;
    int len;
    char temp[30];
    FILE *ptr;
    levels local;

    counter = 0;
    check_field = 5;
    temp[0] = '-';
    ptr = fopen(LEVELS_PATH, "r");
    len = get_records_count_in_file_levels(ptr);
    for (int i = 0; i < 3; i++)  // Identifier = num of column to display
    {
        if (field[i][0] == '*')
        {
            identifier = 3;
            break;
        }
        if (field[i][0] == '1')
        {
            identifier = i;
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(where[i], "") == 0)
        {
            continue;
        } else
        {
            check_field = i;
            strcpy(temp, where[i]);
        }
    }
    for (int i = 0; i < len; i++) {
        local = read_record_from_file_levels(ptr, i);
        if (compare_levels(&local, check_field, temp))
        {
            counter++;
            if (counter == 1)
            {
                print_mask_levels(identifier);
            }            
            print_struct_levels(&local, identifier);
        }
    }
    print_outro_levels(identifier);
    fclose(ptr);
}

void print_mask_levels(int identifier)
{
    if (identifier == 0)
    {
        printf(" ------------------\n");
        printf("| mem_level_levels |\n");
        printf("|------------------|\n");
    } else if (identifier == 1)
    {
        printf(" -------------\n");
        printf("| cell_amount |\n");
        printf(" -------------\n");
    } else if (identifier == 2)
    {
        printf(" --------------\n");
        printf("| protect_flag |\n");
        printf(" --------------\n");
    } else if (identifier == 3)
    {
        printf(" -----------------------------------------------\n");
        printf("| mem_level_levels | cell_amount | protect_flag |\n");
        printf("|-----------------------------------------------|\n");
    }
}

void print_outro_levels(int identifier)
{
    if (identifier == 0)
        printf(" ------------------\n");
    if (identifier == 1)
        printf(" -------------\n");
    if (identifier == 2)
        printf(" --------------\n");
    if (identifier == 3)
        printf(" -----------------------------------------------\n");
}

int compare_levels(levels *local, int check_field, char *temp)
{
    if ((check_field == 5) && (temp[0] == '-'))
        return (1);
    if ((check_field == 0) && (local->mem_level_levels == atoi(temp)))
        return (1);
    if ((check_field == 1) && (local->cell_amount == atoi(temp)))
        return (1);
    if ((check_field == 2) && (local->protect_flag == atoi(temp)))
        return (1);
    return (0);
}

levels read_record_from_file_levels(FILE *pfile, int index)
{
    int offset;

    offset = index * sizeof(levels);
    fseek(pfile, offset, SEEK_SET);
    levels record;
    fread(&record, sizeof(levels), 1, pfile);
    rewind(pfile);
    return (record);
}

int get_file_size_in_bytes_levels(FILE *pfile)
{
    int size;

    size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return (size);
}

void print_struct_levels(levels *local, int identifier)
{
    if (identifier == 0)
    {
        printf("| %-16d |\n", local->mem_level_levels);
    } else if (identifier == 1)
    {
        printf("| %-11d |\n", local->cell_amount);
    } else if (identifier == 2)
    {
        printf("| %-12d |\n", local->protect_flag);
    } else if (identifier == 3)
    {
        printf("| %-16d ", local->mem_level_levels);
        printf("| %-11d ", local->cell_amount);
        printf("| %-12d |", local->protect_flag);
        printf("\n");
    }
}

int check_id_levels(char *id)
{
    levels local;
    FILE *ptr;
    int len;

    ptr = fopen(LEVELS_PATH, "r");
    len = get_records_count_in_file_levels(ptr);
    for (int i = 0; i < len; i++)
    {
        local = read_record_from_file_levels(ptr, i);
        if (local.mem_level_levels == atoi(id))
        {
            fclose(ptr);
            return (0);
        }
    }
    fclose(ptr);
    return (1);
}

void insert_for_levels(char **new_line)
{
    int len;
    FILE *ptr;

    ptr = fopen(LEVELS_PATH, "a");
    len = get_records_count_in_file_levels(ptr);
    levels local;
    if (check_id_levels(new_line[0]) == 0)
        return (invalid_id_error());
    local.mem_level_levels = atoi(new_line[0]);
    local.cell_amount = atoi(new_line[1]);
    local.protect_flag = atoi(new_line[2]);
    write_record_in_file_levels(ptr, &local, len);
    fclose(ptr);
}

void write_record_in_file_levels(FILE *pfile, levels *record_to_write, int index)
{
    int offset;

    offset = index * sizeof(levels);
    fseek(pfile, offset, SEEK_SET);
    fwrite(record_to_write, sizeof(levels), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

void update_for_levels(char **where_ar, char **new_values)
{
    int len;
    FILE *ptr;
    levels where;
    levels local;
    levels change;

    ptr = fopen(LEVELS_PATH, "r+b");
    len = get_records_count_in_file_levels(ptr);
    if (strcmp(where_ar[0], "") != 0)
        where.mem_level_levels = atoi(where_ar[0]);
    else
        where.mem_level_levels = -1;

    if (strcmp(where_ar[1], "") != 0)
        where.cell_amount = atoi(where_ar[1]);
    else
        where.cell_amount = -1;

    if (strcmp(where_ar[2], "") != 0)
        where.protect_flag = atoi(where_ar[2]);
    else
        where.protect_flag = -1;

    if (strcmp(new_values[0], "") != 0)
        change.mem_level_levels = atoi(new_values[0]);
    else
        change.mem_level_levels = -1;

    if (strcmp(new_values[1], "") != 0)
        change.cell_amount = atoi(new_values[1]);
    else
        change.cell_amount = -1;

    if (strcmp(new_values[2], "") != 0)
        change.protect_flag = atoi(new_values[2]);
    else
        change.protect_flag = -1;

    for (int i = 0; i < len; i++) {
        local = read_record_from_file_levels(ptr, i);
        if (compare_for_update_levels(&local, &where))
            update_record_levels(ptr, &local, &change, i);
    }
    fclose(ptr);
}

void update_record_levels(FILE *pfile, levels *local, levels *change, int index) {
    int offset;
    
    offset = index * sizeof(levels);
    fseek(pfile, offset, SEEK_SET);
    if (change->mem_level_levels != -1)
        local->mem_level_levels = change->mem_level_levels;
    if (change->cell_amount != -1)
        local->cell_amount = change->cell_amount;
    if (change->protect_flag != -1)
        local->protect_flag = change->protect_flag;
    fwrite(local, sizeof(levels), 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

int compare_for_update_levels(levels *local, levels *where) {
    if ((where->mem_level_levels != -1) && (local->mem_level_levels == where->mem_level_levels))
        return (1);
    if ((where->cell_amount != -1) && (local->cell_amount == where->cell_amount))
        return (1);
    if ((where->protect_flag != -1) && (local->protect_flag == where->protect_flag))
        return (1);
    return (0);
}

int get_records_count_in_file_levels(FILE *pfile) {
    return (get_file_size_in_bytes_levels(pfile) / sizeof(levels));
}
