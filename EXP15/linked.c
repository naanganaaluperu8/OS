#include<stdio.h>
#include<string.h>
#define SIZE 15
int disk[SIZE];
int next[SIZE];
struct file{
	char name[20];
	int start;
};
struct file f[10];
int fc = 0;
int getBlock(){
	for(int i = 0;i<SIZE;i++){
		if(disk[i]==0){
			disk[i] = 1;
			return i;
		}
	}
	return -1;
}
void allocate(char name[], int n){
	int first = -1;
	int prev = -1;
	for(int i = 0;i<n;i++){
		int b = getBlock();
		next[b] = -1;
		if(first == -1){
			first = b;
		}
		else{
			next[prev] = b;
		}
		prev = b;
	}
	strcpy(f[fc].name,name);
	f[fc].start = first;
	fc++;
}
int main(){
	allocate("A", 3);
    allocate("B", 4);

    printf("Linked File Allocation\n");

    for(int i = 0; i < fc; i++) {

        printf("%s : ", f[i].name);

        int cur = f[i].start;

        while(cur != -1) {
            printf("%d -> ", cur);
            cur = next[cur];
        }

        printf("NULL\n");
    }

    return 0;
}


