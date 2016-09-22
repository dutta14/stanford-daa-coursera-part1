/*
Program to run topological sort on a graph.
*/
#include <iostream>
#include <fstream>
using namespace std;

class node {
public:
	int data;
	node* link;

	node(int data) {
		this->data = data;
		link = NULL;
	}

	node(int data, node* link) {
		this->data = data;
		this->link = link;
	}
};

class list {
public:
	node* head;
};

class graph {
public:
	int V, N;
	list* adjList;
	int* visited, *level;

	graph(int v) {
		V = N = v;
		adjList = new list[V];
		for (int i = 0; i < V; i++)
			adjList[i].head = new node(i);

		visited = new int[V];
		for (int i = 0; i < V; i++)
			visited[i] = 0;
		level = new int[V];
		for (int i = 0; i < V; i++)
			level[i] = 1;

	}

	void addEdge(int v1, int v2) {
		node* link = adjList[v1].head->link;
		node* newnode = new node(v2, link);
		adjList[v1].head->link = newnode;
	}

	void printList() {
		for (int i = 0; i < V; i++) {
			node* cur = adjList[i].head;
			while (cur) {
				cout << cur->data << " -> ";
				cur = cur->link;
			}
			cout << "null\n";
		}
	}

	void dfsLoop() {
		for (int i = 0; i < V; i++)
			if (!visited[i]) {
				cout << endl;
				dfs(i);
			}
				
	}

	void dfs(int s) {
		cout << s << " -> ";
		visited[s] = 1;
		node* cur = adjList[s].head->link;
		while (cur) {
			if (!visited[cur->data])
				dfs(cur->data);
			cur = cur->link;
		}
		level[s] = N;
		N--;
	}

	void printLevels() {
		cout << endl;
		for (int i = 0; i < V; i++)
			cout << i << ":" << level[i] << "\n";
		cout << endl;
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
	int s;
	in >> s;
	//g->printList();
	g->dfsLoop();
	g->printLevels();
}