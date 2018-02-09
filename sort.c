#include <stdio.h>
#include "string.h"

void SortStrings(char *strs[], int count);
int main(int argc,char *argv[]){
    char str[200];
    
    char *words[4] = {"Oh","In","The","Our"};
    int nWords=sizeof(words)/sizeof(words[0]);
    int i;
    SortStrings(words, nWords);
    printf("Sorted:\n");
    for(i=0;i<nWords;i++)
        printf("%s \n" ,words[i]);
    return 0;
}


void SortStrings(char *strs[], int count){

    int i,j,k;
    char *p;
    for(i=0;i<count-1;i++){
        for(k=i,j=k+1;j<count;j++)
            if(strcmp(strs[k],strs[j])>0)
                k=j;
        if(k-i)
            p=strs[i],strs[i]=strs[k],strs[k]=p;
    }
   
}

