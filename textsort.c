#include <stdio.h>
#include <stdlib.h>

void readFile(char file[]);
int compare(const void *a, const void *b);

int main(int argc, char **argv){


	if(argc > 3 || argc == 1){
		fprintf(stderr, "Error: Bad command line parameters\n");
		exit(1);
	}
	else if( argc == 3 ){
		int num;
		char *end;
		num = strtol(argv[2], &end, 10);
		if(num >= 0 ){
			fprintf(stderr, "Error: Bad command line parameters\n");
			exit(1);
		}
	}
		readFile(argv[1]);

	return 0;
}

void readFile(char file[]){
	FILE *f;
	int ch;

	f = fopen(file, "rb"); 
	if(f == NULL){
		fprintf(stderr, "There is no such file.\n");
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

