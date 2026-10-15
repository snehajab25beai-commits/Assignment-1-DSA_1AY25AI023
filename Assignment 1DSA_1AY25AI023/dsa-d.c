#include <stdio.h>

#define MAX 101

typedef struct { int row, col, value; } term;

/* Prints a triples array */
void printTriples(term a[])
{
    int i;
    printf("Row\tCol\tValue\n");
    for (i = 0; i <= a[0].value; i++)
        printf("%d\t%d\t%d\n", a[i].row, a[i].col, a[i].value);
}

/* Fast transpose using row_terms[] and starting_pos[] */
void fast_transpose(term a[], term b[])
{
    int row_terms[MAX], starting_pos[MAX];
    int i, j, numCols, numTerms;

    numCols  = a[0].col;
    numTerms = a[0].value;

    /* header of b: rows and cols swapped */
    b[0].row   = numCols;
    b[0].col   = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {
        /* Step 1: count terms in each column of a */
        for (i = 0; i < numCols; i++)
            row_terms[i] = 0;
        for (i = 1; i <= numTerms; i++)
            row_terms[a[i].col]++;

        /* Step 2: starting position of each row of b */
        starting_pos[0] = 1;
        for (i = 1; i < numCols; i++)
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];

        /* print the two arrays (before they get modified) */
        printf("\ni\t\trow_terms[i]\tstarting_pos[i]\n");
        for (i = 0; i < numCols; i++)
            printf("%d\t\t%d\t\t%d\n", i, row_terms[i], starting_pos[i]);

        /* Step 3: place each term directly at its final position */
        for (i = 1; i <= numTerms; i++) {
            j = starting_pos[a[i].col]++;
            b[j].row   = a[i].col;
            b[j].col   = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

int main()
{
    term a[MAX], b[MAX];
    int  r, c, i, j, x, count = 0;

    /* a. Read matrix: rows, cols, then all elements */
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    printf("Enter the matrix elements row by row:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &x);
            /* b. store only non-zero elements as triples */
            if (x != 0) {
                count++;
                a[count].row   = i;
                a[count].col   = j;
                a[count].value = x;
            }
        }
    }
    a[0].row   = r;
    a[0].col   = c;
    a[0].value = count;

    /* d. original triples */
    printf("\nOriginal matrix triples:\n");
    printTriples(a);

    /* c. fast transpose */
    fast_transpose(a, b);

    /* d. transposed triples */
    printf("\nTransposed matrix triples:\n");
    printTriples(b);

    return 0;
}

