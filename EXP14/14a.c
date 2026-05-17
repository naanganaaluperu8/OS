#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct File{
	char name[20];
	char type[20];
	int size;
};
struct File f[10];
int count = 0;
void create(char n[],char t[],int s){
	strcpy(f[count].name,n);
	strcpy(f[count].type,t);
	f[count].size=s;
	count++;
}
void display(){
	printf("\nFile Name\tType\tSize\n");
	for(int i = 0;i<count;i++){
		printf("%s\t\t%s\t%d\n",
               f[i].name,
               f[i].type,
               f[i].size);
	}
}
void del(char n[]){
	for(int i = 0;i<count;i++){
		if(strcmp(f[i].name,n)==0){
			for(int j = i;j<count-1;j++){
				f[j] = f[j+1];
			}
			count--;
			return;
		}
	}
}



int main(){
	create("notes", "txt", 12);
    create("photo", "jpg", 340);
    create("prog", "c", 5);

    display();

    del("photo");

    display();

    return 0;
}    

