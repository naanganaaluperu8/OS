#include <stdio.h>

int main() {

    int frames[3];
    int ref[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};

    int n = 13;
    int nf = 3;

    int faults = 0;

    // Initialize empty frames
    for(int i = 0; i < nf; i++) {
        frames[i] = -1;
    }

    printf("Page\tFrames\n");

    for(int i = 0; i < n; i++) {

        int found = 0;

        // Check page already exists
        for(int j = 0; j < nf; j++) {

            if(frames[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        // Page Fault
        if(found == 0) {

            int pos = -1;

            // First fill empty frames
            for(int j = 0; j < nf; j++) {

                if(frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, apply Optimal
            if(pos == -1) {

                int farthest = -1;

                for(int j = 0; j < nf; j++) {

                    int k;

                    // Search future use
                    for(k = i + 1; k < n; k++) {

                        if(frames[j] == ref[k]) {
                            break;
                        }
                    }

                    // Never used again
                    if(k == n) {
                        pos = j;
                        break;
                    }

                    // Used farthest later
                    if(k > farthest) {

                        farthest = k;
                        pos = j;
                    }
                }
            }

            // Replace page
            frames[pos] = ref[i];

            faults++;
        }

        // Print frames
        printf("%d\t", ref[i]);

        for(int j = 0; j < nf; j++) {

            if(frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if(found == 0)
            printf("<-- Page Fault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    printf("Hit Ratio = %.2f\n", (float)(n - faults) / n);

    return 0;
}
