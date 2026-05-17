#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	FILE *fs;
	char source[50],pattern[50],line[200];
	printf("Enter the file name:");
	scanf("%s",source);
	printf("Enter the pattern:");
	scanf("%s",pattern);
	fs=fopen(source,"r");
	if(fs==NULL){
		printf("File cannot be opened");
	}
	while((fgets(line,sizeof(line),fs))!=NULL){
		if(strstr(line,pattern)!=NULL){
			printf("%s",line);
		}
	}
	return 0;
}

