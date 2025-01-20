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
    int is_inside_string = 0;
    int string_encounter = 0;
    while ((ch = fgetc(fptr)) != EOF) {
        // Skip spaces so that our array is clean
        // TODO: Unless a string

        if (ch == '"' && string_encounter < 2) {
            is_inside_string = 1;
            string_encounter++;
        } else if (string_encounter == 2) {
            is_inside_string = 0;
            string_encounter = 0;
        }
        if ((ch == ' ' || ch == '\t' || ch == '\n') && is_inside_string == 0) {
            continue;
        }
        content_buffer[index] = ch;
        printf("Current char: %c\n", ch);
        printf("String encountered: %d\n", string_encounter);
        printf("Inside string: %d\n", is_inside_string);
        index++;
    }
    fclose(fptr);
  
    // Testing Place
    printf("%s\n", content_buffer);
    char *str_test = "\"Hel\\\"lo\"";
    printf("%s\n", str_test);
    printf("%d\n", is_valid_json_string(str_test));
    char *num_test = "0.e6";
    printf("Test num 1: %d\n", is_valid_json_numbers(num_test));
    return 0;
}


