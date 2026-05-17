#include <stdio.h>

int main() {

    int process_size, page_size;
    int LA;

    printf("Enter process size and page size: ");
    scanf("%d %d", &process_size, &page_size);

    int noofpages = process_size / page_size;

    printf("Number of pages = %d\n", noofpages);

    // Input logical address
    printf("Enter Logical Address: ");
    scanf("%d", &LA);

    // Calculate page number and offset
    int pageno = LA / page_size;
    int offset = LA % page_size;

    printf("Page Number = %d\n", pageno);
    printf("Offset = %d\n", offset);

    int pagetable[100];

    // Input page table
    for (int i = 0; i < noofpages; i++) {

        printf("Enter frame number for page %d: ", i);
        scanf("%d", &pagetable[i]);
    }

    // Check valid page number
    if (pageno >= noofpages) {

        printf("Invalid Logical Address\n");
    }
    else {

        int PA = (pagetable[pageno] * page_size) + offset;

        printf("Physical Address = %d\n", PA);
    }

    return 0;
}
