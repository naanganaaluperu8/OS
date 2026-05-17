#include <stdio.h>

int max[10][10], alloc[10][10], need[10][10];
int avail[10], work[10], finish[10];
int n, r;

// Input Function
void read() {

    int i, j;

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &r);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for (j = 0; j < r; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Print Need Matrix
    printf("\nNeed Matrix:\n");

    for (i = 0; i < n; i++) {

        for (j = 0; j < r; j++) {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }
}

// Safety Algorithm
int safety() {

    int i, j, k;
    int count = 0;
    int flag;
    int safe[10];

    printf("\nChecking Safety...\n");

    // Copy avail to work
    for (j = 0; j < r; j++) {
        work[j] = avail[j];
    }

    // Initially unfinished
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    while (count < n) {

        flag = 0;

        for (i = 0; i < n; i++) {

            if (finish[i] == 0) {

                int possible = 1;

                // Check Need <= Work
                for (j = 0; j < r; j++) {

                    if (need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                // Process can execute
                if (possible) {

                    printf("Process P%d can execute\n", i);

                    // Release resources
                    for (k = 0; k < r; k++) {
                        work[k] += alloc[i][k];
                    }

                    finish[i] = 1;

                    safe[count] = i;
                    count++;

                    flag = 1;
                }
            }
        }

        // No process executed
        if (flag == 0) {
            printf("No further process can execute\n");
            break;
        }
    }

    // Safe State
    if (count == n) {

        printf("\nSystem is SAFE\n");

        printf("Safe Sequence: ");

        for (i = 0; i < n; i++) {
            printf("P%d ", safe[i]);
        }

        printf("\n");

        return 1;
    }

    // Unsafe State
    else {

        printf("\nSystem is UNSAFE\n");

        return 0;
    }
}

// Resource Request Algorithm
void request() {

    int p, i;
    int req[10];

    printf("\nEnter process number: ");
    scanf("%d", &p);

    printf("Enter request: ");

    for (i = 0; i < r; i++) {
        scanf("%d", &req[i]);
    }

    // Check Request <= Need
    for (i = 0; i < r; i++) {

        if (req[i] > need[p][i]) {
            printf("Error: Request exceeds need\n");
            return;
        }

        // Check Request <= Available
        if (req[i] > avail[i]) {
            printf("Wait: Not enough resources\n");
            return;
        }
    }

    printf("\nTrying temporary allocation...\n");

    // Temporary Allocation
    for (i = 0; i < r; i++) {

        avail[i] -= req[i];
        alloc[p][i] += req[i];
        need[p][i] -= req[i];
    }

    // Check Safety Again
    if (!safety()) {

        printf("Rollback: Unsafe after allocation\n");

        // Rollback
        for (i = 0; i < r; i++) {

            avail[i] += req[i];
            alloc[p][i] -= req[i];
            need[p][i] += req[i];
        }
    }

    else {

        printf("Request GRANTED\n");
    }
}

// Main Function
int main() {

    read();

    if (safety()) {

        request();
    }

    else {

        printf("Initial system is unsafe\n");
    }

    return 0;
}
