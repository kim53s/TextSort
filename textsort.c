#include <stdio.h>
#include <stdlib.h>

void readFile(char file[]);

int main(int argc, char **argv){


	if(argc > 3 || argc == 1){
		fprintf(stderr, "Error: Bad command line parameters\n");
		return 1;
	}
	else
		readFile(argv[1]);

	return 0;
}

void readFile(char file[]){
	FILE *f;
	int ch;

	f = fopen(file, "rb"); 
	if(f == NULL){
		printf("NULL!!");
	}
	ch = getc(f);
	while (ch != EOF){
		putchar(ch);
		ch = getc(f);
	}
	printf("\n");
	fclose(f);
}