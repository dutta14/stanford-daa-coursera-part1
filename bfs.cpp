/*
A program which runs BFS from a start vertex, and then reports the shortest distance between any two points
that can be reached using this BFS.
*/

#include <iostream>
#include <fstream>
using namespace std;

class node {
public:
	int data;
	int level;
	node *link;

	node(int val) {
		data = val;
		link = NULL;
	}

	node(int val, node* ptr) {
		data = val;
		link = ptr;
	}
};

class list {
public:
	node* head;
};

class queue {
public:
	node *front;
	node *rear;

	queue() {
		front = rear = NULL;
	}

	int isEmpty() {
		return front == NULL;
	}

	void enqueue(int i) {
		if (!rear) {
			front = rear = new node(i);	
		}
		else {
			node* temp = new node(i);
			rear->link = temp;
			rear = temp;
		}
	}

	int dequeue() {
		if (front) {
			node* temp = front;
			front = front->link;
			int data = temp->data;
			free(temp);
			if (!front) {
				front = rear = NULL;
			}
			return data;
		}
		else {
			front = rear = NULL;
		}
	}

	void print() {
		node* temp = front;
		while (temp) {
			cout << temp->data << " -> ";
			temp = temp->link;
		}
		cout << endl;
	}
};

class graph {
public:
	list *adjList;
	int V;

	queue* q;
	int *visited;
	int *dist;

	graph(int v) {
		V = v;
		adjList = new list[V];
		q = new queue;
		visited = new int[V];
		dist = new int[V];

		for (int i = 0; i < V; i++)
			adjList[i].head = new node(i);

		//mark as unvisited
		for (int i = 0; i < V; i++)
			visited[i] = 0;
	}

	void addEdge(int v1, int v2) {
		node* old = adjList[v1].head->link;
		node *temp = new node(v2,old);
		adjList[v1].head->link = temp;
	}

	void printlist() {
		for (int i = 0; i < V; i++) {
			node *temp = adjList[i].head;
			while (temp) {
				cout << temp->data << " -> ";
				temp = temp->link;
			}
			cout << endl;
		}
	}

	void printq() {
		cout << "current queue has: ";
		q->print();
	}

	void bfs(int i) {
		q->enqueue(i);
		visited[i] = 1;
		dist[i] = 0;
		cout << i << " -> ";
		while (!q->isEmpty()) {
			int vertex = q->dequeue();
			node *cur = adjList[vertex].head;
			cur = cur->link;
			while (cur) {
				int v = cur->data;
				if (!visited[v]) {
					q->enqueue(v);
					cout << v << " -> ";
					visited[v] = 1;
					dist[v] = dist[vertex] + 1;
				}
				cur = cur->link;
			}
		
		}
	}

	int distance(int v1, int v2) {
		return dist[v2] - dist[v1];
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
		g->addEdge(v2, v1);
	}
	g->printlist();

	int s;
	in >> s;
	g->bfs(s);
	int v1, v2;
	in >> v1 >> v2;
	cout << endl << g->distance(v1, v2) << endl;
	return 0;
}