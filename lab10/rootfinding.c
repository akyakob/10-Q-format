/***************************************************************************
  Student framework for root finding algorithms for bisection, newton, and secant.
   
  11/10/2015   R. Repka - Initial version
  12/28/2015 - R. Repka - added integer solution features
  11/12/2019 - R. Repka - Include bisection and newton sample code
***************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ClassErrors.h"
#include "rootfinding.h"


/******************************************************************************
 Purpose: Finds a root of scalar, nonlinear function f using the bisection  
 method. a and b make up the initial bracket to start bisecting from.
 
 Where: func1arg f  - function whose root is to be determined
                      must take a single argument of type double and return
        double a    - initial root bracket guess
        double b    - initial root bracket guess
        double atol - absolute error termination tolerance,
        int verb    - verbose flag, 1 = TRUE, 0 = FALSE
        
Returns: double - the root refined to the desired tolerance or NAN
Errors:  prints a message and returns with NAN                    
******************************************************************************/
double bisection(func1arg f, double a, double b, double atol, int verb)
{
    double c; /* midpoint */
    double fc; /* the value at the midpoint */
    int i=0; /* iterator */
    
    if ((fabs(a-b) < atol) ||  SIGN(f(a))==SIGN(f(b))){
        fprintf(stdout, "A and B do not center a root\n");
        return(NAN);
    }

    /* Limit the number of attempts */
    while(i < BI_LIMIT)
    {
        /* Calculate the mid point, evaluate it */
        c = (a+b)/2.0;
        fc = f(c);
        
        /* Did we find a root? - check the function */
         // not working if ((fabs(fc) <= atol) || ((fabs(a-b)/2.0) <= atol)) 
        if (fabs(fc) <= atol)
        {
    //        printf("Found root: %f using bisection\n", c);
            return c;
        }
        
        /* Did we find a root? - check the range */
        if (fabs(a-b)/2.0 <= atol) 
        {
    //       printf("Found root: %f using bisection\n", c);
           return(c);
        }
        
        if(verb)
        {
            fprintf(stdout, "iter:%d	a:%f	b:%f	x:%f	err:%f\n",
                    i, a, b, c, fabs(b-c));
        }
        
        /* Pick the next bracket */
        if (SIGN(f(a))==SIGN(fc))
        {
            a = c;
        }
        else
        {
            b = c;
        }
        i++;
    }
    fprintf(stdout, "Bisection could not find a root with %d iterations\n", BI_LIMIT);
    return(NAN);
}


/******************************************************************************
 Purpose: Finds a root of function f using the newton method. x0 is the initial 
 guess,  df is the derivative of function f , Nmax is the maximum number
  of iterations, atol is the tolerance, and verb will turn a verbose print* out

  Where: func1arg f  - function whose root is to be determined
                       must take single argument of type double and return
                       single value of type double
         func1arg df - derivative of function whose root is to be determined
                       must take single argument of type double and return
                       single value of type double
         double x0   - initial guess for location of root
         int Nmax    - maximum number of iterations to achieve convergence
         double atol - absolute error convergence tolerance
         int verb    - verbose flag, 1 = TRUE, 0 = FALSE

Returns: double - the root refined to the desired tolerance or NAN
Errors:  prints a message and returns with NAN      
******************************************************************************/
double newton(func1arg f, func1arg df, double x0, int Nmax, double atol, int verb)
{
   double fx0;		/* Value of f(x0) */
    double dx0;		/* Derivative of f(x0) */
    double x1;		/* New x0 value */
    int i=0;		/* Iteration */

    if(fabs(f(x0))< atol){
        return x0;
    }

    while(i < Nmax)
    {
        /* Evaluate the function at the initial point */
        fx0 = f(x0);
        dx0 = df(x0);

        /* If the slope or derivative is close to zero then Newton won't converge */ 
        if(fabs(dx0) < atol) 
        {
            fprintf(stdout, "Newton could NOT converge on a root.\n");
			return(NAN);
        }       
        /* Calculate the updated point */
        x1 = x0 - fx0/dx0;
        if(fabs(x1-x0) < atol)  /* was if(fabs(x1-x0)/fabs(x1) < atol) which I think is wrong */
        {
           printf("Found root: %f using newton\n", x1);
            return x1;
        }
        
        if(verb)
        {
            fprintf(stdout, "iter:%d	x0:%f	x1:%f	err:%f\n",
                    i, x0, x1, fabs(x1 - x0));
        }
        x0 = x1;
        i++;
    }
    fprintf(stdout, "Newton could not find a root with %d iterations\n", Nmax);
    return(NAN);
}


/******************************************************************************
 Purpose: Finds a root of function f using the secant method. x0 and x1 are 
 the two initial guesses used to find the first tangent.
 
 Where: func1arg f  - function whose root is to be determined
                       must take single argument of type double and return
                       single value of type double
         double x0   - initial guess for location of root
         double x1   - another initial guess for location of root
         int Nmax    - maximum number of iterations to achieve convergence
         double atol - absolute error convergence tolerance
         int verb    - verbose flag, 1 = TRUE, 0 = FALSE

Returns: double - the root refined to the desired tolerance or NAN
Errors:  prints a message and returns with NAN        
******************************************************************************/
double secant(func1arg f, double x0, double x1, int Nmax, double atol, int verb)
{
   double fx0;		/* Value of f(x0) */
   double fx1;
    double x2;          /* 2nd guess for secant*/
    int i=0;		/* Iteration */
    if(fabs(f(x0))< atol){
        return x0;
    }
    while(i < Nmax)
    {    /* Evaluate the function at the initial point */
        fx0 = f(x0);
	fx1 = f(x1);
        /* If the slope or derivative is close to zero then Secant won't converge */ 
       /* if(fabs(dx0) < atol) 
        {
            fprintf(stdout, "Secant could NOT converge on a root.\n");
			return(NAN);
        } */
        /* Calculate the updated point */
	x2 = x0 - fx0*((x0-x1)/(fx0 - fx1)); 
        if(fabs(x2-x1) < atol) 
        {
           printf("Found root: %f using secant\n", x2);
            return x2;
        }
        if(verb)
        {
            fprintf(stdout, "iter:%d	x0:%f	x2:%f	err:%f\n",
                    i, x0, x1, fabs(x2 - x0));
        }
        x1 = x0;
        x0 = x2; 
        i++;
    }
    fprintf(stdout, "Secant could not find a root with %d iterations\n", Nmax);
    return(NAN);
}

