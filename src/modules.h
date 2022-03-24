// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_

#include "main.h"

void select_for_modules(char **field, char **where);
void print_mask_modules(int identifier);
void print_outro_modules(int identifier);
int compare_modules(modules *local, int check_field, char *temp);
modules read_record_from_file_modules(FILE *pfile, int index);
void print_struct_modules(modules *local, int identifier);
void insert_for_modules(char **new_line);
int check_id(char * id);
void write_record_in_file_modules(FILE *pfile, modules *record_to_write, int index);
void update_for_modules(char **old, char **new);
void update_record_modules(FILE *pfile, modules *local, modules *change, int index);
int compare_for_update(modules *local, modules *where);
int get_records_count_in_file_modules(FILE *pfile);
int get_file_size_in_bytes_modules(FILE *pfile);


#endif  // SRC_MODULES_H_
