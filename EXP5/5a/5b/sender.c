#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 100
struct msgbuf{
	long type;
	char text[MAX];
}message;
int main(){
	key_t key = ftok("progfile",65);
	int msgid=msgget(key,0666|IPC_CREAT);
	message.type = 1;
	printf("Enter the message:");
	fgets(message.text,MAX,stdin);
	msgsnd(msgid,&message,sizeof(message.text),0);
	return 0;
}

