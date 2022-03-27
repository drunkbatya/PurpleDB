// Copyright [2022] <drunkbatya>

#ifndef SRC_STRUCTURE_H_
#define SRC_STRUCTURE_H_

#define COLUMN_COUNT_SHIFT sizeof(uint8_t)
#define STRING_SIZE 100

typedef enum e_datatype
{
    integer,
    string,
    error
} t_datatype;

typedef struct s_header
{
    char column_name[STRING_SIZE];
    t_datatype datatype;
} t_header;

#endif  // SRC_STRUCTURE_H_
