#include<stdio.h>

int main() {

    int n, done = 0;

    printf("Enter number of process: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], pri[n];
    int ft[n], wt[n], tat[n], comp[n];

    // Input
    for(int i = 0; i < n; i++) {

        printf("Enter AT BT PRI for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pri[i]);

        rt[i] = bt[i];

        comp[i] = 0;

        ft[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }

    int time = 0;

    // Preemptive Priority Scheduling
    while(done < n) {

        int idx = -1;
        int min = 9999;

        // Find highest priority process
        for(int i = 0; i < n; i++) {

            if(at[i] <= time && comp[i] == 0) {

                // Smaller number = higher priority
                if(pri[i] < min) {

                    min = pri[i];
                    idx = i;
                }
            }
        }

        // If process found
        if(idx != -1) {

            // Execute for 1 unit
            rt[idx]--;

            time++;

            // Process completed
            if(rt[idx] == 0) {

                ft[idx] = time;

                tat[idx] = ft[idx] - at[idx];

                wt[idx] = tat[idx] - bt[idx];

                comp[idx] = 1;

                done++;
            }
        }

        // CPU Idle
        else {

            time++;
        }
    }

    // Output
    printf("\nAT\tBT\tPRI\tFT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
                at[i],
                bt[i],
                pri[i],
                ft[i],
                tat[i],
                wt[i]);
    }

    return 0;
}
