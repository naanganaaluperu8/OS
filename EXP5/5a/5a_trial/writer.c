#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#define SHMSZ 27
int main(){
	int shmid;
	key_t key = 5678;
	char *shm,*s;
	shmid = shmget(key,SHMSZ,IPC_CREAT | 0666);
	if(shmid<0){
		printf("Cannot create:");
		exit(1);
	}
	shm = shmat(shmid,NULL,0);
	if(shm<0){
		printf("Cannot allocate:");
		exit(1);
	}
	s=shm;
	for(char c = 'a';c<='z';c++){
		*s = c;
		s++;
	}
	while(*shm!='*'){
		sleep(1);
	}
	return 0;
}
