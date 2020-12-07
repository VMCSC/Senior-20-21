#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int N,M;

struct Node {
	int L,R;
	int minVal,gcdVal,maxVal;
	
} seg[4*MAXN];
int arr[MAXN];


int oldGCD(int a, int b) {
	if (b == 0) return a;
	return oldGCD(b,a%b);
}




void build_tree(int v, int L, int R) {
	seg[v].L = L;
	seg[v].R = R;
	if (L == R) {
		seg[v].minVal = arr[L];
		seg[v].maxVal = arr[L];
		seg[v].gcdVal = arr[L];

		//return;
	}
	else {
		int mid = (L+R)/2;
		build_tree(v*2,L,mid);
		build_tree(v*2+1,mid+1,R);
		seg[v].minVal = min(seg[v*2].minVal,seg[v*2+1].minVal);
		seg[v].maxVal = max(seg[v*2].maxVal,seg[v*2+1].maxVal);
		seg[v].gcdVal = gcd(seg[v*2].gcdVal,seg[v*2+1].gcdVal);

	}

}

int minQuery(int v, int QL, int QR) {
	int L = seg[v].L, R = seg[v].R;
	if (QR < L || R < QL) {
		return INT_MAX;
	}
	if (QL <= L && R <= QR) {
		return seg[v].minVal;
	}
	return min(minQuery(v*2,QL,QR),minQuery(v*2+1,QL,QR));
}

int gcdQuery(int v, int QL, int QR) {
	int L = seg[v].L, R = seg[v].R;
	if (QR < L || R < QL) {
		//gcd(0,x) = x
		return 0;
	}
	if (QL <= L && R <= QR) {
		return seg[v].gcdVal;
	}
	return gcd(gcdQuery(v*2,QL,QR),gcdQuery(v*2+1,QL,QR));
}

void update(int v, int idx, int newVal) {
	//update function
	int L = seg[v].L, R = seg[v].R;
	if (idx < L || R < idx) {
		//completely outside of the range, we need to nothing here
		return;
	}
	if (idx == L && idx == R) {
		//update the leaf node here
		seg[v].gcdVal = newVal;
		seg[v].minVal = newVal;
		seg[v].maxVal = newVal;
		return;
	}
	//recursive calls
	update(v*2,idx,newVal);
	update(v*2+1,idx,newVal);
	//after child gets updated, you will be here for the parent
	//this is the location to update the parent
	seg[v].minVal = min(seg[v*2].minVal,seg[v*2+1].minVal);
	seg[v].maxVal = max(seg[v*2].maxVal,seg[v*2+1].maxVal);
	seg[v].gcdVal = gcd(seg[v*2].gcdVal,seg[v*2+1].gcdVal);

}

int rangeCount(int v, int QL, int QR, int val) {
	//all the values in the node's have to be equal to some value to add on to the Q query 
	int L = seg[v].L, R = seg[v].R;
	/*
	few things to notice:
	1. if the gcd of a node > val, all numbers in the range are > val, return 0 since it wont have any elements that are equal to val
	2. seg[v].minVal > val, return 0, also if seg[v].maxVal < val

	3. seg[v].gcdVal == val && seg[v].maxVal == val (seg[v].maxVal == seg[v].minVal), return number of elements in the range [L,R]
	*/
	if (seg[v].gcdVal > val || seg[v].minVal > val || seg[v].maxVal < val) {
		return 0;
	}
	if (QR < L || R < QL) {
		return 0;
	}
	if (QL <= L && R <= QR) {
		if (seg[v].gcdVal == val && seg[v].maxVal == val) return R-L+1;
	}
	return rangeCount(v*2,QL,QR,val) + rangeCount(v*2+1,QL,QR,val);
}


int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) cin >> arr[i];
	build_tree(1,1,N);
	char qType;
	int v1,v2;
	for (int q = 0; q < M; q++) {
		cin >> qType >> v1 >> v2;
		if (qType == 'C') {
			arr[v1] = v2;
			//looking for node in seg tree with range [v1,v1]
			//update the gcdVal and minVal of that node
			//update the parents if necessary

			/*
			5 8
			min(5,8) = 5
			MODIFY THE 5 TO A 9
			min(9,8)=  8
			*/
			update(1,v1,v2);
		}
		else if (qType == 'M') {
			//calling some min query function
			cout << minQuery(1, v1, v2) << "\n";
		}
		else if (qType == 'G') {
			cout << gcdQuery(1, v1, v2) << "\n";
		}
		else {
			//Q query
			//get gcd(l,r)
			int gcdValue = gcdQuery(1, v1, v2);
			//range count from [l,r], how many are equal to gcdValue
			cout << rangeCount(1,v1,v2,gcdValue) << "\n";
		}
	}

}
