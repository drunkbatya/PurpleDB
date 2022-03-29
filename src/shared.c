// Copyright [2022] <griselle, sparelis, laynadre>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "shared.h"
#include "modules.h"
#include "levels.h"
#include "status.h"

int check_if_table_exists(char *table_name)
{
    if (strcmp(table_name, LEVELS) == 0 || strcmp(table_name, MODULES) == 0
           || strcmp(table_name, STATUS) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int assign_levels_select(char **lecs, char **select) {
    if (strcmp(lecs[1], "*") == 0) {  // To select all columns
        for (int i = 0; i < 3; i++) {
            select[i] = lecs[1];
        }
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        select[i] = "";
    }

    if (strcmp(lecs[1], "mem_level_levels") == 0) {
        select[0] = "1";
        return 1;
    } else if (strcmp(lecs[1], "cell_amount") == 0) {
        select[1] = "1";
        return 1;
    } else if (strcmp(lecs[1], "protect_flag") == 0) {
        select[2] = "1";
        return 1;
    } else {
        error_unknown_column(lecs[1], lecs[0]);
        return 0;
    }
}

int assign_status_select(char **lecs, char **select) {
    if (strcmp(lecs[1], "*") == 0) {  // To select all columns
        for (int i = 0; i < 5; i++) {
            select[i] = lecs[1];
        }
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        select[i] = "";
    }

    if (strcmp(lecs[1], "event_id") == 0) {
        select[0] = "1";
        return 1;
    } else if (strcmp(lecs[1], "module_id") == 0) {
        select[1] = "1";
        return 1;
    } else if (strcmp(lecs[1], "new_status") == 0) {
        select[2] = "1";
        return 1;
    } else if (strcmp(lecs[1], "status_change_date") == 0) {
        select[3] = "1";
        return 1;
    } else if (strcmp(lecs[1], "status_change_time") == 0) {
        select[4] = "1";
        return 1;
    } else {
        error_unknown_column(lecs[1], lecs[0]);
        return 0;
    }
}

int assign_modules_select(char **lecs, char **select) {
    if (strcmp(lecs[1], "*") == 0) {  // To select all columns
        for (int i = 0; i < 5; i++) {
            select[i] = lecs[1];
        }
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        select[i] = "";
    }

    if (strcmp(lecs[1], "id") == 0) {
        select[0] = "1";
        return 1;
    } else if (strcmp(lecs[1], "module_name") == 0) {
        select[1] = "1";
        return 1;
    } else if (strcmp(lecs[1], "mem_level_modules") == 0) {
        select[2] = "1";
        return 1;
    } else if (strcmp(lecs[1], "cell_num") == 0) {
        select[3] = "1";
        return 1;
    } else if (strcmp(lecs[1], "deletion_flag") == 0) {
        select[4] = "1";
        return 1;
    } else {
        error_unknown_column(lecs[1], lecs[0]);
        return 0;
    }
}

int assign_levels_update(char *update_col, char *update_val, char **update) {
    for (int i = 0; i < 3; i++) {
        update[i] = "";
    }

    if (strcmp(update_col, "mem_level_levels") == 0) {
        update[0] = update_val;
        return 1;
    } else if (strcmp(update_col, "cell_amount") == 0) {
        update[1] = update_val;
        return 1;
    } else if (strcmp(update_col, "protect_flag") == 0) {
        update[2] = update_val;
        return 1;
    } else {
        error_unknown_condition(update_val);
        return 0;
    }
}

int assign_status_update(char *update_col, char *update_val, char **update) {
    for (int i = 0; i < 5; i++) {
        update[i] = "";
    }

    if (strcmp(update_col, "event_id") == 0) {
        update[0] = update_val;
        return 1;
    } else if (strcmp(update_col, "module_id") == 0) {
        update[1] = update_val;
        return 1;
    } else if (strcmp(update_col, "new_status") == 0) {
        update[2] = update_val;
        return 1;
    } else if (strcmp(update_col, "status_change_date") == 0) {
        update[3] = update_val;
        return 1;
    } else if (strcmp(update_col, "status_change_time") == 0) {
        update[4] = update_val;
        return 1;
    } else {
        error_unknown_condition(update_val);
        return 0;
    }
}

int assign_modules_update(char *update_col, char *update_val, char **update) {
    for (int i = 0; i < 5; i++) {
        update[i] = "";
    }

    if (strcmp(update_col, "id") == 0) {
        update[0] = update_val;
        return 1;
    } else if (strcmp(update_col, "module_name") == 0) {
        update[1] = update_val;
        return 1;
    } else if (strcmp(update_col, "mem_level_modules") == 0) {
        update[2] = update_val;
        return 1;
    } else if (strcmp(update_col, "cell_num") == 0) {
        update[3] = update_val;
        return 1;
    } else if (strcmp(update_col, "deletion_flag") == 0) {
        update[4] = update_val;
        return 1;
    } else {
        error_unknown_condition(update_val);
        return 0;
    }
}

int assign_levels_where(char *where_col, char *where_val, char **where) {
    if (strcmp(where_col, "*") == 0) {  // if no WHERE
        for (int i = 0; i < 3; i++) {
            where[i] = "";
        }
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        where[i] = "";
    }

    if (strcmp(where_col, "mem_level_levels") == 0) {
        where[0] = where_val;
        return 1;
    } else if (strcmp(where_col, "cell_amount") == 0) {
        where[1] = where_val;
        return 1;
    } else if (strcmp(where_col, "protect_flag") == 0) {
        where[2] = where_val;
        return 1;
    } else {
        error_unknown_condition(where_col);
        return 0;
    }
}

int assign_status_where(char *where_col, char *where_val, char **where) {
    if (strcmp(where_col, "*") == 0) {  // if no WHERE
        for (int i = 0; i < 5; i++) {
            where[i] = "";
        }
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        where[i] = "";
    }

    if (strcmp(where_col, "event_id") == 0) {
        where[0] = where_val;
        return 1;
    } else if (strcmp(where_col, "module_id") == 0) {
        where[1] = where_val;
        return 1;
    } else if (strcmp(where_col, "new_status") == 0) {
        where[2] = where_val;
        return 1;
    } else if (strcmp(where_col, "status_change_date") == 0) {
        where[3] = where_val;
        return 1;
    } else if (strcmp(where_col, "status_change_time") == 0) {
        where[4] = where_val;
        return 1;
    } else {
        error_unknown_condition(where_col);
        return 0;
    }
}

int assign_modules_where(char *where_col, char *where_val, char **where) {
    if (strcmp(where_col, "*") == 0) {  // if no WHERE
        for (int i = 0; i < 5; i++) {
            where[i] = "";
        }
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        where[i] = "";
    }

    if (strcmp(where_col, "id") == 0) {
        where[0] = where_val;
        return 1;
    } else if (strcmp(where_col, "module_name") == 0) {
        where[1] = where_val;
        return 1;
    } else if (strcmp(where_col, "mem_level_modules") == 0) {
        where[2] = where_val;
        return 1;
    } else if (strcmp(where_col, "cell_num") == 0) {
        where[3] = where_val;
        return 1;
    } else if (strcmp(where_col, "deletion_flag") == 0) {
        where[4] = where_val;
        return 1;
    } else {
        error_unknown_condition(where_col);
        return 0;
    }
}

int validate_status(char **lecs) {
    if (validate_int(lecs[1]) == 0) {
        return 0;
    }
    if (validate_int(lecs[2]) == 0) {
        return 0;
    }
    if (validate_int(lecs[3]) == 0) {
        return 0;
    }
    return 1;
}

int validate_levels(char **lecs) {
    if (validate_int(lecs[1]) == 0) {
        return 0;
    }
    if (validate_int(lecs[2]) == 0) {
        return 0;
    }
    if (validate_int(lecs[3]) == 0) {
        return 0;
    }
    return 1;
}

int validate_modules(char **lecs) {
    if (validate_int(lecs[1]) == 0) {
        return 0;
    }
    if (validate_int(lecs[3]) == 0) {
        return 0;
    }
    if (validate_int(lecs[4]) == 0) {
        return 0;
    }
    if (validate_int(lecs[5]) == 0) {
        return 0;
    }
    return 1;
}

int validate_int(char *strint) {
    if (strcmp(strint, "0") != 0) {
        if (atoi(strint) == 0) {
            error_not_int(strint);
            return 0;
        }
    }
    return 1;
}

void insert(char **lecs) {
    if (check_if_table_exists(lecs[0]) == 0) {
        error_unknown_db(lecs[0]);
        return;
    }
    if (strcmp(lecs[0], MODULES) == 0) {
        if (validate_modules(lecs) == 0) {
            return;
        }
        char *inserts[5];
        inserts[0] = lecs[1];
        inserts[1] = lecs[2];
        inserts[2] = lecs[3];
        inserts[3] = lecs[4];
        inserts[4] = lecs[5];
        insert_for_modules(inserts);
    }
    if (strcmp(lecs[0], LEVELS) == 0) {
        if (validate_levels(lecs) == 0) {
            return;
        }
        char *inserts[3];
        inserts[0] = lecs[1];
        inserts[1] = lecs[2];
        inserts[2] = lecs[3];
        insert_for_levels(inserts);
    }
    if (strcmp(lecs[0], STATUS) == 0) {
        if (validate_status(lecs) == 0) {
            return;
        }
        char *inserts[5];
        inserts[0] = lecs[1];
        inserts[1] = lecs[2];
        inserts[2] = lecs[3];
        inserts[3] = lecs[4];
        inserts[4] = lecs[5];
        insert_for_status(inserts);
    }
}

void print_mock(char **select, char **where) {
    printf("select ");
    for (int i= 0; i < 3; i++) {
        printf("%s ", select[i]);
    }
    printf("\n");
    printf("where ");
    for (int i= 0; i < 3; i++) {
        printf("%s ", where[i]);
    }
    printf("\n");
}

void select_local(char **lecs) {
    if (check_if_table_exists(lecs[0]) == 0) {
        error_unknown_db(lecs[0]);
        return;
    }
    if (strcmp(lecs[0], MODULES) == 0) {
        char *select_ar[5];
        char *where[5];
        if (assign_modules_select(lecs, select_ar) == 0) {
            return;
        }
        if (assign_modules_where(lecs[2], lecs[3], where) == 0) {
            return;
        }
        select_for_modules(select_ar, where);
    }
    if (strcmp(lecs[0], LEVELS) == 0) {
        char *select_ar[3];
        char *where[3];
        if (assign_levels_select(lecs, select_ar) == 0) {
            return;
        }
        if (assign_levels_where(lecs[2], lecs[3], where) == 0) {
            return;
        }
        select_for_levels(select_ar, where);
    }
    if (strcmp(lecs[0], STATUS) == 0) {
        char *select_ar[5];
        char *where[5];
        if (assign_status_select(lecs, select_ar) == 0) {
            return;
        }
        if (assign_status_where(lecs[2], lecs[3], where) == 0) {
            return;
        }
        select_for_status(select_ar, where);
    }
}

void update(char **lecs) {
    if (check_if_table_exists(lecs[0]) == 0) {
        error_unknown_db(lecs[0]);
        return;
    }
    if (strcmp(lecs[0], MODULES) == 0) {
        char *where[5];
        char *update_ar[5];
        if (assign_modules_update(lecs[1], lecs[2], update_ar) == 0) {
            return;
        }
        if (assign_modules_where(lecs[3], lecs[4], where) == 0) {
            return;
        }
        update_for_modules(where, update_ar);
    }
    if (strcmp(lecs[0], LEVELS) == 0) {
        char *where[3];
        char *update_ar[3];
        if (assign_levels_update(lecs[1], lecs[2], update_ar) == 0) {
            return;
        }
        if (assign_levels_where(lecs[3], lecs[4], where) == 0) {
            return;
        }
        update_for_levels(where, update_ar);
    }
    if (strcmp(lecs[0], STATUS) == 0) {
        char *where[5];
        char *update_ar[5];
        if (assign_status_update(lecs[1], lecs[2], update_ar) == 0) {
            return;
        }
        if (assign_status_where(lecs[3], lecs[4], where) == 0) {
            return;
        }
        update_for_status(where, update_ar);
    }
}

void delete(char **lecs)
{
    if (check_if_table_exists(lecs[0]) == 0)
    {
        error_unknown_db(lecs[0]);
        return;
    }

    if (strcmp(lecs[0], MODULES) == 0)
    {
        char *where[5];
        if (assign_modules_where(lecs[1], lecs[2], where) == 0)
            return;
        delete_for_modules(where);
    }
    if (strcmp(lecs[0], LEVELS) == 0)
    {
        char *where[3];
        if (assign_levels_where(lecs[1], lecs[2], where) == 0)
            return;
        delete_for_levels(where);
    }
    if (strcmp(lecs[0], STATUS) == 0) {
        char *where[5];
        if (assign_status_where(lecs[1], lecs[2], where) == 0)
            return;
        delete_for_status(where);
    }
}

