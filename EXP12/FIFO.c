#include<stdio.h>
int main(){
	int frames[3];
	int ref[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
	int n = 13;
	int nf = 3;
	int fault = 0;
	int ptr = 0;
	for(int i = 0;i<nf;i++){
		frames[i] = -1;
	}
	for(int i = 0;i<n;i++){
		int found = 0;
		for(int j = 0;j<nf;j++){
			if(ref[i] == frames[j]){
				found = 1;
				break;
			}
		}
		if(found == 0){
			frames[ptr] = ref[i];
			ptr = (ptr+1)%nf;
			fault++;
		}
		printf("%d\t",ref[i]);
		for(int j = 0;j<nf;j++){
			if(frames[j] == -1){
				printf("-");
			}
			else{
				printf("%d ",frames[j]);
			}
		}
		if(found == 0){
			printf("<-- Page Fault");
		}
		printf("\n");
	}
	 printf("\nTotal Page Faults = %d\n", fault);
	 printf("Hit Ratio = %.2f\n", (float)(n - fault) / n);
	 return 0;
}

