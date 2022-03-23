#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tModules {
    int id;
    char module_name[30];
    int mem_level_modules;
    int cell_num;
    int deletion_flag;
} modules;

typedef struct tLevels {
    int mem_level_levels;
    int cell_amount;
    int protect_flag;
} levels;

typedef struct tStatus {
    int event_id;
    int module_id;
    int new_status;
    char status_change_date[11];
    char status_change_time[9];
} status_events;


int compare (modules *local, char *id, char *module_name, char *mem_level_modules, char *cell_num, char *deletion_flag);
void select_for_modules(char *id, char *module_name, char *mem_level_modules, char *cell_num, char *deletion_flag);
int get_records_count_in_file(FILE *pfile);
modules read_record_from_file(FILE *pfile, int index);
void print_struct(modules *local);
void insert_for_modules(char *id, char *module_name, char *mem_level_modules, char *cell_num, char *deletion_flag);
int get_file_size_in_bytes(FILE *pfile);
void write_record_in_file(FILE *pfile, modules *record_to_write, int index);


int main() {
    char id[] = "1";
    char module_name[] = "*";
    char mem_level_modules[] = "1";
    char cell_num[] = "1";
    char deletion_flag[] = "1";
    insert_for_modules(id, module_name, mem_level_modules, cell_num, deletion_flag);
    return 0;
}


void insert_for_modules(char *id, char *module_name, char *mem_level_modules, char *cell_num, char *deletion_flag) {
    modules local;
    local.id = atoi(id);
    for (int i = 0; i < (int)strlen(module_name); i++) {
        local.module_name[i] = module_name[i];
    }
    local.mem_level_modules = atoi(mem_level_modules);
    local.cell_num = atoi(cell_num);
    local.deletion_flag = atoi(deletion_flag);
    FILE *ptr = fopen("../materials/master_modules.db", "a");
    int len = get_records_count_in_file(ptr);
    write_record_in_file(ptr, &local, len);
    fclose(ptr);
    FILE *read = fopen("../materials/master_modules.db", "r");
    modules new;
    for (int i = 0; i < len + 1; i++) {
        new = read_record_from_file(read, i);
            print_struct(&new);
    }
    fclose(read);
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
    int offset = index * sizeof(modules);          // оффсет - сдвиг??
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

void print_struct(modules *local) {
    printf("%d ", local->id);
    printf("%s ", local->module_name);
    printf("%d ", local->mem_level_modules);
    printf("%d ", local->cell_num);
    printf("%d ", local->deletion_flag);
    printf("\n");
}

