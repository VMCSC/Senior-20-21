#include <bits/stdc++.h>
using namespace std;

const int MAXSZ = 1005;
vector<int> graph[MAXSZ]; //for every index, it will hold a vector of all cities it is connected to
int S,E;
int maxDist;
bool vis[MAXSZ];
/*
Strategy: Have some sort of boolean array holding whether I have visited a node. So, what this will do is prevent any node from being accessed twice in the same path.
We also need an answer variable, holding the maximum number of nodes to traverse in order to go from S to E. 
*/

//create a function that reaches out to other cities and tries to find a path to the end
void traverse(int curCity, int dist) {
    vis[curCity] = true;
    if (curCity == E) {
        //when we update maxDist, because we reached the end
        maxDist = max(maxDist,dist);
    }
    else {
        for (int nextCity : graph[curCity]) {
            if (!vis[nextCity]) {
                
                traverse(nextCity,dist+1);
                //i need to unflag the vis[nextCity]
            }
        }
    }
    vis[curCity] = false;
}

int main() {
    int T;
    cin >> T;
    int a,b;
    for (int i = 0; i < T; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cin >> S >> E;
    maxDist = -100000;

    //call my recursive function from the start, setting the vis[start] = true before
    traverse(S, 0);
    cout << maxDist << "\n";

}