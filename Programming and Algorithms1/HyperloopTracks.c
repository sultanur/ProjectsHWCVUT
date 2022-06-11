#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */
/*
The task is to implement a function (not a whole program, just a function) that plans hyperloop tracks. The function will be given the lengths of the available track segments and the length of the desired track. Based on these parameters, the function computes whether the track can be constructed, or not.

The hyperloop track is composed of individual segments of certain lengths. We assume there are two manufacturers, each of them produces segments of one fixed length. Each pair of adjacent segments must be connected by exactly one bulkhead; the whole track must start and end with a bulkhead. All bulkheads have the same length. The segments and bulkheads must be used in their original length, i.e., they cannot be cut or extended. The function is given the lengths of the segments, bulkheads, and the length of the track. Based on the parameters, the function decides whether there is a valid combination of segments and bulkheads that gives the exact length of the desired track. If the track can be constructed, the function counts how many different variants there exists.

Valid combinations of bulkheads and segments are:

bulkhead
bulkhead segment bulkhead
bulkhead segment bulkhead segment bulkhead
bulkhead segment bulkhead segment bulkhead segment bulkhead
bulkhead segment bulkhead segment bulkhead segment bulkhead segment bulkhead
...

The required interface is:

unsigned long long int  hyperloop                          ( unsigned long long int len, 
                                                             unsigned int s1, 
                                                             unsigned int s2, 
                                                             unsigned int bulkhead, 
                                                             unsigned int * c1, 
                                                             unsigned int * c2 );

len
    an input parameter - the length of the track being constructed,
s1, s2
    input parameters - the lengths of the segments produced by the first/second manufacturer. Either one or both parameter may be zero, meaning the segments from the respective manufacturer are unavailable and cannot be used (i.e., only the segments from the other manufacturer may be used),
bulkhead
    an input parameter - the length of the bulkhead. The parameter may be zero, meaning the bulkheads do not add to the overall length of the track,
c1, c2
    output parameters - the required number of segments from the first/second manufacturer. The function sets the parameters to any valid combination of segments that forms a valid solution. If the function cannot find any solution, it must not modify the parameters,
return value

    is either zero or the number of different solutions found. If the function does not succeed (i.e., no valid combination of segments and bulkheads results in the desired track length), the return value must be 0. Otherwise, if some solutions do exist, the function returns the number of different solutions that lead to the desired track length. The output parameters c1 and c2 must be set to some valid solution.

    Two solutions are considered identical if the required number of segments is the same for each segment length. Conversely, two solutions are considered different if they differ in the number of segments in at least one length. In other words:

        the order of segments in the track is irrelevant. For example:

               len = 20
               s1 = 5
               s2 = 10
               bulkhead = 0
             

        provides combinations:

               [bulkhead] [segment 5] [bulkhead] [segment 5] [bulkhead] [segment 5] [bulkhead] [segment 5] [bulkhead]
               
               [bulkhead] [segment 5] [bulkhead] [segment 5] [bulkhead] [segment 10] [bulkhead]
               [bulkhead] [segment 5] [bulkhead] [segment 10] [bulkhead] [segment 5] [bulkhead]
               [bulkhead] [segment 10] [bulkhead] [segment 5] [bulkhead] [segment 5] [bulkhead]
               
               [bulkhead] [segment 10] [bulkhead] [segment 10] [bulkhead]
             

        Of those, the middle three combinations are equivalent, all three require two segments of length 5 and one segment of length 10. Thus, the return value is 3 for this input:

               4 * s1 + 0 * s2 + 5 * bulkhead = 20
               2 * s1 + 1 * s2 + 4 * bulkhead = 20
               0 * s1 + 2 * s2 + 3 * bulkhead = 20
               
               hyperloop ( 20, 5, 10, 0, &c1, &c2 ) == 3
             

        if both manufacturers produce segments of the same length, then the segments are indistinguishable. For example:

               len = 40
               s1 = 10
               s2 = 10
               bulkhead = 0
             

        may result in five combinations:

               4 * s1 + 0 * s2 + 5 * bulkhead = 40
               3 * s1 + 1 * s2 + 5 * bulkhead = 40
               2 * s1 + 2 * s2 + 5 * bulkhead = 40
               1 * s1 + 3 * s2 + 5 * bulkhead = 40
               0 * s1 + 4 * s2 + 5 * bulkhead = 40
             

        However, these 5 combinations are considered equivalent, all of them require 4 segments of length 10:

               hyperloop ( 40, 10, 10, 0, &c1, &c2 ) == 1
             

Submit a source file with the implementation of hyperloop. Further, the source file must include your auxiliary functions which are called from the required function. The hyperloop function will be called from the testing environment, thus, it is important to adhere to the required interface. Use the attached sample code as a basis for your development, complete the required function and add your required auxiliary functions. There is an example main with some test in the attached code. These values will be used in the basic test. Please note the header files as well as main is nested in a conditional compile block (#ifdef/#endif). Please keep these conditional compile block in place. They are present to simplify the development. When compiling on your computer, the headers and main will be present as usual. On the other hand, the header and main will "disappear" when compiled by Progtest. Thus, your testing main will not interfere with the testing environment's main.

Your function will be executed in a limited environment. There are limits on both time and memory. The exact limits are shown in the test log of the reference. A reasonable implementation of the naive algorithm shall pass both limits without any problems. There is a bonus test, the bonus test requires an efficient algorithm to pass the time limit.
Advice:

    Download the attached sample code and use it as a base for your development.
    The main function in your program may be modified (e.g. new tests may be included). The conditional compile block must remain, however.
    There is assert macro used in the example main function. If the value passed to assert is nonzero (true), the macro does nothing. On the other hand, if the parameter is zero, the macro stops the execution and reports line, where the test did not match (and shall be fixed). Thus, the program ends silently when your implementation passes the tests correctly.
    The total track length and the resulting number of different solutions may exceed the range of the int data type. Therefore, the interface uses unsigned long long int data type instead. Functions printf and scanf use %llu conversion to display/read values of this data type.
    Do not try to generate all possible permutations and subsequently de-duplicate them. Generate only the unique solutions. Arrays are not required to solve the problem. Indeed, the array would add unnecessary complexity (it would have to be dynamically allocated) and the de-duplication would be too time expensive.
    The unsigned long long int data type is an extension of the C90/C++03 standard; the data type is included in the newer standards. If the compiler uses the old standard, it displays warnings. Progtest compiler is configured to suppress this warning, the compilation includes -Wno-long-long flag.

*/



