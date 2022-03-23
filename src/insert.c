#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "shared.h"
#include "functions.h"


int get_records_count_in_file(FILE *pfile);
modules read_record_from_file(FILE *pfile, int index);
int get_file_size_in_bytes(FILE *pfile);
void write_record_in_file(FILE *pfile, modules *record_to_write, int index);


void insert_for_modules(char **new_line) {
    int flag = check_id(new_line[0]);
    if (flag == 0) {
        invalid_id_error();
        return;
    }
    modules local;
    local.id = atoi(new_line[0]);
    for (int i = 0; i < (int)strlen(new_line[1]); i++) {
        local.module_name[i] = new_line[1][i];
    }
    local.mem_level_modules = atoi(new_line[2]);
    local.cell_num = atoi(new_line[3]);
    local.deletion_flag = atoi(new_line[4]);
    FILE *ptr = fopen(MODULES_PATH, "a");
    int len = get_records_count_in_file(ptr);
    write_record_in_file(ptr, &local, len);
    fclose(ptr);
}


int check_id(char * id) {
    modules local;
    int counter = 0;
    FILE *ptr = fopen(MODULES_PATH, "r");
    int len = get_records_count_in_file(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file(ptr, i);
        if (local.id == atoi(id)) {
            fclose(ptr);
            return 0;
        }
    }
    fclose(ptr);
    return 1;
}


// Function of writing a record of the specified type to the file at the specified serial number.
void write_record_in_file(FILE *pfile, modules *record_to_write, int index) {
    // Calculation of the offset at which the required record should be located from the beginning of the file.
    int offset = index * sizeof(modules);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Write a record of the specified type to a file.
    fwrite(record_to_write, sizeof(modules), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}

int get_records_count_in_file(FILE *pfile) {
    return get_file_size_in_bytes(pfile) / sizeof(modules);
}

// Function of reading a record of a given type from a file by its serial number.
modules read_record_from_file(FILE *pfile, int index) {
    // Calculation of the offset at which desired entry should be located from the beginning of the file.
    int offset = index * sizeof(modules);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);

    // Reading a record of the specified type from a file.
    modules record;
    fread(&record, sizeof(modules), 1, pfile);

    // For safety reasons, we return the file position pointer to the beginning of the file.
    rewind(pfile);

    // Return read record
    return record;
}

// Function to get file size in bytes.
int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);    // Move the position pointer to the end of the file.
    size = ftell(pfile);          // Read the number of bytes from the beginning of the file to the current position pointer.
    rewind(pfile);                // For safety reasons, move the position pointer back to the beginning of the file.
    return size;
}


