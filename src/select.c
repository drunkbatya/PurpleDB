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
        printf("%s ", column->column_name);
        if (column_count == columns - 1)
            printf("\n");
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
    uint16_t rows;
    uint16_t row_count;
    COLUMN_COUNTER columns;

    row_count = 0;
    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    rows = get_rows_count(file_path);
    columns = read_column_count(file_path);
    if (!rows)
        return (0);
    if (!columns)
        return (0);
    // check_column_name_exit(arr[1]); TODO(drunkbatya)
    while (row_count < rows)
    {
        if (row_count == 0)
            print_describe_table_select(arr, columns);
        row_count++;
    }
    return (1);
}