int gcdExtended(unsigned long long  int a, unsigned long long  int b, long long int *x, long long int *y) 
{ 
	
	if (a == 0) 
	{ 
		*x = 0; 
		*y = 1; 
		return b; 
	} 

	long long int x1, y1; // To store results of recursive call 
	long long  int gcd = gcdExtended(b%a, a, &x1, &y1); 

	*x = y1 - (b/a) * x1; 
	*y = x1; 
   
	return gcd; 
 
} 
unsigned long long int hyperloop                           ( unsigned long long int length,
                                                             unsigned int        s1,
                                                             unsigned int        s2,
                                                             unsigned int        bulkhead,
                                                             unsigned int      * c1,
                                                             unsigned int      * c2 )
{
  
   unsigned int segment1, segment2;  
   long long int  x, y,  req_num, numSegment1;
   long long int length_bulk;
    int tmp= 0;

   segment1 = bulkhead + s1;
   segment2 = bulkhead + s2;
   length_bulk = length - bulkhead;
    if (bulkhead == length )
   {
     *c1 = 0;
     *c2 = 0;
         return 1;
   }
   if ((s1 == 0 && s2 == 0 )
      || (length < bulkhead) 
      || (segment1 > length && segment2 > length)) {
      return 0;
     if (s1 > length || s2 > length || bulkhead > length)
                  return 0;
   }
   if (segment1 == 0 && segment2 != 0)  {
      if (length_bulk % segment2 != 0) {
          return 0;
      }
      *c1 = 0;
      *c2 = length_bulk / segment2;
            return 1;
}
   if  (segment1 != 0 && segment2 == 0) {
    if (length_bulk % segment1 != 0) {
          return 0;
   } 
      *c2 = 0;
      *c1 = length_bulk / segment1;
            return 1;
}
      if (s1 != 0 && s2 == 0)
       { segment2 = segment1;
         segment1 = bulkhead;
          tmp++; }

	int gcd = gcdExtended(segment1, segment2, &x, &y); 
                req_num = length_bulk / gcd;
   if ((length_bulk % gcd) !=0) 
     return 0;
    numSegment1 = x * req_num;
             
              numSegment1 %= segment2/gcd;   
              if (numSegment1 < 0) {
              numSegment1 = (segment2 / gcd)  - ( - numSegment1 % (segment2 / gcd)); }  
       
    if (tmp == 1) {
         * c1 = (length_bulk - segment1 * numSegment1) / segment2; 
         * c2 = numSegment1; }

   else {                          
      * c1 = numSegment1;
      * c2 = (length_bulk - segment1 * numSegment1) / segment2;
       }
       return ((length_bulk / segment1) - (*c1)) / segment2 + 1;
 
      
}

