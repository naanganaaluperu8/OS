#include<stdio.h>
#include<stdlib.h>
int main(){
	int n;
	printf("Enter number of process:");
	scanf("%d",&n);
	int pid[n],at[n],bt[n],ft[n],tat[n],wt[n];
	int tot_wt = 0;
	int tot_tat = 0;
	float awt,atat;
	for(int i = 0;i<n;i++){
		printf("Enter the process id:");
		scanf("%d",&pid[i]);
		printf("enter the arriva; time:");
		scanf("%d",&at[i]);
		printf("Enter the burst time:");
		scanf("%d",&bt[i]);
	}
	for(int i = 0;i<n-1;i++){
		for(int j = i+1;j<n;j++){
			if(bt[i]>bt[j]){
				int temp = bt[i];
				bt[i] = bt[j];
				bt[j] = temp;

				temp = at[i];
				at[i] = at[j];
				at[j] = temp;

				temp = pid[i];
				pid[i] = pid[j];
				pid[j] = temp;
			}
		}
	}
	for(int i = 0;i<n;i++){
		if(i==0){
			ft[i] = at[i] + bt[i];
			wt[i] = 0;
		}
		else{
			if(ft[i-1]<at[i]){
				ft[i] = at[i] + bt[i];
			}
			else{
				ft[i] = ft[i-1] +bt[i];
			}
			wt[i] = ft[i] - at[i] - bt[i];
		}
		tat[i] = ft[i] - at[i];
	}
	printf("The details are:");
	printf("PID\tAT\tBT\tFT\tTAT\tWT\n");
	for(int i = 0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],at[i],bt[i],ft[i],tat[i],wt[i]);
		tot_wt+=wt[i];
		tot_tat+=tat[i];
	}
	awt = (float)tot_wt/n;
	atat = (float)tot_tat/n;
	printf("%.2f\n",awt);
	printf("%.2f\n",atat);
	return 0;
}

