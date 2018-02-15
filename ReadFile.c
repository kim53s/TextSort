#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readFile(char file[]);
int compare(const void *a, const void *b);
char* getWord(char *string);
int checkInput(char input[]);

int maxRow = 10;
int row = 1;
char **strs;
int wordNum;

int checkInput(char input[]){
    int i = 0;
    for (i=1; input[i]!=0; i++){
        if (!isdigit(input[i])){
            return 1;
        }
    }
    return 0;
}

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
        
        if (checkInput(argv[1])==1){
            fprintf(stderr, "Error: Bad command line parameters\n");
        }
      
        
        else{
            num = strtol(argv[1], &end, 10);
        
        // check the first argument meets the format of a dash followed by a number
        if(num >= 0 ){
            fprintf(stderr, "Error: Bad command line parameters\n");
            exit(1);
        }
        else{
            wordNum = -num;
            readFile(argv[2]);
            return 0;
        }
        }
    }
    else{  // there is only one argument
        wordNum = 1;
        readFile(argv[1]); // read the file
    }

    //printf("%d\n", wordNum);
    return 0;
}


void readFile(char file[]){
    FILE *f;
    int ch;
    
    f = fopen(file, "rb");
    if(f == NULL){
        fprintf(stderr, "Error: Cannot open file %s\n", file);
        exit(1);
    }
    
    
    strs = (char**)malloc(sizeof(char*)*maxRow);
    for(int i = 0; i < maxRow; i++){
        strs[i] = (char*)malloc(sizeof(char)*128);
    }
    
    ch = getc(f);
    while (ch != EOF){
        if(ch != '\n'){
            if(strlen(strs[row-1]) < 128){
                char temp[2];
                temp[0] = ch;
                temp[1] = '\0';
                strcat(strs[row-1], temp);
            }
            else{
                fprintf(stderr, "Line too long\n");
                exit(1);
            }
        }
        else{
            row++;
            
            // reallocate
            if(row > maxRow){
                char** strs2 = (char**)realloc(strs, sizeof(char*)*maxRow*2);
                
                if(strs2 != NULL){
                    strs = strs2;
                }
                else{
                    fprintf(stderr, "malloc failed\n");
                    exit(1);
                }
                
                for(int i = maxRow; i < maxRow*2; i++){
                    strs[i] = (char*)malloc(sizeof(char)*128);
                }
                
                maxRow = maxRow*2;
            }
        }
        ch = getc(f);
    }
    
    qsort((char *)strs, row, sizeof(strs[0]), compare);
    
    // print out the sorted sentences
    for(int i = 0; i < row; i++){
        for(int j = 0; j < strlen(strs[i]); j++){
            printf("%c", strs[i][j]);
        }
        printf("\n");
    }
    
    for(int i = 0; i < maxRow; i++){
        free(strs[i]);
    }
    free(strs);
    
    fclose(f);
}

char* getWord(char *string){
    
   	const char s[2] = " ";
   	char *token;
    char *former;
   	// the first token
   	token = strtok(string, s);
    
   	for(int i = 0; i < wordNum-1; i++){
        former = token;
        token = strtok(NULL, s);
        if(token == NULL){
            return former;
        }		
   	}

   	return token;
}



int compare(const void *elem1, const void *elem2){
    // Cast to its actual type.
    char **strptr1 = (char **) elem1;
    char **strptr2 = (char **) elem2;
   	
    // Dereference to get the strings 
    char *str1 = *strptr1;
    char *str2 = *strptr2;
    
    char s1[sizeof(char)*strlen(str1)];
    char s2[sizeof(char)*strlen(str2)];
    
    for(int i = 0; i < strlen(str1); i++){
        s1[i] = str1[i]; 
    }	
    
    for(int i = 0; i < strlen(str2); i++){
        s2[i] = str2[i]; 
    }	
    
    char *word1 = getWord(s1);
    char *word2 = getWord(s2);
    
    /* Then use strcmp to compare the strings */
    return strcmp(word1, word2);
}
