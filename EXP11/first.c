#include<stdio.h>
int main(){
	int block[] = {100,500,200,300,600};
	int process[] = {212,417,112,426};
	int nb = 5,np = 4;
	int allocation[np];
	for(int i = 0;i<np;i++){
		allocation[i] = -1;
	}
	for(int i = 0;i<np;i++){
		for(int j = 0;j<nb;j++){
			if(block[j]>process[i]){
				allocation[i] = j + 1;
				block[j] = block[j] - process[i];
				break;
			}
		}
	}
	printf("Process\tSize\tBlock\n");

    for(int i = 0; i < np; i++) {

        printf("P%d\t%d\t", i + 1, process[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i]);
        else
            printf("Not Allocated\n");
    }

    return 0;
}

