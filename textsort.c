#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(char file[]);
int compare(const void *a, const void *b);

int maxRow = 5;
int row = 1;
char **strs;

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
		num = strtol(argv[1], &end, 10);

		// check the first argument meets the format of a dash followed by a number
		if(num >= 0 ){
			fprintf(stderr, "Error: Bad command line parameters\n");
			exit(1);
		}
		else{
			readFile(argv[2]);
			return 0;
		}
	}
	else  // there is only one argument
		readFile(argv[1]); // read the file

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
	
				// for (int i = 0; i < maxRow; i++){
				// 	strs2[i] = (char*)realloc(strs[i], sizeof(char)*128);
				// }

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


	printf("The number of sentences: %d\n", row );
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

	// size of the file
	// fseek(f, 0, SEEK_END);    
 //    long fileSize = ftell(f);
 //    fseek(f, 0, SEEK_SET);
 //   printf("%lu\n", fileSize);

	fclose(f);
}


int compare(const void *elem1, const void *elem2){
	// Cast to its actual type.
    char **strptr1 = (char **) elem1;
    char **strptr2 = (char **) elem2;
    
    // Dereference to get the strings 
    char *str1 = *strptr1;
    char *str2 = *strptr2;

    /* Then use strcmp to compare the strings */

	return strcmp(str1, str2);
}

