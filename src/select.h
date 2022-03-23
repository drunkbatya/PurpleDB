#ifndef SRC_SELECT_H_
#define SRC_SELECT_H_

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

void select_for_modules(char **field, char **where);
int compare (modules *local, int check_field, char * temp);
int get_records_count_in_file(FILE *pfile);
modules read_record_from_file(FILE *pfile, int index);
int get_file_size_in_bytes(FILE *pfile);
void print_struct(modules *local, int identifier);

#endif  // SRC_SELECT_H_
