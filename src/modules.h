// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_MODULES_H_
#define SRC_MODULES_H_

#include "main.h"

void select_for_modules(char **field, char **where);
void insert_for_modules(char **new_line);
void update_for_modules(char **old, char **new);

void print_mask_modules(int identifier);
void print_struct_modules(modules *local, int identifier);
void print_outro_modules(int identifier);

int compare_modules(modules *local, int check_field, char *temp);
int compare_for_update(modules *local, modules *where);
void write_record_in_file_modules(FILE *pfile, modules *record_to_write, int index);
void update_record_modules(FILE *pfile, modules *local, modules *change, int index);
int check_id_modules(char *id);

int get_records_count_in_file_modules(FILE *pfile);
int get_file_size_in_bytes_modules(FILE *pfile);
modules read_record_from_file_modules(FILE *pfile, int index);

#endif  // SRC_MODULES_H_
