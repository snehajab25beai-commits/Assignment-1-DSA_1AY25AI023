#include <stdio.h>
#include <math.h>

typedef struct {
    int   degree;
    float coef[101];   /* coef[i] = coefficient of x^(degree-i) */
} polynomial;

/* a. Read a polynomial */
polynomial readPoly(void)
{
    polynomial p;
    int i;

    printf("Enter degree: ");
    scanf("%d", &p.degree);

    printf("Enter %d coefficients (highest power first): ", p.degree + 1);
    for (i = 0; i <= p.degree; i++)
        scanf("%f", &p.coef[i]);

    return p;
}

/* b. Add two polynomials term by term */
polynomial add(polynomial a, polynomial b)
{
    polynomial r;
    float sum[101];
    int maxdeg, e, i;

    maxdeg = (a.degree > b.degree) ? a.degree : b.degree;

    /* Step 1: add coefficients exponent by exponent */
    for (e = 0; e <= maxdeg; e++) {
        sum[e] = 0;
        if (e <= a.degree)
            sum[e] += a.coef[a.degree - e];
        if (e <= b.degree)
            sum[e] += b.coef[b.degree - e];
    }

    /* Step 2: find the highest exponent whose coefficient is not 0 */
    r.degree = maxdeg;
    while (r.degree > 0 && sum[r.degree] == 0)
        r.degree--;

    /* Step 3: store in the same format (highest power first) */
    for (i = 0; i <= r.degree; i++)
        r.coef[i] = sum[r.degree - i];

    return r;
}

/* c. Display in the form 3x^4 + 2x^2 + 1 */
void display(polynomial p)
{
    int i, exp, first = 1;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c   = p.coef[i];
        exp = p.degree - i;

        if (c == 0)                      /* skip zero terms */
            continue;

        /* sign */
        if (first) {
            if (c < 0) printf("-");
        } else {
            printf(c < 0 ? " - " : " + ");
        }

        /* coefficient (omit a coefficient of 1 before x) */
        if (fabs(c) != 1 || exp == 0)
            printf("%g", fabs(c));

        /* variable part */
        if (exp == 1)
            printf("x");
        else if (exp > 1)
            printf("x^%d", exp);

        first = 0;
    }

    if (first)                           /* every term was zero */
        printf("0");
    printf("\n");
}

int main(void)
{
    polynomial A, B, C;

    printf("--- Polynomial A ---\n");
    A = readPoly();
    printf("--- Polynomial B ---\n");
    B = readPoly();

    printf("\nA(x) = "); display(A);
    printf("B(x) = ");   display(B);

    C = add(A, B);
    printf("A(x) + B(x) = ");
    display(C);

    return 0;
}
