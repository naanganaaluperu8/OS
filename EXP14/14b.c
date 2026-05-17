#include<stdio.h>
#include<string.h>
struct File{
	char name[20];
	char type[10];
};
struct User{
	char uname[20];
	struct File f[10];
	int count;
};
struct User u[10];
int uc = 0;
int find(char name[]){
	for(int i = 0;i<uc;i++){
		if(strcmp(u[i].uname,name)==0){
			return i;
		}
	}
	return -1;
}
void adduser(char name[]){
	strcpy(u[uc].uname,name);
	u[uc].count = 0;
	uc++;
}
void addfile(char uname[],char name[],char type[]){
	int idx = find(uname);
	int c = u[idx].count;
	strcpy(u[idx].f[c].name,name);
	strcpy(u[idx].f[c].type,type);
	u[idx].count++;
}
void display(){
	for(int i = 0;i<uc;i++){
		printf("%s\t",u[i].uname);
		for(int j = 0;j<u[i].count;j++){
			printf("%s.%s ",
                   u[i].f[j].name,
                   u[i].f[j].type);
		}
		printf("\n");
	}
}
int main(){
	adduser("alice");
    adduser("bob");

    addfile("alice", "resume", "pdf");
    addfile("alice", "notes", "txt");
    addfile("bob", "photo", "jpg");

    display();

    return 0;
}
