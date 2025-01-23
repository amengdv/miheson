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
    int token_th = 1;
    token t;
    //token prev_t;
    int valid = 1;
    while(1) {
        //prev_t = t;
        t = next_token(&l);
        token_th++;
        // BREAK WHEN REACH END OF FILE
        if (t.tok_type == END) {
            if (token_th == 1) {
                valid = 0;
            }
            break;
        } else if (t.tok_type == INVALID) {
            valid = 0;
            break;
        }
        
    }
    
    printf("token count: %d\n", token_th);
    if (valid == 1) {
        printf("VALID JSON!\n");
    } else {
        printf("INVALID JSON!\n");
    }
    
    fclose(fptr);
  
    return 0;
}


