#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void readFile(char file[]);
int compare(const void *a, const void *b);
char* getWord(char *string);
int checkInput(char input[]);

// the maximun numer of lines
int maxRow = 10;
// the number of lines 
int row = 1;
// string array that holds lines in a file
char **strs;
// nth word is used as the key to sort upon
int nth;

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

		// if the first argument is not a digit 
        if (checkInput(argv[1])==1){
            fprintf(stderr, "Error: Bad command line parameters\n");
            exit(1);
        }
        else
        	num = strtol(argv[1], &end, 10); 

		// check the first argument meets the format of a dash followed by a number
		if(num >= 0 ){
			fprintf(stderr, "Error: Bad command line parameters\n");
			exit(1);
		}
		else{
			nth = -num;

			readFile(argv[2]);
			
			return 0;
		}
	}
	else{  // there is only one argument
		nth = 1;
		
		readFile(argv[1]); 

	return 0;
}

// opens file, reads the lines, and stores them into a string array
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

    // get a char from the file
	ch = getc(f);
	// if it is not the end of the file
	while (ch != EOF){
		if(ch != '\n'){
			if(strlen(strs[row-1]) < 128){

				char temp[2]; 
				temp[0] = ch; 
				temp[1] = '\0';

				strcat(strs[row-1], temp);
			}
			// when the size of a line is bigger than 128
			else{
				fprintf(stderr, "Line too long\n");
				exit(1);
			}
		}
		else{

			row++;

			// if the current number of lines is bigger than the maximun number of lines
			if(row > maxRow){
				// double the size of memory
				char** strs2 = (char**)realloc(strs, sizeof(char*)*maxRow*2);

				if(strs2 != NULL){
					strs = strs2;
				}
				else{
					fprintf(stderr, "malloc failed\n");
					exit(1);
				}

				// the newly allocated part
				for(int i = maxRow; i < maxRow*2; i++){
					strs[i] = (char*)malloc(sizeof(char)*128);	
				}
				
				maxRow = maxRow*2;		
			}			
		}
		ch = getc(f);
	}

	// sort lines
	qsort((char *)strs, row, sizeof(strs[0]), compare); 

	// print out the sorted lines
	for(int i = 0; i < row; i++){
		printf("%s\n", strs[i]);
	}

	// free memory
	for(int i = 0; i < maxRow; i++){
		free(strs[i]);
	}
	free(strs);

	fclose(f);
}

// get the nth word that is used as the key to sort upon
char* getWord(char *string){

   	const char s[2] = " ";
   	char *token;
  	char *last; 

  	// if the string is empty, then return NULL
  	if(string[0] == '\0')
  		return NULL;

   	// the first token 
   	token = strtok(string, s);
  
  	// if the string is just space or newline, then return NULL
  	if(token[0] == '\n' || token[0] == '\0')
  		return NULL;

   	for(int i = 0; i < nth-1; i++){
   		last = token;
   		token = strtok(NULL, s);
   		// if there is no nth word, return the last word
   		if(token == NULL){
   			return last;
   		}		
   	}

   	return token;
}

// return 1 if input is not decimal digit
int checkInput(char input[]){
    int i = 0;
    for (i=1; input[i]!=0; i++){
        if (!isdigit(input[i])){
            return 1;
        }
    }
    return 0;
}

int compare(const void *elem1, const void *elem2){

	// Cast to its actual type.
    char **strptr1 = (char **) elem1;
    char **strptr2 = (char **) elem2;
   	
    // Dereference to get the strings 
    char *str1 = *strptr1;
    char *str2 = *strptr2;

    char s1[sizeof(char)*strlen(str1)+1];
    char s2[sizeof(char)*strlen(str2)+1];

    // copy str1
	for(int i = 0; i < strlen(str1)+1; i++){
		s1[i] = str1[i]; 
	}	
	// copy str2
	for(int i = 0; i < strlen(str2)+1; i++){
		s2[i] = str2[i]; 
	}	

    char *word1 = getWord(s1);
    char *word2 = getWord(s2);

    // if there are empty lines
    if(word1 == NULL && word2 != NULL){
	   	return 1;
    }
    if(word1 != NULL && word2 == NULL){
    	return -1;
    }
    if(word1 == NULL && word2 == NULL){
    	return 0;
	}

    /* Then use strcmp to compare the strings */
	return strcmp(word1, word2);
}