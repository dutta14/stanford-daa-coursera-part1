/*
Program to find the number of strongly connected components in a graph.
*/
#include <iostream>
#include <fstream>
using namespace std;

//1. reverse the graph
//2. run dfs on grev
//3. put time=1 to n for each end of dfs
//4. rename nodes with f(t) values
//5. again reverse the graph to get g
//4. run dfs on g from v=N to 1
//5. set leader node s
//6. all nodes with same leader are in one component.

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

class edge {
public:
	int v1, v2;
	edge() {
		v1 = v2 = -1;
	}

	edge(int v1, int v2) {
		this->v1 = v1;
		this->v2 = v2;
	}
};

class graph {
public:
	int V;
	list* adjList;
	int *visited, *ftime;
	int t,s;

	graph(int v) {
		V = v;
		adjList = new list[V];

		for (int i = 0; i < V; i++)
			adjList[i].head = new node(i);

		visited = new int[V];
		ftime = new int[V];
		for (int i = 0; i < V; i++) {
			visited[i] = ftime[i] =  0;
		}
	}

	void addEdges(int v1, int v2) {
		node *link = adjList[v1].head->link;
		node *newnode = new node(v2, link);
		adjList[v1].head->link = newnode;
	}

	void printList() {
		for (int i = 0; i < V; i++) {
			node* cur = adjList[i].head;
			while (cur) {
				cout << cur->data << " -> ";
				cur = cur->link;
			}
			cout << "NULL" << endl;
		}
	}

	void printFtimes() {
		for (int i = 0; i < V; i++) {
			cout << endl<< i << ":" << ftime[i];
		}
	}

	void DFSLoop(int print) {
		t = s= 0;
		for (int i = V - 1; i >= 0; i--) {
			if (!visited[i]) {
				s++;
				dfs(i);
			}
		}
		print ? cout << "Strongly Connected Components: " << s <<endl: cout << "";
	}

	void dfs(int i) {
		visited[i] = 1;
		node* cur = adjList[i].head->link;
		while (cur) {
			int j = cur->data;
			if (!visited[j]) {
				dfs(j);
			}
			cur = cur->link;
		}
		ftime[i] = ++t;
	}

	edge* updateEdges(edge* e, int m) {
		for (int i = 0; i < m; i++) {
			e[i] = edge(ftime[e[i].v1]-1, ftime[e[i].v2]-1);
		}
		return e;
	}
};

int main() {
	ifstream in;
	in.open("Text2.txt");
	int n, m;
	in >> n >> m;
	graph *g = new graph(n);

	edge *e = new edge[m];
	for (int i = 0; i < m; i++) {
		int v1, v2;
		in >> v1 >> v2;
		e[i] = edge(v1, v2);
		g->addEdges(v2, v1); //reverse the graph
	}

	//g->printList();
	g->DFSLoop(0);
	//g->printFtimes();
	e = g->updateEdges(e, m);
	free(g);
	g = new graph(n);
	for (int i = 0; i < m; i++) {
		g->addEdges(e[i].v1, e[i].v2);
	}
	g->DFSLoop(1);
	return 0;
}