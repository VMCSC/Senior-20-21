#include <bits/stdc++.h>
using namespace std;

pair<long long, int> inp[101];
///Weight,     value
long long arr[100005];
//sum of values are indices, and the thing it holds is maximum sum of weights

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	int N,W;
	int sumofVals=0;
	cin >> N >> W;
	/*
	O(W) memory simply will not pass
	O(V) memory or O(NV) memory, V = sum(vi)
	*/
	for (int i = 1; i <= N; i++) {
		cin >> inp[i].first >> inp[i].second;
		sumofVals += inp[i].second;
	}
	/*
	O(V)/O(NV) memory approach:
	store the least weight that you can get on every index
	Indices --> every possible sum of values
	final answer:
	going from index of maximum sum of values backward, and finding the first index such that there is a sum of values that is less than or equal to W
	*/
	for (int i = 1; i < 100005; i++) {
		arr[i] = 10000000000000;
	}
	arr[0] = 0;

	for (int item = 1; item <= N; item++) {
		/*
		For every spot, you want to check back and see if the current weight at index (sum of values) is less than the sum of the weights of the previous index (sum of values) + weight of current item


		arr[i] = min(arr[i],arr[i-v]+w)
		*/
		for (int i = sumofVals; i >= inp[item].second; i--) {
			arr[i] = min(arr[i],arr[i-inp[item].second]+inp[item].first);
		}
		/*
		item had a value of 5
				x --> y
		i = 5: arr[5] = ..... arr[0]+weight of item
		                       y
		i = 10: arr[10] = ... arr[5] + weight of item

		i = 10: update arr[10] according to old value of arr[5]
		i = 5: update arr[5] to a new value (according to arr[0])

		delete some object from a list in an increasing for loop
		when you got to the next one or got to the end --> you had an error


		*/
	}
	//we have to find the highest index that has a valid sum of weights (<= W), that will result in the index we find it at to be our final answer
	for (int i = sumofVals; i >= 0; i--) {
		if (arr[i] <= W) {
			cout << i << "\n";
			break;
			//return 0;
		}
	}
	return 0;

}