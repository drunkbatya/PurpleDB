// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

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
#endif  // SRC_MAIN_H_
