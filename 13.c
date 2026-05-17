#include<stdio.h>
#include<stdlib.h>
int main(){
	int queue[] = {82, 170, 43, 140, 24, 16, 190};
	int n=7;
	int head = 50;
	int total = 0;
	printf("FCFS Disk Scheduling\n");

    	printf("Initial Head Position = %d\n\n", head);

    	printf("Move\tDistance\n");
	for(int i = 0;i<n;i++){
		int distance = abs(head-queue[i]);
		total = total - distance;
		printf("%d -> %d\t%d\n", head, queue[i], distance);
		head = queue[i];
	}
	 printf("\nTotal Seek Distance = %d\n", total);

    printf("Average Seek Distance = %.2f\n", (float)total / n);

    return 0;
}
