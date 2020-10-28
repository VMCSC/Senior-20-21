// Will not pass, try to optimize
#include <bits/stdc++.h>
using namespace std;

//int N,W
int knapsack[105][100005];

int main() {
    //knapsack
    //2d array, one dimension has # of items currently considered (up to N) and the other is all the possible sum of weights (up to W)
    cin.sync_with_stdio(0);
    cin.tie(0);
    int N,W;
    int wi,vi;
    cin >> N >> W;
    //memset(knapsack,0,sizeof(knapsack));
    for (int i = 0; i < 105; i++) {
        for (int j = 0; j < 100005; j++) {
            knapsack[i][j] = 0;
        }
    }
    /*
    Idea of knapsack:
    For every current item considered:
    Either choose that item, knapsack[i][j] = knapsack[i-1][j-current weight] + value of item
    OR
    If that is not optimal or not possible due to not being high enough in sum of weights
    knapsack[i][j] = knapsack[i-1][j]

    For the first item, if we did 0-indexing for i, then knapsack[0][anything]
    knapsack[i][weight of first item] ---> knapsack[i][total sum of weight]
    0-1 out of bounds

    i =1,2,3,...,N
    SAME algortihm for every i value

    */
    for (int i = 1; i <= N; i++) {
        cin >> wi >> vi;
        for (int j = 0; j <= W; j++) { //0 to max sum of weights
            //max([i-1][j],[i-1][j-weight of item]+value of item)
            if (j - wi >= 0) {
                knapsack[i][j] = max(knapsack[i-1][j],knapsack[i-1][j-wi]+vi);
            }
            else {
                //                    can't include that item
                knapsack[i][j] = knapsack[i-1][j];
            }
        }

    }
    //print out the maximum value that we have determined
    cout << knapsack[N][W] << "\n";
    

}