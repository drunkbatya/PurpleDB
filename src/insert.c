// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "insert.h"

// Convert string str to int value, and insert to table via fptr.
// Ranges - sizeof(int32_t) / 2 - from -2147483648 to +2147483647.
// Type of int defined by INTEGER in structure.h .
uint8_t insert_integer(char *str, FILE *fptr, uint32_t *offset)
{
    INTEGER num;

    num = atoi(str);  //TODO(grusnydance): check if not an int (atoi = 0)
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
        return (0);  // TODO(drunkbatya): add exeption
    memset(arr, 0, STRING_SIZE);
    strcpy(arr, str);
    if (write_record_in_file(fptr, *offset, STRING_SIZE, arr) == 0)
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
    t_header *header;

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
    t_header **headers_struct = calloc(column_number, sizeof(t_header *));
    
    count = 1;
    offset = sizeof(COLUMN_COUNTER);  // Pointer to the data beginning
    while (count < column_number + 1)  // Writing headers structure
    {
        header = read_header_from_file(fptr, offset, sizeof(t_header));
        if (header == NULL)
            make_insert_free(fptr, header, 0);
        headers_struct[count - 1] = header;
        count++;
        offset = offset + sizeof(t_header);
    }
    
    fseek(fptr, 0, SEEK_END);
    offset = ftell(fptr);
    count = 1;
    while (count < column_number + 1)
    {
        if (headers_struct[count - 1]->datatype == integer)
        {
            insert_integer(arr[count], fptr, &offset);  //TODO: add checks for success
        }
        if (headers_struct[count - 1]->datatype == string)
        {
            insert_string(arr[count], fptr, &offset);
        }
        count++;
    }

    count = 0;
    while (count < column_number)  // TODO: one function for freeing
    {
        safe_free(headers_struct[count]);
        count++;
    }
    free(headers_struct);

    safe_fclose(fptr);
    return;
}
