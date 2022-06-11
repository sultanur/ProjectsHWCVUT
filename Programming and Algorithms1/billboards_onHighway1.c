#include <stdio.h>
#include <stdlib.h>

/*
The task is to develop a program that plans the positions of billboards along a highway.

Even though billboards positioned along highways impose some threat, they are still used as an efficient form of advertising. The efficiency of the billboards may be increased if the layout is well thought up. The task is to develop a program to solve the planning. We assume there is a highway of length len. There are certain places along the highway suitable to place the billboards (conversely, the billboards cannot be placed anywhere else). The suitable places are identified by their position from the beginning of the highway; the position is an integer in the range [1;len-1]. There is at most 1000000 such places.

We are about to use some of the places for our advertising. Our concern is to use as few billboards as possible. On the other hand, we require that the distance between two consecutive billboards is at most dist. The first billboard must be placed within dist from the beginning of the highway. Similarly, the last billboard must be placed within dist from the end of the highway. Based on these criteria, the program shall find the required number of billboards.

The input of the program is an integer - the length of the highway len. The length is followed by the list of suitable places. Each place is described by an integer; the integers are enclosed in curly braces and separated by commas. Following the places, there is a list of queries. Each query is formed by an integer - the distance dist. The queries are read from the input until the end-of-file is reached.

The output of the program is the required number of billboards for each input query. The billboards cannot be placed for certain combinations of positions and distances. A different output is printed out in these case. The exact output format is shown in the sample runs below.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

    the distances are not valid integers,
    highway length is zero or negative,
    suitable billboard positions do not fit the range <1;len-1>,
    the list of suitable billboard positions is empty,
    there is more than 1000000 billboard positions in the input,
    the distance dist is negative or zero,
    there are missing/redundant separators (curly brace, comma, colon).

Sample program runs:

Suitable positions:
1000: { 250, 500, 750 }
Distances:
800
Billboards: 1
500
Billboards: 1
300
Billboards: 3
250
Billboards: 3
200
N/A

Suitable positions:
1000 : { 250 , 300 , 550 , 750 }
Distances:
371
Billboards: 3
507
Billboards: 2
273
Billboards: 4
561
Billboards: 1

Suitable positions:
1000:{481,692,159,843,921,315}
Distances:
1000
Billboards: 0
999
Billboards: 1
519
Billboards: 1
518
Billboards: 2
377
Billboards: 2
376
Billboards: 3
315
Billboards: 3
314
Billboards: 4
308
Billboards: 4
307
Billboards: 5
211
Billboards: 5
210
N/A

Suitable positions:
3:{1,2,1,2}
Distances:
1
Billboards: 2
10
Billboards: 0

Suitable positions:
500:{250,830}
Invalid input.

Suitable positions:
330:{15,240 310
Invalid input.

Advice:

    The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
    Do not forget the newline (\n) after the last output line.
    The program is to store the suitable billboard positions. There is up to 1000000 such positions. Therefore, the positions may be stored in a statically allocated array. This task does not require dynamic memory allocation.
    A reasonable implementation of the naive algorithm passes all tests except the bonus tests. The naive algorithm just passes the suitable positions an allocates them with respect to the maximal allowed distance.
    Speed tests #1 and #2 are extra bonus tests. The tests input long highways with many suitable places for the billboards. Moreover, there is a lot of queries with various distances. The naive algorithm is too slow to finish in the given time limit. An efficient algorithm must be used, moreover, it may be advantageous to pre-process the input data.
    The inputs are chosen such that the input values fit into the int data type.
    Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. The memory limit is approx. 500MiB, i.e., more than enough to store the input data in a statically allocated array.
*/

#define MAX 1000000

int getClosest(int, int, int); 
  
// Returns element closest to target in arr[] 
int findClosest(int arr[], int n, int target) 
{ 
    // Corner cases 
    if (target <= arr[0]) 
        return arr[0];  
    if (target >= arr[n - 1]) 
        return arr[n - 1]; 
  
    // Doing binary search 
    int i = 0, j = n, mid = 0; 
    while (i < j) { 
        mid = (i + j) / 2; 
  
        if (arr[mid] == target) 
            return arr[mid]; 
  
        /* If target is less than array element, 
            then search in left */
        if (target < arr[mid]) { 
  
            // If target is greater than previous 
            // to mid, return closest of two 
            if (mid > 0 && target > arr[mid - 1]) 
                return getClosest(arr[mid - 1], 
                                  arr[mid-1], target); 
  
            /* Repeat for left half */
            j = mid; 
        } 
  
        // If target is greater than mid 
        else { 
            if (mid < n - 1 && target < arr[mid + 1]) 
                return getClosest(arr[mid], 
                                  arr[mid], target); 
            // update i 
            i = mid+1;  
        } 
    } 
  
    // Only single element left after search 
    return arr[mid-1]; 
} 
  
// Method to compare which one is the more close. 
// We find the closest by taking the difference 
// between the target and both values. It assumes 
// that val2 is greater than val1 and target lies 
// between these two. 
int getClosest(int val1, int val2, 
               int target) 
{ 
    if (target - val1 >= val2 - target) 
        return val2; 
    else
        return val1; 
} 
  
// Driver code 
/*int main() 
{ 
    int arr[] = { 1, 2, 4, 5, 6, 6, 8, 9 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    int target = 11; 
    cout << (findClosest(arr, n, target)); 
} 
*/
 int cmpfunc (const void * a, const void * b) {
    int int_a = * ( (int*) a);
    int int_b = * ( (int*) b);
  
   if (int_a == int_b) return 0;
   else if (int_a<int_b) return -1;
   else return 1;
}
  
 int main () {

int scanreturn,scanreturn1, length, i;
int positions [MAX];     
char ch1, ch2, ch3;
int dist, scanreturn2, p=0;
int k = 0, count = 0; 

        printf ("Suitable positions:\n");
           scanreturn = scanf ("%d %c %c ", &length, &ch1, &ch2); 
               if (ch1 != ':' || ch2 != '{' || length <= 0 || scanreturn != 3) {
                      printf ("Invalid input.\n"); 
                             return 0;  
                            }                  
               for (i = 1; i < MAX; i++) {
                    scanreturn1 = scanf ("%d", &positions[i]); 
                    scanf (" %c", &ch3);                                                                   
                  if (( ch3 != ',' && ch3 != '}' )|| scanreturn1 !=1 || length < positions[i] || positions[i] <= 0 || positions[i] > length-1 || i > 1000000) {   
                       printf ("Invalid input.\n"); 
                             return 0;   
                       }
                  if (ch3 == '}') 
                   break;
                     }
   printf ("Distances:\n"); 
qsort(positions, i+1,  sizeof(int), cmpfunc);

  while (1)  {       
    // me:            
p = 0;
//T = 1;
count =0;   
int tmp=0;                     
             scanreturn2 = scanf ("%d", &dist);
                  if (scanreturn2 == EOF) 
                      return 0;
               if (dist <= 0 || scanreturn2 != 1) {
                  printf ("Invalid input.\n");
                              return 0;
                  }
                             
  if (dist > length -1)
   {   
      printf ("Billboards: %d\n", 0);
   } else {
   while (1) {
      if ((p + dist) <= (length-1)) {  
         k = findClosest(positions, i+1, p + dist);
    } else {
 //        T = 0;
         break;
    } if (p !=k) {
         p = k;
         count++; 
    } else { 
         printf ("N/A\n");  
         tmp = 1; 
         break;  
       }
     }       
       if(tmp==0)
   printf ("Billboards: %d\n", count);  
   }
  }

        return 0;
 }  


