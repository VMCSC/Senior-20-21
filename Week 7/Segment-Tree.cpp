#include <bits/stdc++.h>
using namespace std;

int arr[1000];

struct Node {
	int L,R; //left and right indices
	int val; //the value attributed to the range [L,R]
} seg[4*1000];

//first step, build our tree
void build_tree(int v, int left, int right) {
	//v represents the index of node in the tree
	//left represents the node's assigned left value
	//right represents the node's assigned right value

	//first step: assign the node's left and right values
	seg[v].L = left;
	seg[v].R = right;

	//second step: check whether the node will have children
	//the way we do this is checking whether Left and Right are the same
	if (left == right) {
		//this node is NOT a parent node
		seg[v].val = arr[left];
		//seg[v].val = arr[right]; is equivalent
	}
	else {
		//this is a parent node
		//we have to build the two children and assign the current node's value based off of the children's values
		int mid = (left+right)/2; //mid way between range [left,right] found by the average
		build_tree(v*2,left,mid); //left child
		build_tree(v*2+1,mid+1,right); //right child
		seg[v].val = max(seg[v*2].val,seg[v*2+1].val);
	}

}

int query(int v, int QL, int QR) {
	//index in array, query left, query right
	int L = seg[v].L, R = seg[v].R;
	//case 1: [L,R] is outside [QL,QR]
	//result: return huge value because it is not to be included in the range
	if (R < QL || QR < L) {
		return -1e9;
	}
	//case 2: [L,R] is inside [QL,QR]
	//result: return the node's stored value
	if (QL <= L && R <= QR) {
		return seg[v].val;
	}
	//case 3 (final case): [L,R] intersects with [QL,QR]
	//result: check the return values of the function with the node's 2 children and return the minimum of the two values that we get
	return max(query(v*2,QL,QR), //left
	query(v*2+1,QL,QR)); //right
}

void update(int v, int idx, int newVal) {
	//update element idx in the array, and change it to newVal. The segment tree should be modified to reflect the changes if necessary.
	int L = seg[v].L, R = seg[v].R;
	//step 1: find the node with index idx
	//step 2: change the value of the node that we find
	//step 3: modify the tree if necessary

	//finding node with range [idx,idx], similar to query function
	//case 1: idx is outside the range [L,R]
	if (R < idx || idx < L) {
		return;
	}
	//case 2: idx has been found
	if (L == R && L == idx) {
		//modify node
		seg[v].val = newVal;
		return;
	}
	//case 3: idx is in the range [L,R], but L and R are not the same
	if (L <= idx && idx <= R) {
		//check 2 children
		update(v*2,idx,newVal);
		update(v*2+1,idx,newVal);
		//one of those calls is eventually going to lead to finding the correct node to modify, the current node here (with index v) is an ancestor of the node we modified

		//update tree at this node
		seg[v].val = max(seg[v*2].val,seg[v*2+1].val); //updating the max value, will change if it actually is needed
	}

}

int main() {
	/*
	N - number of elements in the array (N < 1000)
	each line after has a value in the array

	*/
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	//root node has index 1, has a left value of 0 and a right value of N-1
	build_tree(1,0,N-1);
	//query our tree
	while (true) {
		int QL,QR; //query ranges from [QL,QR]
		cin >> QL >> QR;
		//call a query function
		cout << query(1,QL,QR) << endl;

	}


	//update element in tree
	/*
	get input of some index i in the array, and we want to change index i to be some element v (input it as i v on one line) and have the segment tree reflect all of those changes

	*/

}
