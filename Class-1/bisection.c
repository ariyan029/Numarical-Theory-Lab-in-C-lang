#include <stdio.h>
#include <math.h>
#define ESP 0.000001
#define f(x) x * x * x - 2 * x - 5;
void main()
{
    int i = 1;
    float x0, x1, x2, fx0, fx1, fx2;

    printf("\nEnter the value of x0: ");
    scanf("%f", &x0);
    printf("\nEnter the value of x1: ");
    scanf("%f", &x1);
    printf("\n Intteration\t x0 \t\t x1 \t\tx2 \t   f(x2) ");

    do
    {
        x2 = (x0 + x1) / 2;
        fx0 = f(x0);
        fx1 = f(x1);
        fx2 = f(x2);

        printf("\n %d \t %10.4f \t %10.4f \t %10.4f \t %10.4f", i, x0, x1, x2, fx2);

        if (fx0 * fx2 < 0)
        {
            x1 = x2;
        }
        else
        {
            x0 = x2;
        }
        i++;
    } while (fabs(fx2) > ESP);

    printf("\n\n Approx val od root is: %10.4f", x2);
}