// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_LEVELS_H_
#define SRC_LEVELS_H_

#include "main.h"

void select_for_levels(char **field, char **where);
void print_mask_levels(int identifier);
int compare_levels(levels *local, int check_field, char *temp);
int get_records_count_in_file_levels(FILE *pfile);
levels read_record_from_file_levels(FILE *pfile, int index);
int get_file_size_in_bytes_levels(FILE *pfile);
void print_struct_levels(levels *local, int identifier);
void insert_for_levels(char **new_line);
void write_record_in_file_levels(FILE *pfile, levels *record_to_write, int index);
void update_for_levels(char **old, char **new);
void update_record_levels(FILE *pfile, levels *local, levels *change, int index);
int compare_for_update_levels(levels *local, levels *where);
int get_records_count_in_file_levels(FILE *pfile);
void print_outro_levels(int identifier);
#endif  // SRC_LEVELS_H_
