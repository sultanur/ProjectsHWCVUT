#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/* The task is to develop a program that compares two given triangles in a 2D plane. The problem is an extension of the simple variant. This version accepts input triangles entered either by their vertices or by the lengths of their sides. Starting with the simple problem is highly recommended.

There are given two triangles in a 2D plane. Each triangle is defined either by its vertices or by the lengths of its sides:

    triangle defined by its vertices is entered in the form of three coordinates. The three coordinates are enclosed in curly braces; individual coordinates are separated by commas. A coordinate consists of two decimal numbers separated by a semicolon, the two numbers are enclosed in square braces. An example:

    { [ 1.5; 2 ], [3;4.2], [ 0.5 ; 0.6 ] }

    triangle defined by its sides is entered in the form of three decimal numbers. The three numbers are enclosed in curly braces and separated by commas. An example:

    {2.1, 3, 3.4}

Your program reads the triangles from the standard input. Next, the program decides one of the 4 cases:

    the input does not form a triangle (the three vertices defining the triangle are on a common line, or the sides do not obey triangle inequality),
    the triangles are identical,
    the triangles are not identical while their circumference is the same, or
    the triangles are entirely different.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

    the coordinates or sides are invalid (are not valid decimals),
    some coordinate(s) or sides are missing,
    there are missing some separators (braces, commas, semicolons).

Sample program runs:

Triangle #1:
{[0;0],[5;0],[2.5;3]}
Triangle #2:
 { [ 4 ; -1 ] , [ 7 ; 1.5 ] , [ 4 ; 4 ] } 
The triangles are identical.

Triangle #1:
{
[
0
;
15
]
,	[	112	;	0	]	,[112;15]}
Triangle #2:
{96.0,40.0,104.0}
The triangles are not identical, however, they have the same circumference.

Triangle #1:
 { 10 , 15 , 10 } 
Triangle #2:
{12,8,17}
Triangle #2 has a longer circumference.

Triangle #1:
{[0;14.04],[11.2;0],[0;0]}
Triangle #2:
{[20.16;0],[0;2.7],[20.16;2.7]}
The triangles are not identical, however, they have the same circumference.

Triangle #1:
{[0.00;0.00],[0.24;0.70],[0.24;0.00]}
Triangle #2:
{0.65,0.78,0.25}
The triangles are not identical, however, they have the same circumference.

Triangle #1:
{51.09,49.49,4.94}
Triangle #2:
{37.92,50.11,17.49}
The triangles are not identical, however, they have the same circumference.

Triangle #1:
{[0;0],[10;0],[0;10]}
Triangle #2:
{[0;0],[10;10],[15;15]}
Invalid triangle.

Triangle #1:
{[10;0],[20;1],[25;1.5]}
Invalid triangle.

Triangle #1:
{1,2,3}
Invalid triangle.

Triangle #1:
{[0;0],[999.990;204.330],[899.991;183.897]}
Invalid triangle.

Triangle #1:
{1.923,59.240,61.163}
Invalid triangle.

Triangle #1:
{[1;2],[3;abcd],[7,9]}
Invalid input.

Advice:

    The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
    Do not forget the newline (\n) after the last output line.
    Use double data type to represent the values. Do not use float, the precision of float is not always sufficient.
    The program can be developed without additional functions (i.e., in one big main). However, if divided into functions, the program is readable and easier to debug.
    All numeric values in the input fit into the range of double data type. The reference uses double and int data types to represent numbers.
    The input may be processed using the scanf function.
    scanf conversions %c and %c (with an extra space before %c) are quite useful in this assignment. Learn the difference in the manual pages.
    Please strictly adhere to the format of the output. The output must exactly match the output of the reference program. The comparison is completed by a machine, meaning an exact match is required. If your program provides output different from the reference, the program is considered malfunctioning. Be very careful since the comparison is sensitive even to whitespace characters (spaces, newlines, tabulators). Please note that all output lines are followed by a newline character (\n). The new line character must be present after the last line of the output and after the error messages. Download the enclosed archive. The archive contains a set of testing inputs and the expected outputs. Read Progtest FAQ to learn how to use input/output redirection and how to simplify testing of your programs.

    Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. However, neither time nor memory limit could cause a problem in this simple program. Next, the testing environment prohibits the use of functions which are considered "dangerous" (functions to execute other processes, functions to access the network, ... ). If your program uses such functions, the testing environment refuses to execute the program. 

    This will not work properly in the testing environment - it is prohibited to execute other programs. (Even if the function were allowed, this would not work properly. The program would infinitely wait for a key to be pressed, however, no one will press any key in the automated testing environment. Thus, the program would be terminated on exceeded time limit.) 

*/

