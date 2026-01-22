//Finding a root of the equation f(x)=x^3-6x^2+11x-6.1 using the Bisection Method correct upto
//five decimal places.
#include <stdio.h>
#include <math.h>
#define f(x) (x*x*x - 6*x*x + 11*x - 6.1)
void main() {
    float a, b, c;
    int i, n;
    printf("Enter the initial guesses a and b:\n");
    scanf("%f%f", &a, &b);
    printf("Enter the number of iterations:\n");
    scanf("%d", &n);
    if (f(a) * f(b) >= 0) {
        printf("Incorrect initial guesses. f(a) and f(b) must have opposite signs.\n");
        return;
    }
    for (i = 0; i < n; i++) {
        c = (a + b) / 2;
        if (f(c) == 0.0) {
            break; // c is the root
        } else if (f(c) * f(a) < 0) {
            b = c; // The root lies between a and c
        } else {
            a = c; // The root lies between c and b
        }
    }
    printf("The root is: %.5f\n", c);
}
/*
--------------output--------------
Enter the initial guesses a and b:
2 4
Enter the number of iterations:
10
The root is: 3.10000
-----------------------------------
problem 1 solved successfully.
*/