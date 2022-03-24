// Copyright [2022] <griselle, sparelis, laynadre>

#include "main.h"

void select_for_status(char **field, char **where);
void print_mask_status(int identifier);
void print_outro_status(int identifier);
int compare_status(status_events *local, int check_field, char *temp);
status_events read_record_from_file_status(FILE *pfile, int index);
void print_struct_status(status_events *local, int identifier);