#ifndef __PROGTEST__
int main (  )
{
  unsigned int c1, c2;
  assert ( hyperloop ( 100, 4, 7, 0, &c1, &c2 ) == 4
           && 4 * c1 + 7 * c2 + 0 * (c1 + c2 + 1) == 100 );
   //unsigned long long res = hyperloop ( 123456, 8, 3, 3, &c1, &c2 );
  // printf ("hyperloop ( 123456, 8, 3, 3, &c1, &c2 ) is %llu"
//"\n8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) is %u\n"
  //          , res
    //        , 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1));
  assert ( hyperloop ( 123456, 8, 3, 3, &c1, &c2 ) == 1871
           && 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) == 123456 );

  assert ( hyperloop ( 127, 12, 8, 0, &c1, &c2 ) == 0 );
  assert ( hyperloop ( 127, 12, 4, 3, &c1, &c2 ) == 1
           && 12 * c1 + 4 * c2 + 3 * (c1 + c2 + 1) == 127 );
  assert ( hyperloop ( 100, 35, 0, 10, &c1, &c2 ) == 1
           && c2 == 0
           && 35 * c1 + 10 * (c1 + 1) == 100 );
  assert ( hyperloop ( 110, 30, 30, 5, &c1, &c2 ) == 1
           && 30 * c1 + 30 * c2 + 5 * (c1 + c2 + 1) == 110 );
  c1 = 2;
  c2 = 7;
  assert ( hyperloop ( 110, 30, 30, 0, &c1, &c2 ) == 0 && c1 == 2 && c2 == 7 );
  c1 = 4;
  c2 = 8;
  assert ( hyperloop ( 9, 1, 2, 10, &c1, &c2 ) == 0 && c1 == 4 && c2 == 8 );
  assert (hyperloop ( 935000, 1, 2, 0, &c1, &c2 ) == 467501);
  assert (hyperloop ( 683000, 1, 2, 0, &c1, &c2 ) == 341501);
  assert (hyperloop ( 920757507, 199, 148, 3, &c1, &c2 ) == 30187);
  assert (hyperloop ( 945806623, 176, 33, 21, &c1, &c2 ) == 88909);
  assert (hyperloop ( 834, 0, 834, 0, &c1, &c2 ) == 1);
  assert (hyperloop ( 817, 0, 5719, 0, &c1, &c2 ) == 0);
  return 0;
}
#endif /* __PROGTEST__ */
