#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 20
int disk[SIZE];
struct file{
	char name[20];
	int index;
	int block[20];
	int count;
};
struct file f[10];
int fc= 0;
int getBlock(){
	for(int i = 0;i<SIZE;i++){
		if(disk[i] == 0){
			disk[i] = 1;
			return i;
		}
	}
	return -1;
}
void allocate(char name[],int n){
	strcpy(f[fc].name,name);
	f[fc].index = getBlock();
	for(int i = 0;i<n;i++){
		f[fc].block[i] = getBlock();
	}
	f[fc].count = n;
	fc++;
}
int main(){
	allocate("A",3);
	allocate("B",4);
	printf("Indexed allocation of memory:");
	for(int i = 0;i<fc;i++){
		printf("%s -> Index block: %d:",f[i].name,f[i].index);
		for(int j = 0;j<f[i].count;j++){
			printf("%d ", f[i].block[j]);
		}
		printf("\n");
	}
	return 0;
}
