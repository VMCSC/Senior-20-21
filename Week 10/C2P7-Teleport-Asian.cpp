#include <bits/stdc++.h>
using namespace std;

int lines[15]; //teleporting distances 
bool dp[1005]; //can yang get x units away from his house, x being every index

//dp[i] = true if dp[i-length] is true

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> lines[i];
    }
    int satsHouse;
    cin >> satsHouse;
    //loop through all indices from 0-satsHouse, checking if i can get to that distance from a teleport distance back to here
    dp[0] = true;
    for (int i = 1; i <= satsHouse; i++) {
        for (int j = 0; j < T; j++) {
            //if i can do lines[j] units back and still be in a valid distance away from yang's house
            if (i-lines[j] >= 0) {
                dp[i] = dp[i-lines[j]];
            }
            //if its true for any of the lines, then i can just leave
            if (dp[i]) {
                break;
            }
        }
    }
    cout << dp[satsHouse] << "\n";
}