int main () {


double A1_x, A1_y, B1_x, B1_y, C1_x, C1_y, A2_x, A2_y, B2_x, B2_y, C2_x, C2_y; 
double AB1_length, BC1_length, AC1_length, AB2_length, BC2_length, AC2_length, Circumf_1, Circumf_2;

char ch1, ch2, ch3;
int scanreturn1, scanreturn2;

   printf ("Triangle #1:\n");
       
        

      if ((scanreturn1 = scanf (" %c [ %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }%c", 
                                     &ch1, &A1_x,  &A1_y, &B1_x,  &B1_y,  &C1_x, &C1_y, &ch2)) == 8) {
            if (ch1 != '{') {
      printf ("Invalid input.\n");  
            return 0;
        }
         
         AB1_length = sqrt((A1_x - B1_x)*(A1_x - B1_x) + (A1_y - B1_y)*(A1_y - B1_y));
         BC1_length = sqrt((B1_x - C1_x)*(B1_x - C1_x) + (B1_y - C1_y)*(B1_y - C1_y));
         AC1_length = sqrt((A1_x - C1_x)*(A1_x - C1_x) + (A1_y - C1_y)*(A1_y - C1_y));
    
          double L = ((AB1_length +  BC1_length + AC1_length)/2);
          double M = (sqrt(L*(L-AB1_length)*(L-BC1_length)*(L-AC1_length)));  
       
      if (((BC1_length + AC1_length) - AB1_length)<= 1e-12 || 
          ((AB1_length + AC1_length) - BC1_length)<= 1e-12 || 
          ((AB1_length + BC1_length) - AC1_length)<= 1e-12 || (M == 0)) {
                 printf ("Invalid triangle.\n");
                    return 0;
            }
        }
         else if ((scanreturn2 = scanf (" %lf , %lf , %lf }%c", &AB1_length,  &BC1_length,  &AC1_length, &ch3)) == 4) {
          
         if (((BC1_length + AC1_length) - AB1_length)<= 1e-12 || 
             ((AB1_length + AC1_length) - BC1_length)<= 1e-12 || 
             ((AB1_length + BC1_length) - AC1_length)<= 1e-12) {
                    printf ("Invalid triangle.\n");
                        return 0;
              } 
            } else {          printf ("Invalid input.\n"); 
                               return 0;
                    } 
                  
      
      printf ("Triangle #2:\n");
       
      if ((scanreturn1 = scanf (" %c [ %lf ; %lf ] , [ %lf ; %lf ] , [ %lf ; %lf ] }%c", 
                                     &ch1, &A2_x,  &A2_y, &B2_x,  &B2_y,  &C2_x, &C2_y, &ch2)) == 8) {
         
            if (ch1 != '{') {
      printf ("Invalid input.\n");  
            return 0;
        }

         AB2_length = sqrt((A2_x - B2_x)*(A2_x - B2_x) + (A2_y - B2_y)*(A2_y - B2_y));
         BC2_length = sqrt((B2_x - C2_x)*(B2_x - C2_x) + (B2_y - C2_y)*(B2_y - C2_y));
         AC2_length = sqrt((A2_x - C2_x)*(A2_x - C2_x) + (A2_y - C2_y)*(A2_y - C2_y));
    
        
         double L = (AB2_length +  BC2_length + AC2_length)/2;
         double M = (sqrt(L*(L-AB2_length)*(L-BC2_length)*(L-AC2_length)));  
      if (((BC2_length + AC2_length) - AB2_length) <= 1e-12 || 
          ((AB2_length + AC2_length) - BC2_length) <= 1e-12 || 
          ((AB2_length + BC2_length) - AC2_length) <= 1e-12 || (M == 0)) {
                 printf ("Invalid triangle.\n");
                    return 0;
     }
}
            else if ((scanreturn2 = scanf (" %lf , %lf , %lf }%c", &AB2_length,  &BC2_length,  &AC2_length, &ch3)) == 4) {
           
      if (((BC2_length + AC2_length) - AB2_length) <= 1e-12 || 
          ((AB2_length + AC2_length) - BC2_length) <= 1e-12 || 
          ((AB2_length + BC2_length) - AC2_length) <= 1e-12) {
                 printf ("Invalid triangle.\n");
                    return 0;
            }          
             
       } else  {                
                        printf ("Invalid input.\n");
                               return 0;
                    }  
     
    Circumf_1 = (fabs(AB1_length + BC1_length + AC1_length));
    Circumf_2 = (fabs(AB2_length + BC2_length + AC2_length));
  /*printf ("Circumf1 = %lf\n", Circumf_1 );
  printf ("Circumf2 = %lf\n", Circumf_2 );
  printf ("AB1 = %lf, BC1 = %lf, AC1 = %lf\n", AB1_length,  BC1_length,  AC1_length);
  printf ("AB2 = %lf, BC2 = %lf, AC2 = %lf\n", AB2_length,  BC2_length,  AC2_length);
  */

     if  (((fabs(AB1_length - AB2_length) <= 1e-12) || (fabs(AB1_length - BC2_length) <= 1e-12) ||
          (fabs(AB1_length - AC2_length) <= 1e-12)) && ((fabs(BC1_length - AB2_length) <= 1e-12) || 
          (fabs(BC1_length - BC2_length) <= 1e-12) || (fabs(BC1_length - AC2_length) <= 1e-12))  && 
          ((fabs(AC1_length - AB2_length) <= 1e-12) || (fabs(AC1_length - BC2_length) <= 1e-12) || 
          (fabs(AC1_length - AC2_length) <= 1e-12))) {
               printf ("The triangles are identical.\n");
      
      } else if (fabs(Circumf_1 - Circumf_2) <= 1e-12)  { 
         printf ("The triangles are not identical, however, they have the same circumference.\n");
      } else if (Circumf_1 < Circumf_2) {  
          printf ("Triangle #2 has a longer circumference.\n");
      } else {
          printf ("Triangle #1 has a longer circumference.\n");
     
      }


   return 0;

}









   
