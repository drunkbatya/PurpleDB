#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#define LEVELS "levels"
#define MODULES "modules"
#define STATUS "status_events"

#define LEVELS_PATH "../materials/master_levels.db"
#define MODULES_PATH "../materials/master_modules.db"
#define STATUS_PATH "../materials/master_status_events.db"

void select(char **lecs);
int check_if_table_exists(char *table_name);
int assign_modules_select(char **lecs, char **select);
int assign_modules_where(char *where_col, char *where_val, char **where);
void print_mock(char **select, char **where);
void insert(char **lecs);
int validate_modules(char **lecs);
int validate_int(char *strint);
void update(char **lecs);

#endif  // SRC_SHARED_H_
