#include<stdio.h>
#include<unistd.h>
int main(){
	int pid;
	int p[2];
	char msg[] = "hi";
	char buf[20];
	pipe(p);
	pid = fork();
	if(pid>0){
		write(p[1],msg,sizeof(msg));
	}
	else{
		read(p[0],buf,sizeof(buf));
		printf("%s",buf);
	}
	return 0;
}
