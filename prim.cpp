/*
Program that runs Prim's algorithm from a randomly selected vertex to find
the minimum spanning tree for that graph.
*/
#include <iostream>
#include <fstream>
using namespace std;

class edge;

class vertex {
public:
	int i;
	edge* e;
	int w;
	vertex() {}

	vertex(int j) {
		i = j;
		e = NULL;
		w = INT_MAX;
	}
};



class edge {
public:
	vertex *s, *d;
	int w;

	edge() {
		s = d = NULL;
		w = 0;
	}

	edge(vertex* src, vertex* dst, int wt) {
		s = src;
		d = dst;
		w = wt;
	}

	friend ostream& operator<<(ostream& os, const edge& dt);
};

ostream& operator<<(ostream& os, const edge& dt)
{
	os << '(' << dt.s->i << ',' << dt.d->i << ')';
	return os;
}

void bubbledown(vertex **a, int n) {
	int i = 1;
	while (i <= n) {
		int l = 2 * i, r = 2*i + 1;
		int m = a[l] < a[r] ? l : r;
		if (a[i] < a[m])
			break;
		else {
			swap(a[i], a[m]);
			i = m;
		}
	}
}

void heapify(vertex **a, int i) {
	while (i > 1) {
		if (a[i]->w < a[i / 2]->w) {
			swap(a[i], a[i / 2]);
			i = i / 2;
		}
		else
			break;
	}
}

int *visited;

vertex** v;
edge** e;

void findMinEdges(int s, int m) {
	for (int i = 0; i < m; i++) {
		edge* edge = e[i];
		int s1 = e[i]->s->i;
		int d = e[i]->d->i;
		int w = e[i]->w;

		if (s == d && !visited[s1]) {
			swap(s1, d);
		}

		if (s == s1 && !visited[d]) {
			if (v[d]->e == NULL) {
				v[d]->e = edge;
				v[d]->w = edge->w;
			}
			else if (v[d]->e->w > w) {
				v[d]->e = edge;
				v[d]->w = edge->w;
			}
		}
	}
}

void printHeap(int n) {
	for (int i = 1; i <= n; i++)
		cout << v[i]->i << "("<<v[i]->w<<") ";
	cout << endl;
}

int main() {
	ifstream in;
	in.open("prims_in.txt");
	
	int n, m;
	in >> n >> m;
	int l = n;
	v = new vertex*[n+1];
	visited = new int[n+1];
	for (int i = 1; i <= n; i++) {
		v[i] = new vertex(i);
		visited[i] = 0;
	}

	e = new edge*[m];

	for (int i = 0; i < m; i++) {
		int s, d, w;
		in >> s >> d >> w;
		e[i] = new edge(v[s], v[d], w);
	}

	//randomly select a vertex.
	int r = 1;// rand() % n;
	visited[r] = 1;

	findMinEdges(r,m);
	swap(v[r], v[n]);
	n--;

	for (int i = 1; i <= n; i++) {
		heapify(v, i);
	}

	cout << "after first heapify: ";
	printHeap(n);

	for (int i = 1; i <l; i++) {
		cout << "n=" << n << endl;
		vertex* vt = v[1];
		cout << *(vt->e) << endl;
		visited[vt->i] = 1;
		findMinEdges(vt->i, m);

		swap(v[1], v[n]);
		bubbledown(v,--n);
		printHeap(n);
	}

	return 0;
}

