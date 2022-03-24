// Copyright [2022] <griselle, sparelis, laynadre>

#include "main.h"

#ifndef SRC_STATUS_H_
#define SRC_STATUS_H_

void select_for_status(char **field, char **where);
void insert_for_status(char **new_line);
void print_mask_status(int identifier);
void print_outro_status(int identifier);
int compare_status(status_events *local, int check_field, char *temp);
status_events read_record_from_file_status(FILE *pfile, int index);
void print_struct_status(status_events *local, int identifier);
void write_record_in_file_status(FILE *pfile, status_events *record_to_write, int index);
#endif  // SRC_STATUS_H_