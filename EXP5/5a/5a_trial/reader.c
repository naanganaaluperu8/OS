#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#define SHMSZ 27
int main(){
	int shmid;
	key_t key = 5678;
	char *shm,*s;
	shmid = shmget(key,SHMSZ,0666);
	if(shmid<0){
		printf("cannot create");
		exit(1);
	}
	shm=shmat(shmid,NULL,0);
	if(shm<0){
		printf("Cannot allocate:");
		exit(1);
	}
	for(s=shm;*s!='\0';s++){
		printf("%c",*s);
	}
	printf("\n");
	*shm='*';
	return 0;
}

