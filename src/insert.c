// Copyright [2022] <drunkbatya>

#include "insert.h"

uint8_t read_column_count(char *file_path)
{
    FILE *ptr;
    uint8_t *column_count_ptr;
    uint8_t column_count;

    ptr = fopen(file_path, "r");
    if (ptr == NULL)
        return (0);
    column_count_ptr = read_record_from_file(ptr, 0, sizeof(uint8_t));
    if (column_count_ptr == NULL)
    {
        safe_fclose(ptr);
        return (0);
    }
    column_count = *column_count_ptr;
    safe_fclose(ptr);
    safe_free(column_count_ptr);
    return (column_count);
}

uint8_t insert(char **arr)
{
    char file_path[strlen(arr[0]) + 2];
    uint8_t column_count;

    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    column_count = read_column_count(file_path);
    printf("Column count: %d\n", column_count);
    return (1);
}
