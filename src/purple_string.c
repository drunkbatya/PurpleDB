// Copyright [2022] <drunkbatya, koterin, GrusnyDance>

#include "purple_string.h"
#include "shared.h"

// This fucntion doing some magick to save the space alive!
// It replaces space characters inside quotes to some unprintable
// char, e.x. 26. We need this because we splitting user inputed
// string by spaces.
uint8_t quoted_space_driver(char *str)
{
    char *new_ptr;

    new_ptr = str;
    if (check_unpair_char(new_ptr, '"') == 0)
        return (error_unpaired_char('"', 0));
    while (new_ptr && *new_ptr != '\0')
    {
        if (*new_ptr != '"')
        {
            new_ptr++;
            continue;
        }
        new_ptr++;
        while (*new_ptr != '"')
        {
            if (*new_ptr == ' ')
                *new_ptr = 26;
            new_ptr++;
        }
        new_ptr++;
    }
    return (1);
}

// returns (true) if count of given char in given string
// is an even number. Also true if char isn't exist in string.
uint8_t check_unpair_char(char *str, char c)
{
    char *new_ptr;
    uint32_t count;

    count = 0;
    new_ptr = str;
    while (new_ptr && *new_ptr != '\0')
    {
        if (*new_ptr == c)
            count++;
        new_ptr++;
    }
    return (!(count % 2));
}

// remove all occurrence of char c from string str
void remove_char_from_str(char *str, char c)
{
    char *orig_str;

    if (str == NULL || *str == '\0')
        return;
    orig_str = malloc(strlen(str) + 1);
    if (orig_str == NULL)
        return;
    strcpy(orig_str, str);
    memset(str, 0, strlen(str));
    while (*orig_str != '\0')
    {
        if (*orig_str != c)
            *str++ = *orig_str;
        orig_str++;
    }
    safe_free(orig_str);
}

void clear_input_buffer(void)
{
    int16_t ch;

    ch = getchar();
    while (ch != '\n' && ch != EOF)
        ch = getchar();
}

uint8_t getstr(char *buf)
{
    int16_t ch;
    char *new_ptr;

    ch = 0;
    new_ptr = buf;
    while (ch != '\n' && ch != EOF)
    {
        ch = getchar();
        *new_ptr = ch;
        new_ptr++;
        if (new_ptr - buf > SHELL_BUF_SIZE - 1)
        {
            clear_input_buffer();
            return (error_shell_buff_overflow(0));
        }
    }
    *new_ptr = '\0';
    return (1);
}
