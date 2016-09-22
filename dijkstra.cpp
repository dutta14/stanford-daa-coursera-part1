/*
Program to implement Dijkstra's algorithm using min-heaps.
*/
#include <iostream>
#include <fstream>
using namespace std;

class vertex {
public:
	int i;
	int key;
	int visited;

	vertex(int index) {
		i = index;
		key = INT_MAX;
		visited = 0;
	}
};

class edge {
public:
	vertex *s, *d;
	int w;

	edge(vertex *src, vertex *dst, int wt) {
		s = src;
		d = dst;
		w = wt;
	}
};

void computeCosts(vertex **vset, edge **eset, int m) {
	for (int i = 0; i < m; i++) {
		edge *e = eset[i];
		if (e->s->visited && !(e->d->visited)) {
			int sw = e->s->key, w = e->w;
			if (e->d->key > sw + w)
				e->d->key = sw + w;
		}
	}
}

void heapify(vertex **vset, int i, int n) {
	int l = 2 * i, r = 2 * i + 1;
	int m = 0;
	if (l <= n && r <= n) {
		if (vset[l]->key < vset[r]->key)
			m = l;
		else
			m = r;

		if (vset[i]->key > vset[m]->key) {
			swap(vset[i], vset[m]);
			heapify(vset, m, n);
		}
	}

}

int main() {
	ifstream in;
	in.open("dijkstra_in.txt");

	int n;
	in >> n;
	vertex **vset = new vertex*[n + 1];
	for (int i = 1; i <= n; i++)
		vset[i] = new vertex(i);
	int V = n; //book-keeping for printing.

	int m;
	in >> m;
	edge **eset = new edge*[m];
	for (int i = 0; i < m; i++) {
		int s, d, w;
		in >> s >> d >> w;
		eset[i] = new edge(vset[s], vset[d], w);
	}

	int s;
	in >> s;

	//1. set dist=0 for src and add it to A.
	vset[s]->key = 0;
	vset[s]->visited = 1;
	swap(vset[s], vset[n]);
	n--;

	//2.build initial heap.
	computeCosts(vset, eset, m);
	for (int i = n / 2; i > 0; i--)
		heapify(vset, i, n);

	for (int i = n; i > 0; i--) {
		vertex *v = vset[1];
		vset[1]->visited = 1;
		swap(vset[1], vset[n]);
		n--;
		computeCosts(vset, eset, m);
		heapify(vset, 1, n);
	}

	for (int i = V; i > 0; i--)
		cout << vset[i]->i << ":" << vset[i]->key << endl;
}