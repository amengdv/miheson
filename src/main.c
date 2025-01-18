#include <stdio.h>
#include "yeson.h"

int main() {
  FILE *fptr;
  char content_buffer[64];
  char *filename = "yeson-true.txt";
  fptr = fopen(filename, "r");
  if (fptr == NULL) {
    printf("Error reading from file named %s", filename);
    return 1;
  }
  char ch;
  int index = 0;
  while ((ch = fgetc(fptr)) != EOF) {
    // Skip spaces so that our array is clean
    if (ch == ' ' || ch == '\t' || ch == '\n') {
      continue;
    }
    content_buffer[index] = ch;
    index++;
  }
  fclose(fptr);
  
  // Testing Place
  printf("%s\n", content_buffer);
  char *str_test = "\"Hel\\\"lo\"";
  printf("%s\n", str_test);
  printf("%d\n", is_valid_json_string(str_test));
  return 0;
}

