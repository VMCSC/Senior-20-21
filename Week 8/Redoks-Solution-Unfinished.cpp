#include <bits/stdc++.h>
using namespace std;

const int MAXN = 250005;
int N,M;
string initialConfig;

struct Node {
	int L,R;
	int freq[10]; //frequency of numbers
	int lazy;

} seg[4*MAXN];

void build_tree(int v, int L, int R) {
	seg[v].L = L;
	seg[v].R = R;
	seg[v].lazy = 0; //this holds the number of pending presses to do
	if (L == R) {
		memset(seg[v].freq,0,sizeof(seg[v].freq));
		seg[v].freq[initialConfig[L-1]-'0'] = 1;
	}
	else {
		int mid = (L+R)/2;
		build_tree(v*2,L,mid);
		build_tree(v*2+1,mid+1,R);
		for (int i = 0; i < 10; i++) {
			seg[v].freq[i] = seg[v*2].freq[i] + seg[v*2+1].freq[i];
		}
	}
}

void push_lazy(int v) {
	//this will update the current node, and give the lazy values to the two children
	int L = seg[v].L, R = seg[v].R;
	//change the frequency somehow
	/*
	[1,3,0,0,4,6,5,0,0,1] shifted right by 3
	[0,0,1,1,3,0,0,4,6,5] <-- new frequency array
	*/
	int tmp[10]; //our new frequency array
	seg[v].lazy %= 10;
	for (int i = 0; i < 10; i++) {
		tmp[i] = seg[v].freq[(i-seg[v].lazy+10)%10];
	}
	for (int i = 0; i < 10; i++) {
		seg[v].freq[i] = tmp[i];
	}
	//pushing lazy values to children
	if (L == R) {
		//no children to update
		seg[v].lazy = 0;
		return;
	}
	seg[v*2].lazy += seg[v].lazy;
	seg[v*2].lazy %= 10; //remove unnecessary cycles
	seg[v*2+1].lazy += seg[v].lazy;
	seg[v*2+1].lazy %= 10; //remove unnecessary cycles
	seg[v].lazy = 0;

}

int sumQuery(int v, int QL, int QR) {
	int L = seg[v].L, R = seg[v].R;
	push_lazy(v);
	if (QR < L || R < QL) return 0;
	if (QL <= L && R <= QR) {
		int tot = 0;
		for (int i = 0; i < 10; i++) {
			tot += i*seg[v].freq[i];
		}
		return tot;
	}
	return sumQuery(v*2, QL, QR) + sumQuery(v*2+1, QL, QR);
}

void update(int v, int UL, int UR) {
	int L = seg[v].L, R = seg[v].R;
	push_lazy(v);
	if (UR < L || R < UL) return;
	if (UL <= L && R <= UR) {
		seg[v].lazy++;
		seg[v].lazy %= 10;

		return;
	}
	update(v*2,UL,UR);
	update(v*2+1,UL,UR);
	for (int i = 0; i < 10; i++) {
		seg[v].freq[i] = seg[v*2].freq[i] + seg[v*2+1].freq[i];
	}
}

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	cin >> initialConfig;
	build_tree(1,1,N);
	for (int q = 0; q < M; q++) {
		int a,b;
		cin >> a >> b;
		cout << sumQuery(1, a, b) << "\n";
		//update a RANGE
		/*
		MAKES UPDATES MUCH FASTER --> LAZY PROPAGATION
		The idea behind lazy prop is you want to procrastinate on updates as much as you can.
		Holding them until later guarantees that you have best performance because anything that is not necessary, you will never do. 
		If you ever get multiple things that you have to update on the same node, you can add the lazy values together and do them all later (when you actually access that node for a query).

		*/
		update(1,a,b);
	}

}
