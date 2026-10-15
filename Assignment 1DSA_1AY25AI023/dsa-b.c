#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int  emp_id;
    enum { FULL_TIME, CONTRACT } type;
    union {
        float salary;
        struct {
            float hourly_rate;
            int   hours_worked;
        } contract_info;
    } pay;
} Employee;

int main()
{
    int       n, i, t;
    float     total, totalBill = 0;
    Employee *emp;

    /* a. Dynamic array */
    printf("Enter number of employees: ");
    scanf("%d", &n);
    emp = (Employee *)malloc(n * sizeof(Employee));

    /* b. Read employees */
    for (i = 0; i < n; i++) {
        printf("\nEmployee %d\n", i + 1);
        printf("Enter name: ");
        scanf("%s", emp[i].name);
        printf("Enter emp_id: ");
        scanf("%d", &emp[i].emp_id);
        printf("Enter type (0 = Full-time, 1 = Contract): ");
        scanf("%d", &t);

        if (t == 0) {
            emp[i].type = FULL_TIME;
            printf("Enter monthly salary: ");
            scanf("%f", &emp[i].pay.salary);
        } else {
            emp[i].type = CONTRACT;
            printf("Enter hourly rate: ");
            scanf("%f", &emp[i].pay.contract_info.hourly_rate);
            printf("Enter hours worked: ");
            scanf("%d", &emp[i].pay.contract_info.hours_worked);
        }
    }

    /* c. Payslips */
    printf("\n----- PAYSLIPS -----\n");
    for (i = 0; i < n; i++) {
        if (emp[i].type == FULL_TIME)
            total = emp[i].pay.salary;
        else
            total = emp[i].pay.contract_info.hourly_rate *
                    emp[i].pay.contract_info.hours_worked;

        printf("Name: %s | ID: %d | Type: %s | Total Pay: %.2f\n",
               emp[i].name,
               emp[i].emp_id,
               emp[i].type == FULL_TIME ? "Full-time" : "Contract",
               total);

        totalBill += total;
    }

    /* d. Total salary bill */
    printf("\nTotal salary bill of the company: %.2f\n", totalBill);

    free(emp);
    return 0;
}
