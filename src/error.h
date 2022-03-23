// Copyright [2022] <griselle, sparelis, laynadre>

#ifndef SRC_ERROR_H_
#define SRC_ERROR_H_

int error_shell_buff_overflow(void);
int error_shell_query_parse(void);
int error_miss_semicolon(void);
int error_unknown_db(char *table_name);

#endif  // SRC_ERROR_H_
