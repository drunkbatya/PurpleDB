// Copyright [2022] <drunkbatya>

#include "create.h"

// see t_datatype in structure.h .
t_datatype parse_datatype(char *str)
{
    if (strcmp(str, "integer") == 0)
        return (integer);
    if (strcmp(str, "string") == 0)
        return (string);
    return (error);
}

// To shrink code length
uint8_t make_create_table_free(FILE *fptr, t_header *hptr, uint8_t return_code)
{
    safe_free(hptr);
    safe_fclose(fptr);
    return (return_code);
}

// Write first byte of file with number of columns in table.
// Max size is sizeof(uint8_t) - 255 columns.
// Type defined by COLUMN_COUNTER in structure.h .
uint8_t write_column_count(char *file_path, COLUMN_COUNTER column_count)
{
    FILE *ptr;

    ptr = fopen(file_path, "wx");
    if (ptr == NULL)
        return (0);
    if (!write_record_in_file(ptr, 0, sizeof(COLUMN_COUNTER), &column_count))
    {
        safe_fclose(ptr);
        return (0);
    }
    safe_fclose(ptr);
    return (1);
}

// Create table
// Expected count of arrays in arr = 1 + (2 * column_count).
// Column count value will be located in first byte (prob. bytes)
// in the beginning of the file. Column count must be > 0.
// Arr format: [table_name] [column 1 name] [column 1 type] (etc..).
// For avaliable types see t_datatype in structure.h .
uint8_t create_table(char **arr, int column_count)
{
    int count;
    int index;
    FILE *ptr;
    t_header *header;
    char file_path[strlen(arr[0]) + 2];

    count = 0;
    index = 1;  // to skip table_name and to itterate by pairs
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
        if (!write_record_in_file(ptr, ((count + sizeof(COLUMN_COUNTER)) \
                        * sizeof(t_header)), sizeof(t_header), header))
            return (make_create_table_free(ptr, header, 0));
        safe_free(header);
        count++;
        index+=2;
    }
    safe_fclose(ptr);
    return (1);
}