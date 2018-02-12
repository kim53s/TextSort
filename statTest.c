#include <unistd.h>

int main(void){

    FILE *f;

    f = fopen("test.txt", "rb");
    if(f == NULL){
        printf("ERROR\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);    
    long fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    printf("%lu\n", fileSize);
    
    fclose(f);

    return 0;
} 