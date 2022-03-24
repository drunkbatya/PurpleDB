// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_
#include "main.h"

void select_for_modules(char **field, char **where);
int compare(modules *local, int check_field, char * temp);
modules read_record_from_file_modules(FILE *pfile, int index);
void print_struct(modules *local, int identifier);
void print_outro(int identifier);
void insert_for_modules(char **new_line);
void write_record_in_file(FILE *pfile, modules *record_to_write, int index);
int check_id(char * id);
void update_for_modules(char **old, char **new);
void update_record(FILE *pfile, modules *local, modules *change, int index);
int compare_for_update(modules *local, modules *where);
void print_mask(int identifier);

#endif  // SRC_MODULES_H_
