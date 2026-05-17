#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX 100
struct msgbug{
	long type;
	char text[MAX];
}message;
int main(){
	key_t key = ftok("progfile",65);
	int msgid = msgget(key, 0666 | IPC_CREAT);
	printf("Waiting fpr the message");
	msgrcv(msgid,&message,sizeof(message.text),1,0);
	printf("REceived:%s\n",message.text);
	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}

