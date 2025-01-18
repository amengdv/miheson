#include "yeson.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

int is_valid_json_numbers(char *str) {
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
