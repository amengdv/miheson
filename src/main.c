#include <stdio.h>
#include "hello.h"

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
    content_buffer[index] = ch;
    index++;
  }
  printf("%s\n", content_buffer);
  fclose(fptr);
  hello();
  return 0;
}
