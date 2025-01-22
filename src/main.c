#include <stdio.h>
#include "lexer.h"

int main() {
    FILE *fptr;
    char *filename = "yeson-true.txt";
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error reading from file named %s", filename);
        return 1;
    }

    lexer l = new_lexer(fptr);
    token t;
    while((t = next_token(&l)).tok_type != END) {
        if (t.tok_type == INVALID) {
            printf("Not a Valid JSON\n");
            break;
        }
        print_token(t);
    }
    
    fclose(fptr);
  
    return 0;
}


