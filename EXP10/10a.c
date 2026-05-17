#include <stdio.h>

int main() {

    int n;

    printf("Enter number of segments: ");
    scanf("%d", &n);

    int base[n], limit[n];

    // Input base and limit
    for (int i = 0; i < n; i++) {

        printf("Enter base of segment %d: ", i);
        scanf("%d", &base[i]);

        printf("Enter limit of segment %d: ", i);
        scanf("%d", &limit[i]);
    }

    while (1) {

        int segment, offset;

        printf("\nEnter segment number: ");
        scanf("%d", &segment);

        printf("Enter offset: ");
        scanf("%d", &offset);

        // Check valid segment
        if (segment >= n || segment < 0) {
            printf("Invalid segment number\n");
            continue;
        }

        // Check valid offset
        if (offset < limit[segment]) {

            int pa = base[segment] + offset;

            printf("Physical Address = %d\n", pa);
        }
        else {

            printf("Illegal Address\n");
        }
    }

    return 0;
}
