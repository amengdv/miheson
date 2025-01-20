#include "yeson.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int is_digit_after_decimal(char *str);

int is_valid_json_string(char *str) {
    size_t str_len = strlen(str);
    if (str[0] != '"' && str[str_len - 1] != '"') {
        return 0;
    }
    for (int i = 1; i < (int)str_len - 1; ++i) {
        char curr_str = str[i];
        char after = str[i + 1];
        if (curr_str == '"') {
            return 0;
        }
        if(curr_str == '\\') {
            printf("%c\n", after);
            if (after == 't' || after == 'n' || after == 'b'
                || after == 'f' || after == 'r' || after == '"' || after == '\\') {
                i++;
                continue;
            }
        }
    }
    return 1;
}

/*
  Expect the string to not have whitespace
*/
int is_valid_json_numbers(char *str) {
    if (str[0] == '+' || ((str[0] < '0' || str[0] > '9') && str[0] != '-')
        || (str[0] == '0' && strlen(str) > 1 && str[1] != '.')
        || is_digit_after_decimal(str) == 0) {
        return 0;
    }
    char *end_ptr;
    strtod(str, &end_ptr);
    if (str == end_ptr) {
        return 0;
    }
    if (*end_ptr != '\0') {
        return 0;
    }
    return 1;
}

int is_digit_after_decimal(char *str) {
    for (size_t i = 0; i < strlen(str); ++i) {
        if (str[i] == '.') {
            if (str[i + 1] < '0' || str[i + 1] > '9') {
                return 0;
            }
        }
    }
    return 1;
}
