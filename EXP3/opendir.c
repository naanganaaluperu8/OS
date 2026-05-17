#include<stdio.h>
#include<dirent.h>
int main(){
	DIR *d;
	struct dirent *d1;
	char dir[30];
	printf("Enter directory name:");
	scanf("%s",dir);
	d = opendir(dir);
	if(d==NULL){
		printf("directory cannot be opened");
		return 1;
	}
	d1 = readdir(d);
	while(d1!=NULL){
		printf("%s\n",d1->d_name);
		d1 = readdir(d);
	}
	return 0;
}

