#include <bits/stdc++.h>
using namespace std;

/*
Given N (1 <= N <= 1000) nodes (1,2,3,...,N) and E edges, write a program that will take in two inputs u and v, and output if they are connected to each other.
*/

int N,E;

struct DisjointSetUnion {
	int par[1005]; //the parent of each node is stored in its index
	int subsetRank[1005];
	/*
	The subset rank of a node determines how many connections or things will have to change if you change its parent. The higher the subset rank, the harder it is to eventually modify all node's parents that are connected to it. In other words, if you are merging two nodes x and y with parents px and py respectively, then you must compare the subset ranks of px and py, and the lower of the two will be the one that is modified.
	if (subset rank[px] > subset rank[py]) par[py] = px;
	The reason is because there are less things to modify by changing the parent of py.
	*/
	DisjointSetUnion(int size) {
		//constructor
		for (int i = 1; i <= N; i++) {
			par[i] = i;
			subsetRank[i] = 0;
		}
	}
	int find(int x) {
		//find the parent of x, and set par[x] equal to that if not already
		if (par[x] == x) return x;
		int parent = find(par[x]);
		par[x] = parent;
		return par[x];
	}
	bool connected(int x, int y) {
		//takes two nodes x and y, and checks if they are connected
		int px = find(x), py = find(y);
		/*if (px == py) return true;
		else return false;*/
		return (px == py);
	}
	void merge(int x, int y) {
		//takes two nodes x and y, and connects them together
		int px = find(x), py = find(y);
		if (px == py) return;
		//par[py] = px; //this needs to be more optimized
		if (subsetRank[px] > subsetRank[py]) par[py] = px;
		else if (subsetRank[px] < subsetRank[py]) par[px] = py;
		else {
			//subsetRank[px] == subsetRank[py]
			//In this case, we just choose any one to be more important than the other, and increase its subset rank.
			par[py] = px;
			subsetRank[px]++;
		}
	}
};

int main() {
	cin >> N >> E;
	DisjointSetUnion dsu(N);
	for (int i = 0; i < E; i++) {
		int x,y;
		cin >> x >> y;
		//connect them some way
		dsu.merge(x,y);
	}
	while (true) {
		int u,v;
		cin >> u >> v;
		if (dsu.connected(u,v)) cout << "Connected\n";
		else cout << "Not connected\n";
	}

	/*
	9 6
    1 2
    2 9
    3 9
    4 5
    4 7
    6 4
	1 9
	Connected
	2 4
	Not connected
	2 7
	Not connected
	5 7
	Connected
	8 6
	Not connected
	*/
}