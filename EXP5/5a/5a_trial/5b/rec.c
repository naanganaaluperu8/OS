#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
#define MAX 100
struct msgbuff{
	long type;
	char text[MAX];
}message;
int main(){
	key_t key = ftok("progfile",65);
	int msgid = msgget(key , 0666 | IPC_CREAT);
	printf("Waiting for the message:");
	msgrcv(msgid,&message,sizeof(message.text),1,0);
	printf("%s",message.text);
	msgctl(msgid, IPC_RMID,NULL);
	return 0;
}
