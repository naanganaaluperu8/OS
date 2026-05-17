#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 20
int disk[SIZE];
struct file{
	char name[20];
	int start;
	int length;
};
struct file f[10];
int count = 0;
void allocate(char name[],int length){
	int free = 0;
	int start = 0;
	for(int i = 0;i<SIZE;i++){
		if(disk[i] == 0){
			if(free==0){
				start = i;
			}
			free++;
		}
		else{
			free =0;
		}
		if(free==length){
			for(int j = start;j<start+length;j++){
				disk[j] = 1;
			}
			strcpy(f[count].name,name);
			f[count].start = start;
			f[count].length = length;
			count++;
			printf("%s allocated from %d to %d\n",
                   name, start, start + length - 1);
			return;
		}
	}
	printf("No space for %s\n", name);
}
int main() {

    allocate("A", 4);
    allocate("B", 3);
    allocate("C", 5);

    printf("\nFile Allocation Table\n");

    for(int i = 0; i < count; i++) {
        printf("%s -> Start: %d Length: %d\n",
               f[i].name,
               f[i].start,
               f[i].length);
    }

    return 0;
}
		

