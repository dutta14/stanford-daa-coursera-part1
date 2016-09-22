/*
A program to print the adjacency list of a graph.
*/
#include <iostream>
using namespace std;

class node {
public:
	int value;
	node *link;

	node(int val) {
		value = val;
		link = NULL;
	}
};

class list {
public:
	node *head;
};

class graph {
public:
	int V;
	list *adjList;

	graph(int v) {
		V = v;
		adjList = new list[V];
		for (int i = 0; i < V; i++) {
			adjList[i].head = new node(i);
		}
	}

	void addEdge(int v1, int v2) {
		node* temp = adjList[v1].head->link;
		node* newv = new node(v2);
		adjList[v1].head->link = newv;
		newv->link = temp;
	}

	void printGraph() {
		for (int i = 0; i < V; i++) {
			node* temp = adjList[i].head;
			while (temp) {
				cout << temp->value << " -> ";
				temp = temp->link;
			}
			cout << "XXX" << endl;
		}
	}
};

int main() {
	int v, e;
	cin >> v >> e;
	graph *g = new graph(v);
	for (int i = 0; i < e; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		g->addEdge(v1, v2);
	}
	g->printGraph();
	return 0;
}