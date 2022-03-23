#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

#define LEVELS "levels"
#define MODULES "modules"
#define STATUS "status_events"

#define LEVELS_PATH "../materials/master_levels.db"
#define MODULES_PATH "../materials/master_modules.db"
#define STATUS_PATH "../materials/master_status_events.db"

int select(char **lecs);
int check_if_table_exists(char *table_name);
void assign_modules_structure(char **lecs);
void assign_modules_select(char **lecs, char **select);
void assign_modules_where(char **lecs, char **where);
void print_mock(char **select, char **where);

#endif  // SRC_SHARED_H_
