// Copyright [2022] <drunkbatya, koterin, grusnydance>

#include "update.h"

// Convert string str to int value, and insert to table via fptr.
uint8_t insert_integer_update(char *str, FILE *fptr, uint32_t offset)
{
    INTEGER num;

    num = atoi(str);  // TODO(grusnydance): check if not an int (atoi = 0)
    if (write_record_in_file(fptr, offset, sizeof(INTEGER), &num) == 0)
        return (0);
    return (1);
}

// Insert string str to table via fptr.
// Data will be copied to new zeroed array and written to table.
uint8_t insert_string_update(char *str, FILE *fptr, uint32_t offset)
{
    char arr[STRING_SIZE];

    if (strlen(str) > STRING_SIZE - 1)
        return (error_string_too_long(str, (STRING_SIZE - 1)));
    memset(arr, 0, STRING_SIZE);
    strcpy(arr, str);
    if (write_record_in_file(fptr, offset, STRING_SIZE, arr) == 0)
        return (0);
    return (1);
}

void change_values(uint16_t count, uint32_t offset1, uint32_t size1, \
FILE *fptr, int first_type, char **arr, int sec_type, int32_t diff, int32_t offset_of_whole_row)
{
    for (int i = 0; i < count; i++)
    {
        void *record = calloc(1, size1);
        fseek(fptr, offset1, SEEK_SET);
        fread(record, size1, 1, fptr);
        if (match_is_true(&first_type, record, arr[4], arr[5])) {
            rewind(fptr);
            if (sec_type == integer) {
                insert_integer_update(arr[2], fptr, offset1 - diff);
            }
            if (sec_type == string) {
                insert_string_update(arr[2], fptr, offset1 - diff);
            }
        }
        free(record);
        record = NULL;
        offset1 += offset_of_whole_row;
    }
}

// Update data in existing table.
// Arr format: [table_name] [name of column to update]
// [value to update] [where column name] [operator]
// [equals column value]
void update(char **arr)
{
    FILE *fptr;
    char file_path[strlen(arr[0]) + 4];
    uint32_t offset1;
    int first_type;
    uint32_t offset2;
    int sec_type;
    COLUMN_COUNTER column_number;
    uint32_t where_col_offset, col_to_update_offset;
    uint32_t offset_of_whole_row;
    uint16_t count;
    int32_t diff;
    int32_t size1;

    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    if (check_if_table_exists(file_path) == 0)
        return;
    column_number = read_column_number(file_path);
    if (column_number < 1) {
        error_null_column_number();
        return;
    }
    fptr = fopen(file_path, "r+");
    where_col_offset = find_offset_for_column(arr[3], fptr, column_number, &first_type);
    col_to_update_offset = find_offset_for_column(arr[1], fptr, column_number, &sec_type);
    offset_of_whole_row = find_offset_for_row(fptr, column_number);
    count = get_rows_count(file_path);
    offset1 = sizeof(COLUMN_COUNTER) + sizeof(t_header) * column_number + where_col_offset;
    offset2 = sizeof(COLUMN_COUNTER) + sizeof(t_header) * column_number + col_to_update_offset;
    diff = offset1 - offset2;
    size1 = get_size_by_datatype_simple(&first_type);
    change_values(count, offset1, size1, fptr, first_type,
         arr, sec_type, diff, offset_of_whole_row);
    safe_fclose(fptr);
    return;
}
