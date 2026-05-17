#include<stdio.h>
int main(){
	int nf = 3;
	int frame[nf];
	int time[nf];
	int ref[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
	int n = 13;
	int faults = 0;
	int t = 0;
	for(int i = 0;i<nf;i++){
		frame[i] = -1;
		time[i] = 0;
	}
	printf("Page\tFrames\n");
	for(int i = 0;i<n;i++,t++){
		int found = -1;
		for(int j = 0;j<nf;j++){
			if(frame[j] == ref[i]){
				found = j;
				break;
			}
		}
		if(found==-1){
			int lru = 0;
			for(int j = 1;j<nf;j++){
				if(time[j]<time[lru]){
					lru = j;
				}
			}
			frame[lru] = ref[i];
			time[lru] = t;
			faults++;
		}
		else{
			time[found] = t;
		}
		 printf("%d\t", ref[i]);

        for(int j = 0; j < nf; j++) {

            if(frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }

        if(found == -1)
            printf("<-- Page Fault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    printf("Hit Ratio = %.2f\n", (float)(n - faults) / n);

    return 0;
}



