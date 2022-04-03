// Copyright [2022] <drunkbatya>

#include "select.h"

void print_describe_table_select(char **arr, COLUMN_COUNTER columns)
{
    FILE *fptr;
    char file_path[strlen(arr[0]) + 2];
    t_header *column;
    COLUMN_COUNTER column_count;

    column_count = 0;
    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    fptr = fopen(file_path, "r");
    if (fptr == NULL)
        return;
    while (column_count < columns)
    {
        column = read_record_from_file(fptr, sizeof(COLUMN_COUNTER) \
                + (column_count * sizeof(t_header)), sizeof(t_header));
        if (column == NULL)
            return;
        printf("%s", column->column_name);
        if (column_count == columns - 1)
            printf("\n---\n");
        else
            printf("|");
        column_count++;
    }
}

// Select data from existing table
// Expected count of array in arr = 5.
// Arr format:
//   [table_name] [column_name]
//   [operand - column name] [operator] [operand - column value].
// To use SELECT without WHERE leave [operand - column name] empty.
// To SELECT * put asterisk to [column_name].
uint8_t p_select(char **arr)
{
    char file_path[strlen(arr[0]) + 2];
    char *string_ptr;
    FILE *fptr;
    uint16_t rows;
    uint16_t offset;
    uint16_t row_count;
    t_header *column;
    INTEGER *integer_ptr;
    COLUMN_COUNTER columns;
    COLUMN_COUNTER column_count;

    row_count = 0;
    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    fptr = fopen(file_path, "a+");
    if (fptr == NULL)
        return (0);
    rows = get_rows_count(file_path);
    columns = read_column_number(file_path);
    if (!rows || !columns)
    {
        safe_fclose(fptr);
        return (0);
    }
    // check_column_name_exit(arr[1]); TODO(drunkbatya)
    offset = sizeof(COLUMN_COUNTER) + (sizeof(t_header) * columns);
    while (row_count < rows)
    {
        column_count = 0;
        if (row_count == 0)
            print_describe_table_select(arr, columns);
        while (column_count < columns)
        {
            column = read_record_from_file(fptr, sizeof(COLUMN_COUNTER) \
                    + (column_count * sizeof(t_header)), sizeof(t_header));
            if (column == NULL)
                return (0);
            if (column->datatype == integer)
            {
                integer_ptr = read_record_from_file(fptr, offset, sizeof(INTEGER));
                printf("%d", *integer_ptr);
                offset += sizeof(INTEGER);
                safe_free(integer_ptr);
            }
            if (column->datatype == string)
            {
                string_ptr = read_record_from_file(fptr, offset, STRING_SIZE);
                printf("%s", string_ptr);
                offset += STRING_SIZE;
                safe_free(string_ptr);
            }
            if (column_count == columns - 1)
                printf("\n");
            else
                printf("|");
            safe_free(column);
            column_count++;
        }
        row_count++;
    }
    return (1);
}
