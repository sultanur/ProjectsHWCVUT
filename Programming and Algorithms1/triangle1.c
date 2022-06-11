#include <stdio.h>
#include <math.h>
/*
Advice:

    The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
    Do not forget the newline (\n) after the last output line.
    Use double data type to represent the values. Do not use float, the precision of float is not always sufficient.
    The program can be developed without additional functions (i.e., in one big main). However, if divided into functions, the program is readable and easier to debug.
    All numeric values in the input fit into the range of double data type. The reference uses double and int data types to represent numbers.
    Please strictly adhere to the format of the output. The output must exactly match the output of the reference program. The comparison is completed by a machine, meaning an exact match is required. If your program provides output different from the reference, the program is considered malfunctioning. Be very careful since the comparison is sensitive even to whitespace characters (spaces, newlines, tabulators). Please note that all output lines are followed by a newline character (\n). The new line character must be present after the last line of the output and after the error messages. Download the enclosed archive. The archive contains a set of testing inputs and the expected outputs. Read Progtest FAQ to learn how to use input/output redirection and how to simplify testing of your programs.

    Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. However, neither time nor memory limit could cause a problem in this simple program. Next, the testing environment prohibits the use of functions which are considered "dangerous" (functions to execute other processes, functions to access the network, ... ). If your program uses such functions, the testing environment refuses to execute the program. 

    This will not work properly in the testing environment - it is prohibited to execute other programs. (Even if the function were allowed, this would not work properly. The program would infinitely wait for a key to be pressed, however, no one will press any key in the automated testing environment. Thus, the program would be terminated on exceeded time limit.) If you want to keep the pause for your debugging and you want the program to be accepted by the Progtest, use the following trick:
*/


int main () {


double A1_x, A1_y, B1_x, B1_y, C1_x, C1_y, A2_x, A2_y, B2_x, B2_y, C2_x, C2_y; 
double AB1_length, BC1_length, AC1_length, AB2_length, BC2_length, AC2_length, Circumf_1, Circumf_2;



   printf ("Triangle #1:\nVertex A:\n");
   if (scanf (" %lf %lf", &A1_x, &A1_y)  != 2) { 
      printf ("Invalid input.\n");
             return 0;
      } 

   printf ("Vertex B:\n");
   if (scanf (" %lf %lf", &B1_x, &B1_y)  !=2) {
       printf ("Invalid input.\n");
             return 0;
      }

   printf ("Vertex C:\n");
   if (scanf (" %lf %lf", &C1_x, &C1_y)  != 2) {
      printf ("Invalid input.\n");
             return 0;
      }

  AB1_length = sqrt((A1_x - B1_x)*(A1_x - B1_x) + (A1_y - B1_y)*(A1_y - B1_y));
  BC1_length = sqrt((B1_x - C1_x)*(B1_x - C1_x) + (B1_y - C1_y)*(B1_y - C1_y));
  AC1_length = sqrt((A1_x - C1_x)*(A1_x - C1_x) + (A1_y - C1_y)*(A1_y - C1_y));

double EPS =0;

  if ( AB1_length < BC1_length) {
      if (AB1_length < AC1_length) {
           EPS = AB1_length;
   } else {
            EPS = AC1_length;
   }  
   } else {
      if (BC1_length < AC1_length) {
             EPS = BC1_length;
      } else {
          EPS = AC1_length;
      }
     }
    
   if (((BC1_length + AC1_length) - AB1_length)*1000000000000. < EPS || 
       ((AB1_length + AC1_length) - BC1_length) *1000000000000. < EPS || 
       ((AB1_length + BC1_length) - AC1_length) *1000000000000. < EPS) {
            printf ("The points do not form a triangle.\n");
                     return 0;
      }

   printf ("Triangle #2:\nVertex A:\n");
   if (scanf ("%lf%lf", &A2_x, &A2_y)  != 2) {
      printf ("Invalid input.\n");
             return 0;
      }

   printf ("Vertex B:\n");
   if (scanf ("%lf%lf", &B2_x, &B2_y)  !=2)  {
      printf ("Invalid input.\n");
             return 0;
   }

   printf ("Vertex C:\n");
   if (scanf ("%lf%lf", &C2_x, &C2_y) != 2) {
      printf ("Invalid input.\n");
             return 0;
      }

 

  AB2_length = sqrt((A2_x - B2_x)*(A2_x - B2_x) + (A2_y - B2_y)*(A2_y - B2_y));
  BC2_length = sqrt((B2_x - C2_x)*(B2_x - C2_x) + (B2_y - C2_y)*(B2_y - C2_y));
  AC2_length = sqrt((A2_x - C2_x)*(A2_x - C2_x) + (A2_y - C2_y)*(A2_y - C2_y));



  if ( AB2_length < BC2_length) {
      if (AB2_length < AC2_length) {
           EPS = AB2_length;
   } else {
            EPS = AC2_length;
   }  
   } else {
      if (BC2_length < AC2_length) {
             EPS = BC2_length;
      } else {
          EPS = AC2_length;
      }
     }


   if (((BC2_length + AC2_length) - AB2_length) *1000000000000. < EPS || 
       ((AB2_length + AC2_length) - BC2_length) *1000000000000. < EPS || 
       ((AB2_length + BC2_length) - AC2_length) *1000000000000. < EPS) {
            printf ("The points do not form a triangle.\n");
            return 0;
      }

    Circumf_1 = (AB1_length + BC1_length + AC1_length);
    Circumf_2 = (AB2_length + BC2_length + AC2_length);
  
 
     if (((fabs(AB1_length - AB2_length)) *1000000000000.) < EPS || ((fabs(AB1_length - BC2_length)) *1000000000000.) < EPS ||      
         ((fabs(AB1_length - AC2_length)) *1000000000000.) < EPS && ((fabs(BC1_length - AB2_length)) *1000000000000.) < EPS || 
         ((fabs(BC1_length - BC2_length))*1000000000000.) < EPS  || ((fabs(BC1_length - AC2_length)) *1000000000000.) < EPS  && 
         ((fabs(AC1_length - AB2_length)) *1000000000000.) < EPS || ((fabs(AC1_length - BC2_length) *1000000000000.) < EPS   || 
         ((fabs(AC1_length - AC2_length) *1000000000000.) < EPS))) {
              
                         printf ("The triangles are identical.\n");
      } else if ((fabs(Circumf_1 - Circumf_2)*1000000000000.) < EPS) { 
         printf ("The triangles are not identical, however, they have the same circumference.\n");
      } else if (Circumf_1 < Circumf_2) {
          printf ("Triangle #2 has a longer circumference.\n");
      } else {
          printf ("Triangle #1 has a longer circumference.\n");
     
      }


   return 0;

}









   
