#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000
/*
The task is to develop a program that plans the positions of billboards along a highway. This problem is an extension of the simpler task.

The task is to develop a program to solve the planning of billboards. There are certain places along the highway suitable to place the billboards (conversely, the billboards cannot be placed anywhere else). The suitable places are identified by their position from the beginning of the highway; the position is an integer. There is at most 1000000 such places.

We are about to use some of the places for our advertising. Our primary concern is to place exactly the given number of billboards. Secondly, the distance between a pair of adjacent billboards must be as high as possible. The program shall place the billboards and find the distance between the closest pair of billboards.

The input of the program is the list of suitable places. Each place is described by an integer; the integers are enclosed in curly braces and separated by commas. Following the places, there is a list of queries. Each query is formed by an integer - the required number of billboards cnt. The queries are read from the input until the end-of-file is reached.

The output of the program is the computed distance of the closest pair of billboards, the output is provided for each input query. There are some combinations of input data where the distance cannot be computed. Namely, the first special case is "infinite" and the second special case is "cannot accomplish". There is a special output in these case. The exact output format is shown in the sample runs below.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

    the suitable positions or the number of billboards are not valid integers,
    suitable billboard positions are negative,
    the list of suitable billboard positions is empty,
    there is more than 1000000 billboard positions in the input,
    the number of billboards cnt is negative,
    there are missing/redundant separators (curly brace, comma).

Sample program runs:

Suitable positions:
{ 250, 500, 750 }
# of billboards:
0
Distance: inf
3
Distance: 250
2
Distance: 500
1
Distance: inf
4
N/A

Suitable positions:
{ 250 , 300 , 550 , 750 }
# of billboards:
1
Distance: inf
5
N/A
4
Distance: 50
2
Distance: 500
3
Distance: 200

Suitable positions:
{481,692,159,843,921,315}
# of billboards:
1
Distance: inf
5
Distance: 156
4
Distance: 211
6
Distance: 78
2
Distance: 762
3
Distance: 322

Suitable positions:
{0,1,2,1,2}
# of billboards:
2
Distance: 2
4
Distance: 0
1
Distance: inf
3
Distance: 1
6
N/A
2
Distance: 2
5
Distance: 0

Suitable positions:
{250,-3}
Invalid input.

Suitable positions:
{15,240 310
Invalid input.

Advice:

    The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
    Do not forget the newline (\n) after the last output line.
    The program is to store the suitable billboard positions. There is up to 1000000 such positions. Therefore, the positions may be stored in a statically allocated array. This task does not require dynamic memory allocation.
    A reasonable implementation of the naive algorithm passes all tests except the bonus tests. The naive algorithm just sets up a minimum billboard distance and tries to place all billboards with that minimum distance. Based on the result, the distance is either increased or decreased until the minimum is found.
    Speed tests #1 and #2 are extra bonus tests. The tests input long highways with many suitable places for the billboards. Moreover, there is a lot of queries with various distances. The naive algorithm is too slow to finish in the given time limit. An efficient algorithm must be used, moreover, it may be advantageous to pre-process the input data.
    The inputs are chosen such that the input values fit into the int data type.
    Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. The memory limit is approx. 500MiB, i.e., more than enough to store the input data in a statically allocated array.
*/

// Returns true if it is possible to arrange k elements of arr[0..n-1] with minimum distance given as mid. 
int isFeasible(int mid, int arr[], int l, int m) { 
    // Place first element at arr[0] position 
            int positions = arr[0]; 
  
    // Initialize count of elements placed. 
            int elements = 1; 
  
    // Try placing k elements with minimum distance mid. 
       for (int i=1; i<l; i++)   { 
          if ((arr[i] - positions) >= mid)  { 
            //Place next element if its distance from the previously placed element is greater than current mid */
                 positions = arr[i]; 
                 elements++;   
            // Return if all elements are placed successfully 
            if (elements == m) 
              return 1; 
        } 
    } 
    return 0; 
} 
  
// Returns largest minimum distance for k elements in arr[0..n-1]. If elements can't be placed, returns -1. 
     int largestMinDist(int arr[], int l, int m)  { 
    // Sort the positions 
        //sort(arr,arr+n); 
  
    // Initialize result. 
             int res = 0; 
  
    // Consider the maximum possible distance 
             int left = 0;
             int  right = arr[l-1]; 
  
    // Do binary search for largest minimum distance 
             while (left < right) { 
                  int mid = (left + right)/2; 
  
        // If it is possible to place k elements with minimum distance mid, search for higher distance. 
                   if (isFeasible(mid, arr, l, m)) { 
            // Change value of variable max to mid iff all elements can be successfully placed  //res = max(res, mid); 
                         if (res < mid) {
                            res = mid; 
                            }
                                left = mid + 1; 
                           
          // If not possible to place k elements, search for lower distance 
                       } else   right = mid; 
                                } 
                                return res; 
                               } 
                    
                           
      int cmpfunc (const void * a, const void * b) {
           int int_a = * ( (int*) a);
           int int_b = * ( (int*) b);
  
          if (int_a == int_b) return 0;
          else if (int_a<int_b) return -1;
          else return 1; 
               }

int main () {

int scanreturn, i, dist, distance_out;
int positions [MAX];     
char ch1, ch2;
 

        printf ("Suitable positions:\n");
           scanreturn = scanf ("%c ",  &ch1); 
               if (ch1 != '{' || scanreturn != 1) {
                      printf ("Invalid input.\n"); 
                             return 0;  
                            }                  
           for (i = 0; i < MAX; i++) {
                scanreturn = scanf ("%d", &positions[i]); 
                scanf (" %c", &ch2);                                                                   
        if (( ch2 != ',' && ch2 != '}' )|| scanreturn !=1 ||  positions[i] < 0 ||  i > 1000000) {   
                       printf ("Invalid input.\n"); 
                             return 0;   
                       }
                  if (ch2 == '}') 
                    break;
                     }
   printf ("# of billboards:\n"); 
   i++;     
qsort(positions, i,  sizeof(int), cmpfunc);

 while (1)  {       
                     
             scanreturn = scanf ("%d", &dist);
                  if (scanreturn == EOF) {
                      return 0;
                    }
               if (dist < 0 || scanreturn != 1) {
                  printf ("Invalid input.\n");
                        return 0;
                       }                                   
          if   (dist == 0 || dist == 1) {
               printf("Distance: inf\n");  
          } else if (dist > i) {
               printf("N/A\n");
          }  else if (dist == 2)  {
               printf("Distance: %d\n", (positions[i-1] - positions[0]));
          }  else  {
                distance_out = largestMinDist(positions, i, dist);
                printf("Distance: %d\n", distance_out); 
                }
                  
                }
                     return 0;
               }




         


