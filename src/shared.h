// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#define LEVELS "levels"
#define MODULES "modules"
#define STATUS "status_events"

#define LEVELS_PATH "../materials/master_levels.db"
#define MODULES_PATH "../materials/master_modules.db"
#define STATUS_PATH "../materials/master_status_events.db"

void select(char **lecs);
void insert(char **lecs);
void update(char **lecs);
void delete(char **lecs);

int check_if_table_exists(char *table_name);
int validate_int(char *strint);

int assign_modules_select(char **lecs, char **select);
int assign_modules_where(char *where_col, char *where_val, char **where);
int assign_modules_update(char *update_col, char *update_val, char **update);
int validate_modules(char **lecs);

int assign_levels_update(char *update_col, char *update_val, char **update);
int assign_levels_select(char **lecs, char **select);
int assign_levels_where(char *where_col, char *where_val, char **where);
int validate_levels(char **lecs);

int assign_status_update(char *update_col, char *update_val, char **update);
int assign_status_select(char **lecs, char **select);
int assign_status_where(char *where_col, char *where_val, char **where);
int validate_status(char **lecs);

#endif  // SRC_SHARED_H_
