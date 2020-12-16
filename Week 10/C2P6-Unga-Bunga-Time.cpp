#include <bits/stdc++.h>
using namespace std;

int dp[105][105];

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int T;
    string oldStr,newStr;
    cin >> T;
    for (int q = 0; q < T; q++) {
        cin >> oldStr >> newStr; //0 indexing
        for (int i = 0; i < 105; i++) {
            //assigning base cases
            dp[0][i] = dp[i][0] = i;
        }
        for (int i = 1; i <= oldStr.size(); i++) { //1 indexing
            for (int j = 1; j <= newStr.size(); j++) {
                //"knapsack"
                if (oldStr[i-1] == newStr[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    dp[i][j] = min(dp[i-1][j-1]+1,min(dp[i][j-1]+1,dp[i-1][j]+1));
                }
            }
        }
        cout << dp[oldStr.size()][newStr.size()] << "\n";
    }

}