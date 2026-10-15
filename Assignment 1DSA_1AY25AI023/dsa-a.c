#include <stdio.h>
#include <stdlib.h>

struct Student {
    int   roll_no;
    char  name[20];
    float marks;
};

int main()
{
    int n, i;
    char choice;
    float sum;
    struct Student *ptr, *top;

    /* a. Ask for n and allocate memory */
    printf("Enter number of students: ");
    scanf("%d", &n);
    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    /* b. Read n records */
    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %s %f", &(ptr + i)->roll_no, (ptr + i)->name, &(ptr + i)->marks);
    }

    /* c. Average and topper */
    sum = 0;
    top = ptr;
    for (i = 0; i < n; i++) {
        sum = sum + (ptr + i)->marks;
        if ((ptr + i)->marks > top->marks)
            top = ptr + i;
    }
    printf("\nAverage marks: %.2f\n", sum / n);
    printf("Topper: %s (Roll %d, Marks %.2f)\n", top->name, top->roll_no, top->marks);

    /* e. Add 2 more students using realloc */
    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y') {
        ptr = (struct Student *)realloc(ptr, (n + 2) * sizeof(struct Student));
        for (i = n; i < n + 2; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %s %f", &(ptr + i)->roll_no, (ptr + i)->name, &(ptr + i)->marks);
        }
        n = n + 2;

        sum = 0;
        for (i = 0; i < n; i++)
            sum = sum + (ptr + i)->marks;
        printf("Updated average marks: %.2f\n", sum / n);
    }

    /* d. Free memory */
    free(ptr);
    return 0;
}
