#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,i;
	int s1=0,s2=0;
	float AWT,ATAT;
	printf("Enter the number of precoess:");
	scanf("%d",&n);
	int pid[n],at[n],bt[n],ft[n],wt[n],tat[n];
	for(i=0;i<n;i++){
		printf("Enter the prcess id:");
		scanf("%d",&pid[i]);
		printf("\nEnter the arrival time:");
		scanf("%d",&at[i]);
		printf("\nEnter the burst time:");
		scanf("%d",&bt[i]);
	}
	for(i=0;i<n;i++){
		if(i==0){
			ft[i]=at[i]+bt[i];
			wt[i] = 0;
		}
		else{
			if(ft[i-1]<at[i])
				ft[i]=at[i]+bt[i];
			else
				ft[i] = ft[i-1]+bt[i];
			wt[i]=ft[i]-at[i]-bt[i];
		}
		tat[i] = ft[i] - at[i];
	}
	printf("\nThe details are:\n");
	printf("Pid\tAT\tBT\tFT\tWT\tTAT\t\n");

	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t\n",pid[i],at[i],bt[i],ft[i],wt[i],tat[i]);
		s1+=wt[i];
		s2+=tat[i];
	}
	AWT=(float)s1/n;
	ATAT=(float)s2/n;
	return 0;
}

