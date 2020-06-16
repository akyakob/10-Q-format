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
   double fnum1, fnum2, fnum3, fproduct, fnum4, fproduct2, fproduct3, fnum5, fnum6;
   int  qnum1, qnum2, qnum3, qnum4, qnval, qnval2, qproduct, qnum5, qnum6, qnum7;
   clock_t  time1, time2;
   unsigned i;
   
   
   //------------------------------------------------------------------------
   // Examine the division utilities
   //------------------------------------------------------------------------   
   printf("\nDivision test\n");
   fnum1 = -0.0625;
   qnval = 18;
   qnum1 = floatToFixed(fnum1, qnval);
   qnum2 = floatToFixed(fnum1, qnval);
   printf("fnum1  qnum1(dec) qnum2(dec) qnum1(float) qnum2(float)\n");
   while(qnum1!=0 | qnum2!=0) {
      fnum1 = fnum1/2.0;
      qnum1 = qnum1/2;
      qnum2 = Qn_DIVIDE(qnum2, floatToFixed(2.0, qnval), qnval);
   printf("%f  %d  %d  %f  %f\n", fnum1, qnum1, qnum2, fixedToFloat(qnum1, qnval), fixedToFloat(qnum2,qnval));
   }
   
   printf("\nDivision test 2\n");
   fnum1 = -0.0625;
   qnval = 18;
   qnum1 = floatToFixed(fnum1, qnval);
   qnum2 = floatToFixed(fnum1, qnval);
   printf("fnum1  qnum1(dec) qnum2(dec) qnum1(float) qnum2(float)\n");
   while(qnum1!=0 | qnum2!=0) {
      fnum1 = fabs(fnum1/2.0);
      qnum1 = abs(qnum1/2);
      qnum2 = abs(Qn_DIVIDE(qnum2, floatToFixed(2.0, qnval), qnval));
   printf("%f  %d  %d  %f  %f\n", fnum1, qnum1, qnum2, fixedToFloat(qnum1, qnval), fixedToFloat(qnum2,qnval));
   }
   //------------------------------------------------------------------------
   // Examine the multiplication utilities
   //------------------------------------------------------------------------   
   printf("\nMultiplication test\n");
   fnum2 = 64.125;
   fnum3 = 0.755;
   qnval2 = 18;
   qnum3 = floatToFixed(fnum2, qnval2);
   qnum4 = floatToFixed(fnum3, qnval2);
   qproduct = Qn_MULTIPLY(qnum3, qnum4, qnval2);
   fproduct = fixedToFloat(qproduct, qnval2);
   printf("Product= %f, qn%d product= %d dec, converted back %f float", fproduct, qnval, qproduct, fproduct);
   //------------------------------------------------------------------------
   // Implement floating point scientific equations two different ways
   // using normal fractions and using decimal fractions
   //------------------------------------------------------------------------
   printf("\nComplex calculations test\n");
   fnum4 = 1.0;
   fproduct2 = fnum4*fnum4*fnum4 - -0.0001*(fnum4*fnum4) - 676*fnum4 + 0.0676;
   fproduct3 = fnum4*fnum4*fnum4 - (fnum4*fnum4)/100000 - 676*fnum4 + 169/2500;
   //---------------------------------------------------------------------
   // Implement QN scientific equations: x**3-.0001x**2-676X+.0676
   //------------------------------------------------------------------------   
   qnum5 = floatToFixed(fnum4, qnval2); //1.0 as Qn18
   //qnum6 = qnum5*qnum5*qnum5 - 0.0001*(qnum5*qnum5) - 676*qnum5 + 0.0676;
   int q0001, q676, q0676, qprod1, qprod2, qprod3, qprod4, qfinal;
      q0001 = floatToFixed(0.0001, qnval2);
      q676 = floatToFixed(676.0, qnval2);
      q0676 = floatToFixed(0.0676, qnval2);
   qprod1 = Qn_MULTIPLY(qnum5, qnum5, qnval2); //qnum5**2
   qprod2 = Qn_MULTIPLY(qnum5, qprod1, qnval2); //qnum5***3
   qprod3 = Qn_MULTIPLY(q0001, qprod1, qnval2); //0.0001*qnum5**2
   qprod4 = Qn_MULTIPLY(q676, qnum5, qnval2); 
   qfinal = qprod2 - qprod3 - qprod4 + q0676;
   // print all 3 answers
   printf("floating-point product: %f\n", fproduct2);
   printf("fractional product: %f\n", fproduct3);
   printf("Qn18 product: %f\n", fixedToFloat(qfinal, qnval2));
   //------------------------------------------------------------------------
   // Examine the performance 
   //------------------------------------------------------------------------
   printf("\nPerformance test\n");
   
   fnum5 = 3.1415;
   fnum6 = -674.9325;
   qnum6 = floatToFixed(fnum5, qnval2);
   qnum7 = floatToFixed(fnum6, qnval2);
   // Floating point addition
   time1 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      fnum5 + fnum6;
   }
   time1 = clock()-time1;
   
   // QN addition
   time2 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      // Insert your addition here
      qnum6 + qnum7;
   }
   time2 = clock()-time2;
   
   // Print out the clicks and who was faster
   printf("Float point addition: %jd\n QN addition: %jd\n", (intmax_t)time1, (intmax_t)time2);
   
   // Floating multiplication
   time1 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
      fnum5 * fnum6;
}
   time1 = clock()-time1;
   
   // QN multiplication
   time2 = clock();
   for(i = 0; i < LOOP_DELAY; i++) {
     Qn_MULTIPLY(qnum6, qnum7, qnval2);
   }
   time2 = clock()-time2;
   
   // Print out the clicks and who was faster
   printf("Float point multiplication: %d\n QN multiplication: %d\n", time1, time2);

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
   printf("\t[");
   
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

