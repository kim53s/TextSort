#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a;
int b;


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



void sortString(char *str[a][b]){
    printf("%s\n", str[0][0]);
    int i;
    char words[a];
    for (i=0;i<=a;i++){
     words[i] = *str[i][0];
         //printf("%s\n", words[i]);
    }
}




void readFile(char file[]){
    FILE *f;


    int i=0;

    
    f = fopen(file, "rb");
    if(f == NULL){
        fprintf(stderr, "There is no such file.\n");
        exit(1);
    }
    
    
    char input[100][100];
    
    char *str[sizeof(input)][sizeof(input[0])];
    
    
    while(fgets(input[i],sizeof(input),f)){
        input[i][strlen(input[i]) - 1] = '\0';
        i++;
    }
    
    
    char * pch;
    int j;
    int k;
    for(k=0; k<sizeof(str); k++){
        pch = strtok (input[k]," ");
        j=0;
        while (pch != NULL)
        {
            str[k][j] = pch;
            //printf("%s\n", str[k][j]);
            j++;
            pch = strtok (NULL, " ");
        }
        printf("%s\n", str[1][1]);
    }
    printf("%s\n", str[1][1]);
   printf("%s\n", "hello world");
    sortString(str);
    
    fclose(f);
}




