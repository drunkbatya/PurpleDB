// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "insert.h"

// Convert string str to int value, and insert to table via fptr.
// Ranges - sizeof(int32_t) / 2 - from -2147483648 to +2147483647.
// Type of int defined by INTEGER in structure.h .
uint8_t insert_integer(char *str, FILE *fptr, uint32_t *offset)
{
    INTEGER num;

    num = atoi(str);  // TODO(grusnydance): check if not an int (atoi = 0)
    if (write_record_in_file(fptr, *offset, sizeof(INTEGER), &num) == 0)
        return (0);
    *offset += sizeof(INTEGER);
    return (1);
}

// Insert string str to table via fptr.
// Data will be copied to new zeroed array and written to table.
// Size of array defined by STRING_SIZE in structure.h .
// Throws exeption if input string size greater then (STRING_SIZE - 1)
uint8_t insert_string(char *str, FILE *fptr, uint32_t *offset)
{
    char arr[STRING_SIZE];

    if (strlen(str) > STRING_SIZE - 1)
        return (0);  // TODO(drunkbatya): add exception
    memset(arr, 0, STRING_SIZE);
    strcpy(arr, str);
    if (write_record_in_file(fptr, *offset, STRING_SIZE, arr) == 0)
        return (0);
    *offset += STRING_SIZE;
    return (1);
}

// Insert data to existing table.
// Expected count of array in arr = 1 + column_count.
// Column count value is located in first byte (prob. bytes)
// in the beginning of the file. Column count must be > 0.
// Arr format: [table_name] [column 1 value] ([column 2 value]) (etc..).
void insert(char **arr)
{
    FILE *fptr;
    char file_path[strlen(arr[0]) + 4];
    uint32_t offset;
    COLUMN_COUNTER count;
    COLUMN_COUNTER column_number;
    int *reserve_array;

    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    if (check_if_table_exists(file_path) == 0)
        return;

    column_number = read_column_number(file_path);
    if (column_number < 1)
    {
        error_null_column_number();
        return;
    }

    fptr = fopen(file_path, "rb+");

    reserve_array = calloc(column_number, sizeof(int *));

    get_headers_structure(fptr, column_number, reserve_array);  // TODO(koterin): THIS BITCH is fine now

    fseek(fptr, 0, SEEK_END);
    offset = ftell(fptr);
    count = 1;

    while (count <= column_number)
    {
        if (reserve_array[count - 1] == integer)
        {
            if (insert_integer(arr[count], fptr, &offset) == 0)  // TODO(koterin): add checks for success
                break;
        }
        if (reserve_array[count - 1] == string)
        {
            if (insert_string(arr[count], fptr, &offset) == 0)
                break;
        }
        count++;
    }

    safe_fclose(fptr);
    free(reserve_array);
    return;
}