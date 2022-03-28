// Copyright [2022] <drunkbatya>

#include "select.h"

// Select data from existing table
// Expected count of array in arr = 5.
// Arr format:
//   [table_name] [column_name]
//   [operand - column name] [operator] [operand - column value].
// To use SELECT without WHERE leave [operand - column name] empty.
uint8_t select(char **arr)
{
    char file_path[strlen(arr[0]) + 2];
    uint8_t column_count;

    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    column_count = read_column_count(file_path);
    return (0);
}
