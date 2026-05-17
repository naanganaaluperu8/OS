#include<stdio.h>
int main(){
	int n,done = 0;
	printf("Enter number of process:");
	scanf("%d",&n);
	int at[n],bt[n],comp[n];
	int ft[n],wt[n],tat[n],rt[n],pri[n];

	for(int i = 0;i<n;i++){
		printf("Enter the process at and bt and pri:");
		scanf("%d %d %d",&at[i],&bt[i],&pri[i]);
		rt[i] = bt[i];
		comp[i] = 0;
	}
	int time = 0;
	while(done<n){
		int min = 9999;
		int idx = -1;
		for(int i = 0;i<n;i++){
			if(at[i]<=time && comp[i] == 0){
				if(pri[i]<min){
					idx= i;
					min = pri[i];
				}
			}
		}
		if(idx!=-1){
			rt[idx]--;
			time++;
			if(rt[idx] == 0){
				ft[idx] = time;
				tat[idx] = ft[idx]-at[idx];
				wt[idx] = tat[idx]-bt[idx];
				comp[idx] = 1;
				done++;
			}
		}
		else{
			time++;
		}
//		return 0;
	}
	return 0;
}
