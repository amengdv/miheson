#include "yeson.h"
#include <string.h>

int is_valid_json_string(char *str) {
  size_t str_len = strlen(str);
  if (str[0] != '"' && str[str_len - 1] != '"') {
    return 0;
  }
  for (int i = 1; i < (int)str_len; ++i) {
    char curr_str = str[i];
    if (curr_str == '"') {
      if (str[i - 1] == '\\') {
        continue;
      }

      if (str[i + 1] != '\0') {
        return 0;
      }
    }
  }
  return 1;
}
