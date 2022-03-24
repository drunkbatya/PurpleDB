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

void update_for_modules(char **old, char **new);
void update_record(FILE *pfile, modules *local, modules *change, int index);
int compare_for_update (modules *local, modules *where);
int get_records_count_in_file(FILE *pfile);
modules read_record_from_file(FILE *pfile, int index);
int get_file_size_in_bytes(FILE *pfile);
void print_struct(modules *local);



int main() {

    char *select[5];
    char *id = "9";
    char *name = "";
    char *mem_level_modules = "";
    char *cell_num = "";
    char *deletion_flag = "";
    select[0] = id;
    select[1] = name;
    select[2] = mem_level_modules;
    select[3] = cell_num;
    select[4] = deletion_flag;
    char *where[5];
    char *idw = "";
    char *namew = "";
    char *mem_level_modulesw = "";
    char *cell_numw = "";
    char *deletion_flagw = "100";
    where[0] = idw;
    where[1] = namew;
    where[2] = mem_level_modulesw;
    where[3] = cell_numw;
    where[4] = deletion_flagw;
    update_for_modules(select, where);
    return 0;
}

void update_for_modules(char **old, char **new) {
    modules where;
    if (strcmp(old[0], "") != 0) {
        where.id = atoi(old[0]);
    } else {
        where.id = -1;
    }
    if (strcmp(old[1], "") != 0) {
        int i;
        for (i = 0; i < (int)strlen(old[1]); i++) {
            where.module_name[i] = old[1][i];
        }
        where.module_name[(int)strlen(old[1])] = '\0';
    } else {
        where.module_name[0] = '\0';
    }
    if (strcmp(old[2], "") != 0) {
        where.mem_level_modules = atoi(old[2]);
    } else {
        where.mem_level_modules = -1;
    }
    if (strcmp(old[3], "") != 0) {
        where.cell_num = atoi(old[3]);
    } else {
        where.cell_num = -1;
    }
    if (strcmp(old[4], "") != 0) {
        where.deletion_flag = atoi(old[4]);
    } else {
        where.deletion_flag = -1;
    }

    modules change;
    if (strcmp(new[0], "") != 0) {
        change.id = atoi(new[0]);
    } else {
        change.id = -1;
    }
    if (strcmp(new[1], "") != 0) {
        int i;
        for (i = 0; i < (int)strlen(new[1]); i++) {
            change.module_name[i] = new[1][i];
        }
        change.module_name[(int)strlen(new[1])] = '\0';
    } else {
        change.module_name[0] = '\0';
    }
    if (strcmp(new[2], "") != 0) {
        change.mem_level_modules = atoi(new[2]);
    } else {
        change.mem_level_modules = -1;
    }
    if (strcmp(new[3], "") != 0) {
        change.cell_num = atoi(new[3]);
    } else {
        change.cell_num = -1;
    }
    if (strcmp(new[4], "") != 0) {
        change.deletion_flag = atoi(new[4]);
    } else {
        change.deletion_flag = -1;
    }

    FILE *ptr = fopen("../materials/master_modules.db", "r+b");
    modules local;
    int len = get_records_count_in_file(ptr);
    for (int i = 0; i < len; i++) {
        local = read_record_from_file(ptr, i);
        if (compare_for_update(&local, &where) == 1) {
            update_record(ptr, &local, &change, i);
        }
    }
    fclose(ptr);

    FILE *read = fopen("../materials/master_modules.db", "r");
    modules check;
    for (int i = 0; i < len + 1; i++) {
        check = read_record_from_file(read, i);
            print_struct(&check);
    }
    fclose(read);
}

void update_record(FILE *pfile, modules *local, modules *change, int index) {
    // Calculation of the offset at which the required record should be located from the beginning of the file.
    int offset = index * sizeof(modules);
    // Move the position pointer to the calculated offset from the beginning of the file.
    fseek(pfile, offset, SEEK_SET);
    if (change->id != -1) {
        local->id = change->id;
    }
    if (change->module_name[0] != '\0') {
        int i;
        for (i = 0; i < (int)strlen(change->module_name); i++) {
            local->module_name[i] = change->module_name[i];
        }
        local->module_name[i] = '\0';
    }
    if (change->mem_level_modules != -1) {
        local->mem_level_modules = change->mem_level_modules;
    }
    if (change->cell_num != -1) {
        local->cell_num = change->cell_num;
    }
    if (change->deletion_flag != -1) {
        local->deletion_flag = change->deletion_flag;
    }
    // Write a record of the specified type to a file.
    fwrite(local, sizeof(modules), 1, pfile);

    // Just in case, force the I/O subsystem to write the contents of its buffer to a file right now.
    fflush(pfile);

    // For safety reasons, return the file position pointer to the beginning of the file.
    rewind(pfile);
}


int compare_for_update (modules *local, modules *where) {
    if ((where->id != -1) && (local->id != where->id)) {
        return 0;
    }
    if ((where->module_name[0] != '\0') && (strcmp(local->module_name, where->module_name) != 0)) {
        return 0;
    }
    if ((where->mem_level_modules != -1) && (local->mem_level_modules != where->mem_level_modules)) {
        return 0;
    }
    if ((where->cell_num != -1) && (local->cell_num != where->cell_num)) {
        return 0;
    }
    if ((where->deletion_flag != -1) && (local->deletion_flag != where->deletion_flag)) {
        return 0;
    }
    return 1;
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

