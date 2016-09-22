/* 
A program that implements a Binary search tree (BST) and performs the following operations:
1. Search the BST for an element.
2. Return the minimum and maximum elements in the BST.
3. Find the successor and predecessor of an element.
4. Height of a tree.
5. Deletes a node.
6. Finds the node at a particular position.
7. Finds the rank of a value in the BST.
*/
#include <iostream>
#include <fstream>
using namespace std;

class node {
public:
	int data;
	node *p;
	node *l, *r;
	int count; //statistic for select and rank.

	node(int data, node* parent) {
		this->data = data;
		p = parent;
		l = r = NULL;
		count = 1;
	}

	void inorder() {
		if (l != NULL)
			l->inorder();
		cout << data << " ";
		if (r != NULL)
			r->inorder();
	}

	void preorder() {
		cout << data << " ";
		if (l != NULL)
			l->preorder();
		if (r != NULL)
			r->preorder();
	}
};

class tree {
public:
	node *root;

	tree(int r) {
		root = new node(r, NULL);
	}

	//print in sorted order
	void inorder() {
		root->inorder();
	}

	void preorder() {
		root->preorder();
	}

	//insert nodes.
	void insertNode(int r) {
		node *temp = root;
		node *p = temp;
		while(temp) {
			p = temp;
			if (temp->data > r)
				temp = temp->l;
			else temp = temp->r;
		}
		node *newnode = new node(r, p);
		if (p->data > r)
			p->l = newnode;
		else
			p->r = newnode;
		while (p) {
			p->count++;
			p = p->p;
		}
	}

	//search node.
	node* search(int v) {
		node *temp = root;
		while (temp) {
			if (temp->data == v)
				return temp;
			else if (temp->data < v)
				temp = temp->r;
			else
				temp = temp->l;
		}
		return NULL;
	}

	//minimum node.
	node* min(node *n) {
		node* temp = n?n:root;
		node* p = NULL;
		while (temp) {
			p = temp;
			temp=temp->l;
		}
		return p;
	}

	//maximum node.
	node* max(node *n) {
		node* temp = n?n:root;
		node* p = NULL;
		while (temp) {
			p = temp;
			temp = temp->r;
		}
		return p;
	}

	//successor
	node* successor(int i) {
		node* n = search(i);
		if (n->r)
			return min(n->r);
	
		while (n) {
			if (!n->p)
				return NULL;
			if (n == n->p->l)
				return n->p;
			else
				n = n->p;
		}
		return NULL;
	}

	//predecessor.
	node* predecessor(int i) {
		node* n = search(i);
		if (n->l)
			return max(n->l);
		while (n) {
			if (!n->p)
				return NULL;
			if (n == n->p->r)
				return n->p;
			else n = n->p;
		}
		return NULL;
	}

	//helper function
	int max(int l, int r) {
		return l > r ? l : r;
	}

	//height
	int height(node* r) {
		if (r == NULL)
			return 0;
		return 1 + max(height(r->l), height(r->r));
	}

	//delete
	void del(int v) {
		node* n = search(v);
		int l = 0;
		if (!n->p || n == n->p->l )
			l = 1;
		if (!(n->l) && !(n->r)) {
			if (l)
				n->p->l = NULL;
			else
				n->p->r = NULL;
			delete(n);
		}
		else if (!(n->l)) {
			if (l)
				n->p->l = n->r;
			else
				n->p->r = n->r;
			delete(n);
		}
		else if (!(n->r)) {
			if (l)
				n->p->l = n->l;
			else
				n->p->r = n->l;
			delete(n);
		}
		else {
			node* s = predecessor(v);
			n->data = s->data;
			if (s == s->p->l)
				l = 1;
			else
				l = 0;
			if (l)
				s->p->l = s->r;
			else
				s->p->r = s->r;
			delete(s);
		}
		
	}

	//select node at index i
	node* select(node*r, int index) {
		if (index > r->count)
			return NULL;
		int rindex = (r->l?r->l->count:0) + 1; //index of node.
		if (rindex == index)
			return r;
		if (rindex > index)
			return select(r->l, index);
		if (rindex < index) {
			int s_node = r->l->count + 1;
			index -= s_node;
			return select(r->r, index);
		}
		return NULL;
	}

	//find rank of an element.
	int rank(node *n, int val) {
		int rank = 1;
		while (n) {
			if (val < n->data)
				n = n->l;
			else if (val > n->data) {
				rank += n->l->count + 1;
				n = n->r;
			}
			else
				return rank + (n->l?n->l->count:0);
		}
	}
};

int main() {
	ifstream cin;
	cin.open("bst_input.txt");
	int nodes;
	cin >> nodes;
	int r;
	cin >> r;
	tree *t = new tree(r);

	for (int i = 1; i < nodes; i++) {
		cin >> r;
		t->insertNode(r);
	}

	int nSearch;
	cin >> nSearch;
	cout << endl;
	for (int i = 0; i < nSearch; i++) {
		int sv;
		cin >> sv;
		cout << sv << ":";
		t->search(sv) ? cout << "Success\n" : cout << "Fail\n";
	}
	cout << "\nMin: " << t->min(NULL)->data<<endl;
	cout << "Max: " << t->max(NULL)->data << endl;
	int nSucessor;
	cin >> nSucessor;
	for (int i = 0; i < nSucessor; i++) {
		int v;
		cin >> v;
		node* s = t->successor(v);
		cout << "Succesor of " << v << ":" <<(s?s->data:-99)<<endl;
	}
	int nPred;
	cin >> nPred;
	for (int i = 0; i < nPred; i++) {
		int v;
		cin >> v;
		node *p = t->predecessor(v);
		cout << "Predecessor of " << v << ":" << (p?p->data:-99) << endl;
	}
	cout << "Height: " << t->height(t->root)-1<<endl;
	int nDel;
	cin >> nDel;
	for (int i = 0; i < nDel; i++) {
		int v;
		cin >> v;
		t->del(v);
		t->preorder();
	}

	int nSel;
	cin >> nSel;
	for (int i = 0; i < nSel; i++) {
		int v;
		cin >> v;
		node* r = t->select(t->root, v);
		cout << "Node at position "<<v<<":" << (r?r->data:-99)<<endl;
	}
	int nRank;
	cin >> nRank;
	for (int i = 0; i < nSel; i++) {
		int v;
		cin >> v;
		int r = t->rank(t->root, v);
		cout << "Rank of " << v << ":" << r << endl;
	}
	return 0;
}