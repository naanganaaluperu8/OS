#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
	int a;
	a = fork();
	if(a==0){
		printf("Child is executing\n");
		printf("child exits\n");
	}
	else if(a>0){
		printf("Parent is executing\n");
		wait(NULL);
		printf("Parent is exiting\n");
	}
	else{
		printf("Process is unable to be created");
	}
	return 0;
}
