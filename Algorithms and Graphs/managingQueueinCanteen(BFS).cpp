#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
/*
 After well spent holidays, you are back at the school. Unfortunately you haven't managed to acquire a decent timetable and so for the most of the week you have almost no time to get a lunch. Nevertheless, you thought you could always pay a quick visit to the school canteen, which shouldn't take more than a few minutes. However, your first lunch in the canteen didn't go as planned. You spent an hour stuck in the queue, because the campus is full of confused first-year students. Luckily, you aren't a rookie anymore, and so you can utilize some of the dirty tricks you learned, in order to get to the canteen counter faster.

You will be situated at the canteen with two queues, which don't move whatsoever. Your task is to get to the canteen counter in the shortest possible time. During a single unit of time, you can perform one of the following actions:

    either you can jump the queue you are currently standing in (i.e. move one position in the queue forward),
    or you can let the person behind you take your position, and move one position in the queue backwards,
    or you can use your connections and switch places with a friend, who is standing in the adjacent queue several positions in front of you (the number of positions will be given in the input).

In both of the queues are inappropriate people for you to switch positions with — e.g. professors, or classmates, who regularly visit a gym. You can't move to these positions in the queue (not even if you were to offer a better position in the queue). On top of that you need to act fast, as the floor in the canteen will soon be cleaned by a cleaning lady. By no means you can appear on a cleaned part of the floor.

You will be given the length of the queues (it is the same for both of them), a specific number of positions, by which you can move to the adjacent queue, and a description of the queues with marked positions of the inappropriate people. The canteen counter is reached after you appear at an arbitrary position beyond the end of any of the two queues. Movement beyond the end of a queue is always possible. Movement to the adjacent queue is possible only by the given number of positions given in the input, never less. That means if it is possible to move to the adjacent queue by K positions, you can move from position X in one queue to position X + K in the other queue. After performing an action, the length of the queues stays the same (there are always two people switching positions) and similarly the positions of the inappropriate people never change (the exchange of positions always takes place between you at a reachable position and a person suitable for exchanging positions). The cleaning lady cleans the floor in such a way, that in time i the floor at i-th positions from the beginnings of the queues is cleaned. That means in time i you can never appear at i-th, or lower, position from the beginning of a queue. Time starts at 0 and increases by 1 every time you perform an action. Therefore, first you perform and action and then the cleaning lady cleans the floor at positions 1. Afterwards you again perform an action and cleaning lady cleans the floor at positions 2 etc... You start in the left queue at the first position (there will never be an inappropriate person standing there). It is possible for the canteen counter to be unreachable by any sequence of steps.

Input Format:

    On the first line there are two numbers; number N specifying the length of the queues and number K specifying the number of positions by which you can move to the adjacent queue. You can assume that 1 ≤ K ≤ N holds.
    On the second and third line are consecutively descriptions of left and right queues (in this order). The description of a queue is a string of length N consisting of characters '.' (a position you can move to) and 'x' (a position with an inappropriate person, which you can't move to).
    The numbering of positions in the queue is one-based; their numbers are thus 1, ..., N. The canteen counter is thus reached by appearing at an imagined position N + 1, or higher, in an arbitrary queue.
    You can assume the input is valid.

Output Format:

    Output consists of a single row. If there is a way to reach the canteen counter, output the minimal number of actions needed to do so. Should there be no such way, output -1.

Classification Conditions:

    To pass the compulsory tests (basic and small data tests), your solution has to return correct answers for queues of length at most 20.
    To pass the test on medium dataset, your solution has to output correct answers within the time and memory limit for queues of length at most 1 000.
    To pass the test on large dataset, your solution has to output correct answers within the time and memory limit for queues of length at most 100 000.

Examples:
Input example 1:

5 2
....x
.xx.x

Output example 1:

3

Input example 2:

10 4
.xx.x...xx
x.x....x..

Output example 2:

4

Input example 3:

5 1
..x..
..xx.

Output example 3:

-1


*/



struct content_q {
    int  x, y,  dist = 0; };
                   
void BFS ( std::vector <std::string> strin, int lenn, int jump) {
    
    bool visited_firstrow[100000] ={0};
    bool visited_secondrow[100000] ={0};
    
    std::queue <content_q> my_q;
    visited_firstrow[0] = true;
    my_q.push({0, 0, 0});
    
    int min_dist = -1;
   
    while (!my_q.empty()) {
        content_q node = my_q.front();
        my_q.pop();    

        if ( node.y < node.dist) {
            continue;
        }    

     int i = node.x, j = node.y, dist = node.dist;
     if ( j + jump >= lenn || j + 1 == lenn){
         if (min_dist > dist || min_dist == -1) {
         min_dist = dist+1;
         }
         continue;
     }    
 
       if ((!visited_secondrow[j+jump]) && strin[1][j+jump] == '.' && i == 0 )  {
                visited_secondrow[j+jump] = true;
                my_q.push ({1, j+jump, dist +1 }); 
            } else if ((!visited_firstrow[j+jump]) && strin[0][j+jump] == '.' && i == 1 )  {
                visited_firstrow[j+jump] = true;
                my_q.push ({0, j+jump, dist +1 });                      
            }
       if ((!visited_firstrow[j+1]) && strin[0][j+1] == '.'  && i == 0)  {
                visited_firstrow[j+1] = true;
                my_q.push ({0, j+1, dist +1 }); 
            } else if ((!visited_secondrow[j+1]) && strin[1][j+1] == '.' && i == 1 )  {
                visited_secondrow[j+1] = true;
                my_q.push ({1, j+1, dist +1 });
            }
            if (j != 0){
       if ((!visited_firstrow[j-1]) && strin[0][j-1] == '.' && i == 0 )  {
                visited_firstrow[j-1] = true;
                my_q.push ({0, j-1, dist +1 }); 
           } else if ((!visited_secondrow[j-1]) && strin[1][j-1] == '.' && i == 1 )  {
                visited_secondrow[j-1] = true;
                my_q.push ({1, j-1, dist +1 });
               }
            }
        // std::cout << "x, y, dist =  " << my_q.front().x <<" , " << my_q.front().y << " , " << my_q.front().dist <<std::endl;  
    }
         std::cout <<min_dist<<std::endl;

}
    int main () {

        int len, k;
        std::string first_q, second_q;     
        std::cin >> len >> k >> first_q >> second_q;
        std::vector <std::string> str;       
        str.push_back(first_q);
        str.push_back(second_q);   
              
        BFS ( str, len, k);

        return 0;
    }

    





