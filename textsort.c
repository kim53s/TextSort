#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		fprintf(stderr, "There is no such file.\n");
		exit(1);
	}


	char **strs;
    strs = (char**)malloc(sizeof(char*)*3); 

    strs[0] = (char*)malloc(sizeof(char)*4);
    strs[1] = (char*)malloc(sizeof(char)*10);
    strs[2] = (char*)malloc(sizeof(char)*6);

    int i = 0;
	ch = getc(f);
	while (ch != EOF){
		if(ch != '\n'){
			char temp[2]; 
			temp[0] = ch; 
			temp[1] = '\0';
			strcat(strs[i], temp);
		}
		else{
			i++;		
			//printf("New Line!\n");
		}
		ch = getc(f);
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < strlen(strs[i]); j++){
			printf("%c", strs[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");

	for(int i = 0; i < 3; i++){
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

// int compare(const void *a, const void *b){
// 	/* Cast to its actual type. */
//     char **strptr1 = (char **) elem1;
//     char **strptr2 = (char **) elem2;
    
//      Dereference to get the strings 
//     char *str1 = *strptr1;
//     char *str2 = *strptr2;

//     /* Then use strcmp to compare the strings */

// 	return ( *(char *)a - *(char *)b);
// }

