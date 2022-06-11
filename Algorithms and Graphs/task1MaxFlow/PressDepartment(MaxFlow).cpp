#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

/*
The current government is losing support among the citizens of the country, so the PR team of the prime minister’s movement decided to hold a press conference. The main goal of the conference is to convince the voters that all the bad things are due to opposition, to promise that taxes will be reduced and pensions, on the other hand, increased.

Parties that form the ruling coalition are not evenly represented, each one has a different number of representatives in the government. Due to this, each party has assigned the minimum and the maximum number of words that may be spoken by its representatives at the conference.

All members of parliament were elected with some election program. Although politicians usually do not behave according to their program, they would like to show at least at this pre-election press conference that they are ardent supporters of their program. Because of this, each politician is only willing to talk about a limited set of topics covered by the text of the speech.

Your goal is, as a member of a press department, to partition parts of the prepared speech between attendants of the press conference. You must not violate the minimal and maximal number of words assigned to each party. Also, the politician’s requirements on topics must be observed. You have to recognize the situations when the partitioning is not possible without violating the provided restrictions.

To maintain the appearance of the unity of the coalition, each word of each sentence may be spoken by a different politician. It is not even necessary for these politicians to be members of the same political party.
Input format

    The input starts with four numbers M, O, R, and T, where M stands for the number of political parties, O denotes the number of politicians, R stands for the number of sentences of the speech, and T is the number of topics mentioned in the speech.
    Then follows M lines consisting out of the pair of numbers t_min and t_max, where t_min denotes the minimum, and t_max denotes the maximum number of words assigned to this party.
    Then follows O lines. Each line begins with numbers m and t, where m is the identification of a political party the politician belongs to, and t is the number of topics the politician is capable to speak about. After this pair, there are t space-separated numbers of the topics about which the politician is willing to talk.
    The input ends with R lines containing pair of numbers. The first number denotes the identification of the topic relevant to this sentence, and the second number is the number of words in the sentence.
    The input is always valid.

Output format

    The output consists out of O lines o_1,…,o_n, where every row o_i contains R space-separated numbers. Each of these numbers represents a number of words that will be sad by the politician i-1. If the speech does not satisfy provided criteria, you have to print value -1 to the standard output.

Classification conditions

    To obtain 1 point you have to correctly solve instances with t_min = 0, M = 1, 1 ≤ O,R,T ≤ 100, and where each sentence consists exactly out of a single word.
    To obtain 5 points you have to correctly solve instances with t_min = 0 a 1 ≤ M,O,R,T ≤ 100.
    To obtain 10 points you have to correctly solve instances with t_min = 0 a 1 ≤ M,O,R,T ≤ 1000.
    To obtain 15 points you have to correctly solve instances with 0 ≤ t_min a 1 ≤ M,O,R,T ≤ 1000.

Examples
Example input 1

2 4 4 4
0 2
0 2
0 1 3
0 1 0
1 1 1
1 1 2
0 1
1 1
2 1
3 1

Example output 1

0 0 0 1
1 0 0 0
0 1 0 0
0 0 1 0

Example input 2

1 2 2 2
0 1
0 1 0
0 1 0
0 2
0 2

Example output 2

-1


*/
void add_edge (int a, int b, int cap);
bool bfs();
int dfs (int v, int flow);
int dinic();

const int MAXN = 3000; 
const int INF = 1000000000; 

struct edge {
    int a, b, cap, flow;
};

int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<int> g[MAXN];
vector<int> t_min, t_max;
vector<vector<int> > politics;
vector<vector<int> > politics_sent;
vector<int> politics_part;
vector<int> sent_topic;
vector<int> sent;
vector<int> topics;
vector<int> topics_ptr;
vector<vector<int> > topics_sent;

vector<vector<int> > parts_needs;
vector<vector<int> > parts_needs_polIdx;
vector<int> parts_needs_sum;


void add_edge (int a, int b, int cap) {
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back ((int) e.size());
    e.push_back (e1);
    g[b].push_back ((int) e.size());
    e.push_back (e2);
}

