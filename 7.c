#include<stdio.h>
int max[10][10],alloc[10][10],need[10][10];
int avail[10],work[10],finished[10];
int n,r;
void read(){
	printf("Enter number of process:");
	scanf("%d",&n);
	printf("Enter number of resources:");
	scanf("%d",&r);
	int i = 0,j =0;
	printf("Enter the max matrix:");
	for(i=0;i<n;i++){
		for(j=0;j<nj++){
			scanf("%d",&max[i][j]);
		}
	}
	printf("Enter the allocation matrix:");
	 for(i=0;i<n;i++){
                for(j=0;j<nj++){
                        scanf("%d",&alloc[i][j]);
                }
        }
	for(i=0;i<n;i++){
                for(j=0;j<nj++){
                        need[i][j] = max[i][j] - alloc[i][j];
                }
        }
	for(i=0;i<n;i++){
                for(j=0;j<nj++){
                        printf("%d ",need[i][j]);
                }
		printf("\n");
        }
}
int safe(){
	int safe[10];
	int i,j;
	for(j = 0;j<r;j++){
		work[j] = avail[j];
	}
	for(j = o;j<n;j++){
		finished[j] = 0;
	}
	int count = 0;
	while(count<n){
		int flag = 0;
		for(i=0;i<n;i++){
			if(finish[i]==0){
				int possible = 1;
				for(j=0;j<r;j++){
					if(need[i][j]>work[j]){
						possible = 0;
						break;
					}
				}
				if(possible){
					for(int k = 0;k<r;k++){
						work+=alloc[i][k];
					}
					finish[i] = 1;
					safe[count++] = i;
					falg = 1;
				}
			}
		}
		if(!flag){
			printf("No process");
			break;
		}
	}
	if(count == n){
		printf("safe sequencr");
		return 1;
	}
	else {
		return 0;
	}
}


void request(){




