#include <stdio.h>
#include <stdlib.h>

void readFile(char file[]);
int compare(const void *a, const void *b);

int main(int argc, char **argv){
    
    // if there are no arguments or more than two arguments, exit
    if( argc == 1 || argc > 3 ){
        fprintf(stderr, "Error: Bad command line parameters\n");
        exit(1);
    }
    // if there are two arguments
    else if( argc == 3 ){
        int num;
        char *end;
        num = strtol(argv[2], &end, 10);
        
        // check the second argument meets the format of a dash followed by a number
        if(num >= 0 ){
            fprintf(stderr, "Error: Bad command line parameters\n");
            exit(1);
        }
    }
    
    // read the file
    readFile(argv[1]);
    
    return 0;
}

void readFile(char file[]){
    FILE *f;
    
    char s1[100];
    char s2[100];
    char s3[100];
    char s4[100];
    
    f = fopen(file, "rb");
    if(f == NULL){
        fprintf(stderr, "There is no such file.\n");
        exit(1);
    }
    
    fgets(s1,100,f);
    fgets(s2,100,f);
    fgets(s3,100,f);
    fgets(s4,100,f);

    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);
    printf("%s\n", s4);
    
    fclose(f);
}


