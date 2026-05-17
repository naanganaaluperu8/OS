#include<stdio.h>
#include<stdlib.h>
int main(){
	int n;
	printf("Enter the number of process:");
	scanf("%d",&n);
	int tq = 0;
	printf("Enter the time quantum:");
	scanf("%d",&tq);
	int pid[n],at[n],bt[n],ft[n],tat[n],wt[n],comp[n],rt[n],visited[n];
	for(int i = 0;i<n;i++){
		printf("Enter the process id:");
		scanf("%d",&pid[i]);
		printf("Enter the arrival time:");
		scanf("%d",&at[i]);
		printf("Enter the burst time:");
		scanf("%d",&bt[i]);
		rt[i] = bt[i];
		comp[i] = 0;
		visited[i] = 0;
		ft[i] = 0;
		tat[i] = 0;
		wt[i] = 0;
	}
	int time = 0,front = 0,rear = 0,done = 0;
	int queue[200];
	for(int i = 0;i<n;i++){
		if(at[i]<=time && visited[i] == 0){
			queue[rear++]=i;
			visited[i] = 1;
		}
	}
	while(done<n){
		if(front==rear){
			time++;
			for(int i = 0;i<n;i++){
				if(at[i]<=time && visited[i] == 0 ){
					queue[rear++]=i;
					visited[i] = 1;
				}
			}
			continue;
		}
		int i = queue[front++];
		if(rt[i]>tq){
			rt[i]-=tq;
			time+=tq;
		}
		else{
			time+=rt[i];
			rt[i] = 0;
			ft[i] = time;
			tat[i] = ft[i] - at[i];
			wt[i] = tat[i] - bt[i];
			comp[i] = 1;
			done++;
		}
		for(int j = 0;j<n;j++){
			if(at[j]<=time && visited[j] == 0){
				queue[rear++] = j;
				visited[j] = 1;
			}
		}
		if(rt[i] > 0){
			queue[rear++] = i;
		}
	}
	for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               ft[i],
               tat[i],
               wt[i]);
    }

    return 0;
}

