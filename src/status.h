// Copyright [2022] <griselle, sparelis, laynadre>

#include "main.h"

#ifndef SRC_STATUS_H_
#define SRC_STATUS_H_

void select_for_status(char **field, char **where);
void insert_for_status(char **new_line);
void update_for_status(char **where_ar, char **new_values);

void print_mask_status(int identifier);
void print_struct_status(status_events *local, int identifier);
void print_outro_status(int identifier);

int compare_status(status_events *local, int check_field, char *temp);
void update_record_status(FILE *pfile, status_events *local, status_events *change, int index);
int compare_for_update_status(status_events *local, status_events *where);
int check_id_status(char *id);

void write_record_in_file_status(FILE *pfile, status_events *record_to_write, int index);
status_events read_record_from_file_status(FILE *pfile, int index);

#endif  // SRC_STATUS_H_
