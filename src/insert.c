// Copyright [2022] <drunkbatya>

#include "insert.h"

// Read first byte of file to get number of columns in table.
// Max size is sizeof(uint8_t) - 255 columns.
// Type defined by COLUMN_COUNTER in structure.h .
COLUMN_COUNTER read_column_count(char *file_path)
{
    FILE *ptr;
    COLUMN_COUNTER *column_count_ptr;
    COLUMN_COUNTER column_count;

    ptr = fopen(file_path, "r");
    if (ptr == NULL)
        return (0);
    column_count_ptr = read_record_from_file(ptr, 0, sizeof(COLUMN_COUNTER));
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

// Convert string str to int value, and insert to table via fptr.
// Ranges - sizeof(int32_t) / 2 - from -2147483648 to +2147483647.
// Type of int defined by INTEGER in structure.h .
uint8_t insert_integer(char *str, FILE *fptr, uint16_t *offset)
{
    INTEGER integer;

    printf("Inserting INTEGER\n");
    integer = atoi(str);
    if (!write_record_in_file(fptr, *offset, sizeof(INTEGER), &integer))
        return (0);
    *offset += sizeof(INTEGER);
    return (1);
}

// Insert string str to table via fptr.
// Data will be copied to new zeroed array and written to table.
// Size of array defined by STRING_SIZE in structure.h .
// Throws exeption if input string size greater then (STRING_SIZE - 1)
uint8_t insert_string(char *str, FILE *fptr, uint16_t *offset)
{
    char arr[STRING_SIZE];

    printf("Inserting STRING\n");
    if (strlen(str) > STRING_SIZE - 1)
        return (0);  // TODO(drunkbatya): add exeption
    memset(arr, 0, STRING_SIZE);
    strcpy(arr, str);
    if (!write_record_in_file(fptr, *offset, STRING_SIZE, arr))
        return (0);
    *offset += STRING_SIZE;
    return (1);
}

// To shrink code length
uint8_t make_insert_free(FILE *fptr, t_header *hptr, uint8_t return_code)
{
    safe_fclose(fptr);
    safe_free(hptr);
    return (return_code);
}

// Insert data to existing table.
// Expected size of arr = 1 + column_count.
// Column count value is located in first byte (prob. bytes)
// in the beginning of the file. Column count must be > 0.
// Arr format: [table_name] [column 1 value] ([column 2 value]) (etc..).
uint8_t insert(char **arr)
{
    FILE *fptr;
    char file_path[strlen(arr[0]) + 2];
    uint8_t count;
    uint8_t column_count;
    uint16_t offset;
    t_header *column;

    count = 0;
    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    column_count = read_column_count(file_path);
    if (column_count < 1)
        return (0);
    fptr = fopen(file_path, "a+");
    if (fptr == NULL)
        return (0);
    offset = sizeof(COLUMN_COUNTER) + (sizeof(t_header) * column_count);
    while (count < column_count)
    {
        column = read_record_from_file(fptr, sizeof(COLUMN_COUNTER) \
                + (count * sizeof(t_header)), sizeof(t_header));
        if (column == NULL)
            make_insert_free(fptr, column, 0);
        if (column->datatype == integer)
        {
            if (!insert_integer(arr[count + 1], fptr, &offset))
                return (make_insert_free(fptr, column, 0));
        }
        if (column->datatype == string)
        {
            if (!insert_string(arr[count + 1], fptr, &offset))
                return (make_insert_free(fptr, column, 0));
        }
        safe_free(column);
        count++;
    }
    printf("Column count: %d\n", column_count);
    safe_fclose(fptr);
    return (1);
}
