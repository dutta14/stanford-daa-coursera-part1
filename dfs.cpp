/*
Program to run DFS from an input source vertex.
*/
#include <iostream>
#include <fstream>
using namespace std;

class node {
public:
	int data;
	node *link;

	node(int val) {
		data = val;
		link = NULL;
	}

	node(int val, node* l) {
		data = val;
		link = l;
	}
};

class list {
public:
	node* head;
};

class graph {
public:
	int V;
	list* adjList;
	int* visited;

	graph(int v) {
		V = v;
		adjList = new list[V];
		visited = new int[V];

		for (int i = 0; i < V; i++)
			visited[i] = 0;

		for (int i = 0; i < V; i++)
			adjList[i].head = new node(i);
	}

	void addEdge(int v1, int v2) {
		node* temp = adjList[v1].head->link;
		node* newNode = new node(v2,temp);
		adjList[v1].head->link = newNode;
	}

	void dfs(int i) {
		if (!visited[i]) {

			node* cur = adjList[i].head;
			int val = cur->data;

			visited[val] = 1;
			cout << val<< " ";
			cur = cur->link;
			while (cur) {
				dfs(cur->data);
				cur = cur->link;
			}
		}
	}
};

int main() {
	ifstream in;
	in.open("Text2.txt");
	int n, m;
	in >> n >> m;
	graph *g = new graph(n);
	for (int i = 0; i < m; i++) {
		int v1, v2;
		in >> v1 >> v2;
		g->addEdge(v1, v2);
	}
	int v;
	in >> v;
	g->dfs(v);
	cout << endl;
	return 0;
}