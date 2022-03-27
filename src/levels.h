// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_LEVELS_H_
#define SRC_LEVELS_H_

#include "main.h"

void select_for_levels(char **field, char **where);
void insert_for_levels(char **new_line);
void update_for_levels(char **where_ar, char **new_values);
void delete_for_levels (char **array);

void print_mask_levels(int identifier);
void print_struct_levels(levels *local, int identifier);
void print_outro_levels(int identifier);

int compare_levels(levels *local, int check_field, char *temp);
void update_record_levels(FILE *pfile, levels *local, levels *change, int index);
int compare_for_update_levels(levels *local, levels *where);
int check_id_levels(char *id);

int get_records_count_in_file_levels(FILE *pfile);
int get_file_size_in_bytes_levels(FILE *pfile);
void write_record_in_file_levels(FILE *pfile, levels *record_to_write, int index);
levels read_record_from_file_levels(FILE *pfile, int index);
#endif  // SRC_LEVELS_H_
