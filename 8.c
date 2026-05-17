#include <stdio.h>

int alloc[10][10], request[10][10];
int avail[10], work[10], finish[10];
int n, r;

void read() {
    int i, j;

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &r);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < r; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < r; j++)
        scanf("%d", &avail[j]);
}

void detect() {
    int i, j, k, flag;

    // Step 1: Initialize work = available
    for (j = 0; j < r; j++)
        work[j] = avail[j];

    // Step 2: Initialize finish = 0
    for (i = 0; i < n; i++)
        finish[i] = 0;

    printf("\nChecking Deadlock...\n");

    // Step 3: Try to find processes that can complete
    while (1) {
        flag = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int possible = 1;

                // Check if request <= work
                for (j = 0; j < r; j++) {
                    if (request[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                // If possible, simulate completion
                if (possible) {
                    printf("Process P%d can finish\n", i);

                    for (k = 0; k < r; k++)
                        work[k] += alloc[i][k];

                    finish[i] = 1;
                    flag = 1;
                }
            }
        }

        // If no process executed → stop
        if (flag == 0)
            break;
    }

    // Step 4: Check unfinished processes
    int deadlock = 0;
    printf("\nDeadlocked Processes: ");

    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if (!deadlock)
        printf("None (No Deadlock)");

    printf("\n");
}

int main() {
    read();
    detect();
    return 0;
}
