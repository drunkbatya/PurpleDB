// Copyright [2022] <drunkbatya>

#include "create.h"

t_datatype parse_datatype(char *str)
{
    if (strcmp(str, "integer"))
        return (integer);
    if (strcmp(str, "string"))
        return (string);
    return (error);
}

uint8_t make_create_table_free(FILE *fptr, t_header *hptr, uint8_t return_code)
{
    safe_free(hptr);
    safe_fclose(fptr);
    return (return_code);
}

uint8_t write_column_count(char *file_path, uint8_t column_count)
{
    FILE *ptr;

    ptr = fopen(file_path, "wx");
    if (ptr == NULL)
        return (0);
    if (!write_record_in_file(ptr, 0, sizeof(uint8_t), &column_count))
    {
        safe_fclose(ptr);
        return (0);
    }
    safe_fclose(ptr);
    return (1);
}

uint8_t create_table(char **arr, int column_count)
{
    int count;
    int index;
    FILE *ptr;
    t_header *header;
    char file_path[strlen(arr[0]) + 2];

    count = 0;
    index = 1;
    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    if (!write_column_count(file_path, column_count))
        return (0);
    ptr = fopen(file_path, "a");
    if (ptr == NULL)
        return (0);
    while (count < column_count)
    {
        header = (t_header *)malloc(sizeof(t_header));
        if (header == NULL)
            return (make_create_table_free(ptr, header, 0));
        strcpy(header->column_name, arr[index]);
        header->datatype = parse_datatype(arr[index + 1]);
        if (header->datatype == error)
            return (make_create_table_free(ptr, header, 0));
        if (!write_record_in_file(ptr, count + COLUMN_COUNT_SHIFT, sizeof(t_header), header))
            return (make_create_table_free(ptr, header, 0));
        safe_free(header);
        count++;
        index+=2;
    }
    safe_fclose(ptr);
    return (1);
}

