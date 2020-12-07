#include <bits/stdc++.h>
using namespace std;

int main() {
	/*
	You are given 2 lines of input.
	The first line is N, the number of elements in our array. 
	The second line is M, the desired number that we are looking for.

	Using binary search, figure out how many bisections with binary search with the elements of the array {1,2,3,...,N} we have to take to reach M.

	*/

	
	/*
	Sample input:
	N -> 6 (1,2,3,4,5,6)
	M -> 3 
	{1,2,3,4,5,6}
	 0 1 2 3 4 5
	ELement 2: 3
	Output: 0

	Another input:
	N -> 6 (1,2,3,4,5,6)
	M -> 6
	{1,2,3,4,5,6}
	 0 1 2 3 4 5
	Element (0+5)/2 = 2: 3
	M > 3, so we have to eliminate indices 0-2
	Eliminate indices 0-2, remaining is 3-5

	{4,5,6}
	 3 4 5
	Element (3+5)/2 = 4: 5
	M > 5, so we have to eliminate the left side (4-5)
	Remaining indexes are 6-6

	{6}
	 5
	Element (5+5)/2 = 5: 6
	Target found, output 2 for # of bisections

	7, searching for the value 6

	*/


	int N,M;
	cin >> N >> M;
	int arr[N];
	for (int i = 0; i < N; i++) {
		arr[i] = i+1;
		//filling array with values 1,2,3,...,N
	}
	int left,right;
	left = 0; right = N-1;
	int bisects = 0;

	//first assume that M is guaranteed to be in the array
	while (true) {
		int mid = (left+right)/2;
		if (arr[mid] == M) {
			cout << "We found " << M << " in " << bisects << " cuts.\n";
			break;
		}
		bisects++;
		//++bisects;
		if (arr[mid] < M) {
			left = mid+1; //we cut off the left side, namely [old left, mid]
		}
		else if (arr[mid] > M) {
			right = mid-1; //we cut off the right side, namely [mid, old right]
		}

	}



}
