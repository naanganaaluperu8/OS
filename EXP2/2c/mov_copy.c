#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE *fs;
	FILE *fd;
	char source[50],destination[50];
	char ch;
	printf("Enter the source file name:");
	scanf("%s",source);
	printf("Enter the destination file anme:");
	scanf("%s",destination);
	fs=fopen(source,"r");
	if(fs==NULL){
		printf("Source file cannot be opened");
		exit(1);
	}
	fd=fopen(destination,"w");
	if(fd==NULL){
		printf("Destionation file cannot be opened");
	}
	while((ch=fgetc(fs))!=EOF){
		fputc(ch,fd);
	}
	fclose(fs);
	fclose(fd);
	remove(source);
	return 0;
}
