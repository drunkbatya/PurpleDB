#ifndef SRC_FUNCTIONS_H_
#define SRC_FUNCTIONS_H_

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
void insert_for_modules(char **new_line);
void write_record_in_file(FILE *pfile, modules *record_to_write, int index);
int check_id(char * id);
void update_for_modules(char **old, char **new);
void update_record(FILE *pfile, modules *local, modules *change, int index);
int compare_for_update (modules *local, modules *where);


#endif  // SRC_FUNCTIONS_H_
