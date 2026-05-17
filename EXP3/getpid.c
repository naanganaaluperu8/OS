#include<stdio.h>
#include<unistd.h>
int main(){
	int a;
	a = fork();
	if(a==0){
		printf("child process id: %d\n",getpid());
		printf("Child parent id: %d\n",getppid());
	}
	else if(a>0){
		printf("Parent process id: %d\n",getpid());
		printf("Parents parent process id: %d\n",getppid());
	}
	else{
		printf("Uable to create process");
	}
	return 0;
}
