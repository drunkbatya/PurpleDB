#include <stdio.h>
#include <stdlib.h>

typedef struct tModules{
    int id;
    char module_name[30];
    int mem_level_modules;
    int cell_num;
    int deletion_flag;
} modules;

typedef struct tLevels{
    int mem_level_levels;
    int cell_amount;
    int protect_flag;
} levels;

typedef struct tStatus{
    int event_id;
    int module_id;
    int new_status;
    char status_change_date[11];
    char status_change_time[9];
} status_events;

int main() {


}


select_for_modules(int id, char * module_name, int mem_level, int ) {
    if (read_binary_file(db) == 0) {
        free(filename);
        printf("n/a");
    }
}



int read_binary_file(char *filename) {
    struct my_struct record;
    FILE *ptr = fopen(filename, "r");
    if (ptr == NULL) {
        return 0;
    } else {
        int len = get_records_count_in_file(ptr);
        for (int i = 0; i < len; i++) {
            record = read_record_from_file(ptr, i);
            print_struct(&record);
        }
        fclose(ptr);
    }
    return 1;
}
