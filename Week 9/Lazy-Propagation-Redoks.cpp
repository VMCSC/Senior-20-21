#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250005;

struct Node {
	int L,R;
	int freq[10];
	int lazy = 0; //this is the lazy variable, we do not need to update any children when building the tree
} seg[4*MAXN];

string input;

void build_tree(int v, int L, int R) {
	//assign left and right bounds
	seg[v].L = L;
	seg[v].R = R;
	//check if at leaf node, because you can't divide further
	if (L == R) {
		//assign input[L] as the only thing contributing to the frequency array
		seg[v].freq[input[L]-'0']++;
	}
	else {
		//divide further into 2 child nodes
		//calculate our middle point
		int mid = (L+R)/2;
		//split and build the 2 children nodes
		build_tree(v*2,L,mid);
		build_tree(v*2+1,mid+1,R);
		for (int i = 0; i < 10; i++) {
			seg[v].freq[i] = seg[v*2].freq[i] + seg[v*2+1].freq[i];
		}
	}
}


//LAZY PROPAGATION
/*
Be like a master procrastinator. Do work only when you absolutely need it.
Don't update a node's children until they are needed for a new query.
This will save a lot of time, and even in some cases make solutions go from O(MN) to O(Mlog(N)).
You can't outsmart the procrastinator.

How do I know when I have to update the children?
The effective approach we will use is to have a lazy boolean:
if lazy is true, we will need to update the children eventually (this node was changed when doing the previous query)
if lazy is false, we do not need to update the children

Problems with using boolean lazy value:
Multiple updates pending to children will cause them to only think they have 1 update.
Solution:
Instead of using a boolean for lazy, make the lazy value an integer.
The integer represents the number of pending rotations/dial pressings.

Problem: You, as a node, came into the funciton with pending updates (or rotations).
Solution: Call push_down function inside of the query function, at the VERY BEGINNING

Problem: Child wasn't updating
Solution: Don't listen to Sat, he was lying, apply changes to the node value in the push_down function
*/

//update the children somehow
void push_down(int v) {
	//check if the node doesn't have children
	int L = seg[v].L, R = seg[v].R;
	seg[v].lazy %= 10;
	int tmp[10];
	for (int i = 0; i < 10; i++) {
		tmp[(i+seg[v].lazy)%10] = seg[v].freq[i]; //shifting by seg[v].lazy to the right
	}
	//seg[v].freq = tmp;
	for (int i = 0; i < 10; i++) {
		seg[v].freq[i] = tmp[i]; //assigning all values from tmp to frequency array
	}
	if (L == R) {
		seg[v].lazy = 0;
	}
	else {
		seg[v*2].lazy += seg[v].lazy;
		seg[v*2+1].lazy += seg[v].lazy;
		seg[v].lazy = 0;
	}
}

void update(int v, int UL, int UR) {
	int L = seg[v].L, R = seg[v].R;
	push_down(v);
	if (UR < L || R < UL) {
		return;
	}
	if (UL <= L && R <= UR) {
		//do something with updates
		seg[v].lazy++; //telling the program that we need 1 more cycle shift to myself and my children eventually

		push_down(v);
		return;
	}
	update(v*2,UL,UR);
	update(v*2+1,UL,UR);
	for (int i = 0; i < 10; i++) {
		seg[v].freq[i] = seg[v*2].freq[i] + seg[v*2+1].freq[i];
	}

}

int query(int v, int QL, int QR) {
	int L = seg[v].L, R = seg[v].R;
	push_down(v); //the procrastinator has to do their homework, otherwise they mess up the program and its not good
	//check if query range is OUTSIDE of node range
	if (QR < L || R < QL) {
		//return some value that won't impact the sum
		return 0;
	}
	//2nd case: node range is completely inside query range
	if (QL <= L && R <= QR) {
		//add on the sum of i*freq[i]
		int sum = 0;
		for (int i = 0; i < 10; i++) {
			sum += i * seg[v].freq[i];
		}
		
		return sum;
	}
	//3rd case: partially intersecting, add on the queries for the 2 children
	return query(v*2,QL,QR) + query(v*2+1,QL,QR);

}


int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	int N,M;
	cin >> N >> M;
	cin >> input;

	//before taking queries, build the tree
	build_tree(1,0,N-1);
	// all of your queries
	int A,B;
	for (int q = 0; q < M; q++) {
		cin >> A >> B;
		A--; //going from 1 indexing to 0 indexing 
		B--;
		//query function, start the query from the root (index 1)
		cout << query(1,A,B) << "\n";
		update(1,A,B);
	}
}
