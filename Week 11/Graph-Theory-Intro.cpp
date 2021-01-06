#include <bits/stdc++.h>
using namespace std;



/*
GRAPH THEORY

There are two types of searching methods that we will cover.
BFS - Breadth First search (breakfast search)

"Breadth" - traversing thru all nodes from a single point, put all points in a "line" - queue. Add all the nodes that are connected to the current node in this line, and then you go to the next labeled node in line.

Queue: Taking from the front, but inserting from the back (line).

DFS - Depth First Search

"Depth" - Getting as deep as possible with one path. For every edge that connects to the node, we add those immediately to the stack nodes and then move forward.

Stack:
Push something from the front, and then you also take out from the front - a pile of paper.

*/

queue<int> q; //LIFO
stack<int> stck; //FIFO
deque<int> dq; //all combinations of L and F, a deck is the most OP of the bunch because you can add and remove into the top and bottom

int main() {
	/*q.push(5);
	q.push(6);
	q.push(7);
	q.push(8);
	while (!q.empty()) {
		// In python, I can do x = q.pop(), assigns the value to x
		int x = q.front();
		cout << x << "\n";
		q.pop();
	}

	stck.push(5);
	stck.push(10);
	stck.push(25);
	stck.push(58);
	while (!stck.empty()) {
		cout << stck.top() << "\n";
		stck.pop();
	}*/

	dq.push_back(5); //add to back
	dq.push_front(10); //add to front
	dq.pop_back(); //remove from back
	dq.pop_front(); //remove from front
	/*
	Insertion into the front or back of the deck is done in O(1).
	Deletion from the front or back of the deck is also done in O(1).
	Accessing the front or back is O(1).
	
	Accessing an nth element in a deck (that is not the front or back) is done in O(n).

	struct Person {

	}
	struct Deck {
		Person back;
		Person front;
	}	
	*/
	//IMPLEMENTATIONS
	/*
	1 2
	1 3 
	1 4
	2 5
	2 6
	2 7
	3 8
	4 9
	-1 -1
	*/
	vector<int> graph[40];
	/*
	"graph" is an array of vectors.
	the maximum number of nodes is the array size.
	each node's vector is a list of all the nodes that are connected to it.
	*/
	int a,b;
	while (true) {
		cin >> a >> b;
		if (a == -1) break;
		graph[a].push_back(b);
		//if this was birectional, we have to do 
		//graph[b].push_back(a);
	}
	//BFS
	/*q.push(1);
	while (!q.empty()) {
		int curNode = q.front(); //the current element we are working with
		q.pop();
		cout << curNode << "\n";
		for (int i : graph[curNode]) {
			q.push(i);
		}
		//q.pop();
	}*/
	//DFS
	/*stck.push(1);
	while (!stck.empty()) {
		int curNode = stck.top();
		stck.pop();
		cout << curNode << "\n";
		for (int i = graph[curNode].size()-1; i >= 0; i--) {
			stck.push(graph[curNode][i]);
		}
		
	}*/


}
