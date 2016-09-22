/* 
Program to find the number of strongly connected components in a graph.
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

	node(int val, node* next) {
		data = val;
		link = next;
	}
};

class list {
public:
	node* head;
};


class queue {
public:
	node* front;
	node* rear;

	queue() {
		front = rear = NULL;
	}

	int isEmpty() {
		return front == NULL;
	}

	void enqueue(int i) {
		node* newnode = new node(i);
		if (rear == NULL) {
			rear = front = newnode;
		}
		else {
			rear->link = newnode;
			rear = newnode;
		}
	}

	int dequeue() {
		if (front == NULL)
			return -1;
		node* temp = front;
		front = front->link;
		int data = temp->data;
		free(temp);
		if (!front) {
			front = rear = NULL;
		}
		return data;
	}
};

class graph {
public:
	int V;
	list* adjList;
	int *visited;
	queue* q;

	graph(int v) {
		V = v;
		adjList = new list[V];
		visited = new int[V];
		q = new queue();

		for (int i = 0; i < V; i++)
			visited[i] = 0;

		for (int i = 0; i < V; i++)
			adjList[i].head = new node(i);
	}

	void addEdge(int v1, int v2) {
		node* link = adjList[v1].head->link;
		node *newnode = new node(v2,link);
		adjList[v1].head->link = newnode;
	}

	void printList() {
		for (int i = 0; i < V; i++) {
			node* temp = adjList[i].head;
			while (temp) {
				cout << temp->data << " -> ";
				temp = temp->link;
			}
			cout << "null" << endl;
		}
	}

	void bfs(int s) {
		cout << s << " -> ";
		q->enqueue(s);
		visited[s] = 1;
		while (!q->isEmpty()) {
			int val = q->dequeue();
			node *cur = adjList[val].head->link;
			while (cur) {
				int v = cur->data;
				if (!visited[v]) {
					cout << v << " -> ";
					q->enqueue(v);
					visited[v] = 1;
				}
				cur = cur->link;
			}
		}
	}

	int bfsLoop() {
		int components = 0;
		for (int i = 0; i < V; i++) {
			if (!visited[i]) {
				components++;
				bfs(i);
			}
		}
		return components;
	}
};

int main() {
	fstream in;
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
	cout << endl<< "components: " << g->bfsLoop() << endl;
}