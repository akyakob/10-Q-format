/**************************************************************************
  intTest.c - for students
  This program demonstrates the speed advantages of integer versus floating
  point math.
 12/28/2015 - R. Repka  Initial version
 10/12/2016 - R. Repka  Switched to PRINT_RTIMER() macro
 03/25/2018 - R. Repka  Switched to timing macros 
 11/18/2019 - R. Repka  Polynomial comment error 
**************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ClassErrors.h"
#include "rootfinding.h"
#include "Timers.h"
// NEVER INCLUDE .C FILES 
/****************************************************************************
  Use this to define the number of iterations in your performance measurements
  ----------- You will need to adjust this number  --------
****************************************************************************/
#define ITERATIONS   (300000)

/* Optional verbose flag, compile with -DVERBOSE or not */
#ifdef VERBOSE
   #undef VERBOSE 
   #define VERBOSE (1)
#else 
   #define VERBOSE (0)
#endif

/****************************************************************************
  Remember to set the QN value in rootfinding.h
****************************************************************************/

/************************************************************************
   Simple code to test Qn performance vs floating point  
************************************************************************/
int main(int argc, char* argv[])
    {
    double Result;          /* The result from floating point calculation   */
    long  iResult;          /* The result from floating point calculation   */
    /* The bisection guesses and tolerance value                        */
    double a = -25.0;
    double b = 25.0;
    double tol= 0.000001;
    long qnuma, qnumb, qtol;
qnuma = FLOAT_TO_FIX(a);   
qnumb = FLOAT_TO_FIX(b);   
qtol = FLOAT_TO_FIX(tol);   
    /* You many need to modify the timing code for your macro implementation! */
    DECLARE_TIMER(timer);
    DECLARE_REPEAT_VAR(tloop)

    /************************************************************************
     Run the Qn format test 
    ************************************************************************/
    /* You many need to modify the timing code for your macro implementation! */
    START_TIMER(timer);
    BEGIN_REPEAT_TIMING(ITERATIONS,tloop)
         iResult = ibisection(&iPoly, qnuma, qnumb, qtol, VERBOSE);
    END_REPEAT_TIMING
    STOP_TIMER(timer);

    if(iNAN == iResult)
        {
        fprintf(stderr, "Qn %d ibisection couldn't find a root. \n", QN);
        exit(99);
        }
    else
        {
        fprintf(stderr, "Found the root %f using Qn %d ibisection.\n",
                        FIX_TO_FLOAT(iResult ), QN);
        }      
    PRINT_TIMER(timer);
    PRINT_RTIMER(timer, ITERATIONS); 

    /************************************************************************
     Run the floating point format test 
    ************************************************************************/
    RESET_TIMER(timer);
    START_TIMER(timer);
    BEGIN_REPEAT_TIMING(ITERATIONS,tloop)
        Result = bisection(&rPoly, a, b, tol, VERBOSE);
    END_REPEAT_TIMING
    STOP_TIMER(timer);

    if(NAN == Result)
        {
        fprintf(stderr, "Float bisection couldn't find a root. \n");
        exit(99);
        }
    else
        {
        fprintf(stderr, "Found the root %f using float bisection.\n",
                        Result);
        }

    PRINT_TIMER(timer);
    PRINT_RTIMER(timer, ITERATIONS);
    
    /* Display the percentage error */
    Result = ((fabs(Result-FIX_TO_FLOAT(iResult)))/Result)*100.0;
    fprintf(stderr, "Qn %d error= %f\n", QN, Result);
    return 0;
    } /* End main */   
    
    

/******************************************************************************
 Purpose: Finds a root of scalar, non-linear function f using the integer 
 bisection  method. a and b make up the initial bracket to start bisecting from.
 Only implement this after you have the floating point function implemented
 
 Where: ifunc1arg f - INTEGER function whose root is to be determined
                      must take a single argument of type long and return
        long a      - initial Qn root bracket guess
        long b      - initial Qn root bracket guess
        long atol   - absolute Qn error termination tolerance,
        int verb    - verbose flag, 1 = TRUE, 0 = FALSE
        
Returns: long - the root refined to the desired tolerance or NAN
Errors:  prints a message and returns with NAN                 
******************************************************************************/
long ibisection(ifunc1arg f, long a, long b, long atol, int verb)
{
 //a b and atol already passed in as qn values
    long qc; //midpoint
    long qfc; //value at midpoint
    int i=0; //itertor
    long qaplusb, q2; 
    q2 = FLOAT_TO_FIX(2.0);
    /* change to qn vals if using
    //need or not?
    if((fabs(a-b) < atol) || SIGN(f(a))==SIGN(f(b))) {
      fprintf(stdout, "a and b do not center a root\n");
      return(NAN); 
    }
    */

    //Limit number of attempts
    while(i < BI_LIMIT) {
       //calculate midpoint, evaluate it
       qaplusb = a + b;
       qc = Qn_DIVIDE(qaplusb,q2); //(a+b)/2.0
       qfc = f(qc);
              //did we find a root? - check the function
       if(abs(qfc) <= atol) { 
    //       printf("Found root: %f using ibisection\n", FIX_TO_FLOAT(qc));
	   return qc;
       }
              //did we find a root? - check the range
       if(abs(Qn_DIVIDE(a-b,q2)) <= atol) { 
   //	   printf("Found root: %f using ibisection\n",FIX_TO_FLOAT(qc));
	   return(qc);
       }
       if (verb) {
	   fprintf(stdout, "iter:%d	a:%f	b:%f	x:%f	err:%f\n", 
                         i, FIX_TO_FLOAT(a), FIX_TO_FLOAT(b), FIX_TO_FLOAT(qc), FIX_TO_FLOAT(b-qc));
       }
       if(SIGN(f(a)) == SIGN(qfc)) { //pick the next bracket
           a = qc;
       }
       else {
           b = qc;
       }
     i++;
    }
    fprintf(stdout, "ibisection could not find a root with %d iterations\n", BI_LIMIT);
    return(NAN);
    
}    
    
/*---------------------------------------------------------------------------
  This function implements the real polynomial equation to be solved.  
  
  Where:   double x - the value to evaluate
  Returns: double - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
double rPoly(double x){
    //x**3-.0001x**2-676X+.0676    
    return(x*(x*(x-.0001)-676.0)+.0676);
}


/*---------------------------------------------------------------------------
  This function implements the integer polynomial equation to be solved.  
  
  Where:    long x - the value to evaluate
  Returns: long - the value of the function at the point
  Errors:  none
---------------------------------------------------------------------------*/
long iPoly(long x){
    //x**3-.0001x**2-676X+.0676    
    //convert everything to Qn to be able to multiply
 /*  long q0001, q676, q0676, qprod1, qprod2, qprod3, qprod4, qfinal;
      q0001 = FLOAT_TO_FIX(0.0001);
      q676 = FLOAT_TO_FIX(676);
      q0676 = FLOAT_TO_FIX(0.0676);
   qprod1 = MUL_FIX(x, x); //qnum5**2
   qprod2 = MUL_FIX(x, qprod1); //qnum5***3
   qprod3 = MUL_FIX(q0001, qprod1); //0.0001*qnum5**2
   qprod4 = MUL_FIX(q676, x); 
   qfinal = qprod2 - qprod3 - qprod4 + q0676;
 */  //return(qfinal);
   return MUL_FIX(x,(MUL_FIX(x,(x-FLOAT_TO_FIX(.0001)))-FLOAT_TO_FIX(676.0)))+FLOAT_TO_FIX(0.0676);
}
