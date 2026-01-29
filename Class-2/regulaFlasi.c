//find a root of the equation 3x-1-cos(x)=0 using regula falsi method
#include <stdio.h>
#include <math.h>   
#define f(x) (3*x - 1 - cos(x))
int main()
{
    float a, b, c, fa, fb, fc, tol;
    int max_iter, iter;
    //initial guesses
    a = 0.0;
    b = 1.0;
    tol = 0.0001;
    max_iter = 100;
    fa = f(a);
    fb = f(b);
    if (fa * fb >= 0)
    {
        printf("The function must have different signs at the endpoints a and b.\n");
        return -1;
    }
    for (iter = 1; iter <= max_iter; iter++)
    {
        //calculate the point c
        c = (a * fb - b * fa) / (fb - fa);
        fc = f(c);
        //check for convergence
        if (fabs(fc) < tol)
        {
            printf("Root found at x = %f after %d iterations\n", c, iter);
            return 0;
        }
        //update the interval
        if (fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }
    printf("Maximum iterations reached. Approximate root at x = %f\n", c);
    return 0;
}
