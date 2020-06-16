/*---------------------------------------------------------------------------
  QN code testing and verification
  student copy
---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>

#define LOOP_DELAY (1<<27)

// QN math functions which pass the number of bits "n" 
#define Qn_MULTIPLY(A,B,n) ((A>>(n/2))*(B >>(n-(n/2))))
#define Qn_DIVIDE(A,B,n) ((int) (((long int)(A)<<n)/(B) ))

// QN math and printing functions
void  printBinary(unsigned num, short N);
int  floatToFixed(double x, int n);
float fixedToFloat(int x, int n); 

/*---------------------------------------------------------------------------
  QN testing framework 
---------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
   // QN testing variables, add more as necessary
   double fnum1, fnum2, fnum3, fnum4, fnum5, fnum6, fnum7, fnum8;
   int  qnum1, qnval, qnum2, qnval2, qnum3, qnval3, qnum4, qnval4;
   
   //------------------------------------------------------------------------
   // Print data on sizes  
   //------------------------------------------------------------------------
   printf("Integers are %ld bits long\n", 8*sizeof(int));

   //------------------------------------------------------------------------
   // Prove floating point has limits 
   //------------------------------------------------------------------------
   printf("Proving floating point has limits by adding Epsilon\n");
   printf("10.0 plus Epsilon is: '%2.6g'\n", (10.0 + DBL_EPSILON));
   printf("Epsilon value '%2.6g' didn't add\n",  DBL_EPSILON);
   
   //------------------------------------------------------------------------
   // Examine the conversion utilities
   //------------------------------------------------------------------------
   fnum1 = 0.0;
   qnval = 0;
   printf("\nConversion test\n");
   qnum1 = floatToFixed(fnum1, qnval);
   fnum2 = fixedToFloat(qnum1, qnval);
   printf("Started with %f converted to qn%d = %d decimal then back to %f\n", fnum1, qnval, qnum1, fnum2);
   printBinary(qnum1, qnval);

   fnum3 = 12.25;
   qnval2 = 3;
   qnum2 = floatToFixed(fnum3, qnval2);
   fnum4 = fixedToFloat(qnum2, qnval2);
   printf("Started with %f converted to qn%d = %d decimal then back to %f\n", fnum3, qnval2, qnum2, fnum4);
   printBinary(qnum2, 8);
   
   fnum5 = 12.0625;
   qnval3 = 3;
   qnum3 = floatToFixed(fnum5, qnval3);
   fnum6 = fixedToFloat(qnum3, qnval3);
   printf("Started with %f converted to qn%d = %d decimal then back to %f\n", fnum5, qnval3, qnum3, fnum6);
   printBinary(qnum3, 8);

   fnum7 = 12.0625;
   qnval4 = 4;
   qnum4 = floatToFixed(fnum7, qnval4);
   fnum8 = fixedToFloat(qnum4, qnval4);
   printf("Started with %f converted to qn%d = %d decimal then back to %f\n", fnum7, qnval4, qnum4, fnum8);
   printBinary(qnum4, 9);
   return(0);
}


/*---------------------------------------------------------------------------
  This prints a number in character binary bracketed by [..]
  
  Where: unsigned num - number to print
         short N      - number of bits to print
         
  Returns: nothing
  Error handling: none
----------------------------------------------------------------------------*/
void printBinary(unsigned num, short N) { 
   unsigned i; 
   printf("QN %d decimal in binary is\t[", num);
   
   for (i = 1 << (N-1); i > 0; i = i >> 1) {
      (num & i)? printf("1"): printf("0");
    }        
   printf("]\n");
   return;
} 


/*---------------------------------------------------------------------------
  This convert from Float to FP(Qn) 
  
  Where: double x  - number to convert
         int qnval - number of bits to use
         
  Returns: int    - QN encoded number
  Error handling: none
----------------------------------------------------------------------------*/
int floatToFixed(double x, int qnval) { 
   return( x * (double)(1 << qnval) );            
} 

/*---------------------------------------------------------------------------
  This converts from FP(Qn) to Float
  
  Where: int x     - number to convert
         int qnval - number of bits to use
         
  Returns: float   - converted number
  Error handling: none
----------------------------------------------------------------------------*/
float fixedToFloat(int x, int qnval) { 
   return((double)x / (double) (1 << qnval));
}

