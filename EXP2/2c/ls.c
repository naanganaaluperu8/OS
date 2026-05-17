#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
int main(){
	DIR *dp;
	struct dirent *entry;
	dp=opendir(".");
	if(dp==NULL){
		printf("Directory cannot be opened");
		exit(1);
	}
	while((entry=readdir(dp))!=NULL){
		printf("%s\n",entry->d_name);
	}
	closedir(dp);
	return 0;
}

