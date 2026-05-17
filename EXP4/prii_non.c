#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,done = 0;
	printf("Enter number of process:");
	scanf("%d",&n);
	int pid[n],at[n],bt[n];
	int ft[n],tat[n],pri[n],wt[n],comp[n];
	for(int i = 0;i<n;i++){
		printf("Enter the PID:");
		scanf("%d",&pid[i]);
		printf("Enter the AT:");
		scanf("%d",&at[i]);
		printf("Enter the burst time:");
		scanf("%d",&bt[i]);
		printf("Enter the priority:");
		scanf("%d",&pri[i]);
		comp[i] = 0;
		ft[i] = 0;
		wt[i] = 0;
		tat[i] = 0;
	}
	int time = 0;
	while(done<n){
		int idx = -1;
		int min = 9999;
		for(int i = 0;i<n;i++){
			if(at[i]<=time && comp[i] == 0){
				if(pri[i]<min){
					idx = i;
					min = pri[i];
				}
			}
		}
		if(idx!=-1){
			ft[idx] = time + bt[idx];
			tat[idx] = ft[idx] - at[idx];
			wt[idx] = tat[idx] - bt[idx];
			comp[idx] = 1;
			time = ft[idx];
			done++;
		}
		else{
			time++;
		}
	}
	printf("PID\tAT\tBT\tFT\tWT\tTAT\n");
	for(int i = 0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],at[i],bt[i],ft[i],wt[i],tat[i]);
	}
	return 0;
}


