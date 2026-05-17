#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE *fs;
	FILE *fd;
	char ch;
	char source[50],destination[50];
	printf("Enter the source file name:");
	scanf("%s",source);
	printf("Enter the destionation file name:");
	scanf("%s",destination);
	fs=fopen(source,"r");
	if(fs==NULL){
		printf("Source file cannot be opened");
		exit(1);
	}
	fd=fopen(destination,"w");
	if(fd==NULL){
		printf("Destination file cannot be opened");
		exit(1);
	}
	while((ch=fgetc(fs))!=EOF){
		fputc(ch,fd);
	}
	return 0;
}
