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
	int ch;

	f = fopen(file, "rb"); 
	if(f == NULL){
		fprintf(stderr, "There is no such file.\n");
		exit(1)
	}

	ch = getc(f);
	while (ch != EOF){
		putchar(ch);
		ch = getc(f);
	}
	printf("\n");
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