bool bfs() {
    int qh=0, qt=0;
    q[qt++] = s;
    memset (d, -1, n * sizeof d[0]);
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        int v = q[qh++];
        for (size_t i=0; i<g[v].size(); ++i) {
            int id = g[v][i],
                to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

int dfs (int v, int flow) {
    if (!flow)  return 0;
    if (v == t)  return flow;
    for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
            to = e[id].b;
        if (d[to] != d[v] + 1)  continue;
        int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id^1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic() {
    int flow = 0;
    for (;;) {
        if (!bfs())  break;
        memset (ptr, 0, n * sizeof ptr[0]);
        while (int pushed = dfs (s, INF))
            flow += pushed;
    }
    return flow;
}

int main(void)
{
    int M, O, R, T;
    cin >> M >> O >> R >> T;

    t_min.resize(M);
    t_max.resize(M);
    for (int i = 0; i < M; ++i) {
        cin >> t_min[i] >> t_max[i];
    }

    politics.resize(O);
    politics_part.resize(O);
    for (int i = 0; i < O; ++i) {
        int k;
        politics[i].resize(T);
        cin >> politics_part[i] >> k;
        for (int j = 0; j < k; ++j) {
            int tmp;
            cin >> tmp;
            politics[i][tmp] = 1;
        }
    }

    topics_sent.resize(T);
    sent.resize(R);
    sent_topic.resize(R);
    topics.resize(T);
    for (int i = 0; i < T; ++i) {
        topics[i] = 0;
    }
    for (int i = 0; i < R; ++i) {
        cin >> sent_topic[i] >> sent[i];
        topics[sent_topic[i]] += sent[i];
        topics_sent[sent_topic[i]].push_back(i);
    }

    parts_needs.resize(M);
    parts_needs_polIdx.resize(M);
//    parts_needs_sum.resize(M);
    fill(parts_needs_sum.begin(), parts_needs_sum.end(), 0);
    for (int i = 0; i < M; ++i) {
        parts_needs[i].resize(T);
        parts_needs_polIdx[i].resize(T);
        fill(parts_needs[i].begin(), parts_needs[i].end(), 0);
        fill(parts_needs_polIdx[i].begin(), parts_needs_polIdx[i].end(), -1);
    }
    for (int i = 0; i < O; ++i) {
        for (int j = 0; j < T; ++j) {
            if (politics[i][j] == 1) {
                parts_needs[politics_part[i]][j]++;
                parts_needs_polIdx[politics_part[i]][j] = i;
//                parts_needs_sum[politics_part[i]]++;
//                topics[j]--;
                if (topics[j] < 0) {
                    cout << -1 << endl;
                    return 0;
                }
            }
        }
    }
//    for (int i = 0; i < M; ++i) {
//        t_min[i] -= parts_needs_sum[i];
//        if (t_min[i] < 0) {
//            t_min[i] = 0;
//        }
//        t_max[i] -= parts_needs_sum[i];
//        if (t_max[i] < 0) {
//            cout << -1 << endl;
//            return 0;
//        }
//    }

    for (int i = 0; i < T; ++i) {
        add_edge(T + M, i, topics[i]);
    }

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < T; ++j) {
            if (parts_needs[i][j] > 0) {
                add_edge(j, T + i, INF);
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        add_edge(i + T, T + M + 1, t_max[i] - t_min[i]);
    }

    int flag = 0;

    for (int i = 0; i < M; ++i) {
        if (t_min[i] > 0) {
            add_edge(T + M + 2, T + M + 1, t_min[i]);
            add_edge(i + T, T + M + 3, t_min[i]);
            flag = 1;
        }
    }
    if (flag == 1) {
        add_edge(T + M + 1, T + M, INF);
        s = T + M + 2;
        t = T + M + 3;
        n = T + M + 4;
    } else {
        s = T + M;
        t = T + M + 1;
        n = T + M + 2;
    }


    int neededFlow = 0;
    for (size_t i = 0; i < topics.size(); ++i) {
        neededFlow += topics[i];
    }

    int maxFlow = dinic();

    if (maxFlow != neededFlow) {
        cout << -1 << endl;
        return 0;
    }


    for (int i = 0; i < O; ++i) {
        fill(politics[i].begin(), politics[i].end(), 0);
    }


    for (size_t i = 0; i < e.size(); ++i) {
        if (e[i].a < T && e[i].b >= T && e[i].b < T + M) {
            politics[parts_needs_polIdx[e[i].b - T][e[i].a]][e[i].a] += e[i].flow;
        }
    }

    politics_sent.resize(O);
    for (int i = 0; i < O; ++i) {
        politics_sent[i].resize(R);
        fill(politics_sent[i].begin(), politics_sent[i].end(), 0);
    }

    topics_ptr.resize(T);
    fill(topics_ptr.begin(), topics_ptr.end(), 0);


    for (int i = 0; i < O; ++i) {
        for (int j = 0; j < T; ++j) {

            while (   politics[i][j] > 0
                   && sent[topics_sent[j][topics_ptr[j]]] < politics[i][j]) {
                politics_sent[i][topics_sent[j][topics_ptr[j]]] = sent[topics_sent[j][topics_ptr[j]]];
                politics[i][j] -= sent[topics_sent[j][topics_ptr[j]]];
                sent[topics_sent[j][topics_ptr[j]]] = 0;

                topics_ptr[j]++;
            }
            if (politics[i][j] > 0) {
        		politics_sent[i][topics_sent[j][topics_ptr[j]]] = politics[i][j];
        		sent[topics_sent[j][topics_ptr[j]]] -= politics[i][j];

                politics[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < O; ++i) {
        for (int j = 0; j < R; ++j) {
            cout << politics_sent[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
