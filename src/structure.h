// Copyright [2022] <drunkbatya>

#ifndef SRC_STRUCTURE_H_
#define SRC_STRUCTURE_H_

// data types
#define COLUMN_COUNTER uint8_t
#define INTEGER int32_t
#define STRING_SIZE 100

typedef enum e_datatype
{
    integer,
    string,
    error
} t_datatype;

typedef struct s_header
{
    char column_name[30];
    t_datatype datatype;
} t_header;

#endif  // SRC_STRUCTURE_H_
