/*
Red-black trees:
Program to insert n elements into a red-black tree.
*/
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

enum {red, black};

class tree;
class node {
public:
	int data;
	int color;
	node *l, *r, *p;

	node(int val, node* parent) {
		data = val;
		color = red;
		p = parent;
		l = r = NULL;
	}

	void inorder() {
		if (l != NULL)
			l->inorder();
		cout << data << " ";
		if (r != NULL)
			r->inorder();
	}
	
	void preorder() {
		cout << data << " " << (color == black ? "(black)" : "(red)");
		if (l != NULL)
			l->preorder();
		if (r != NULL)
			r->preorder();
	}

	friend void l_rotate(tree*, node*);
	friend void r_rotate(tree*, node*);
};



class tree {
public:
	node *root;
	int count;

	friend void l_rotate(tree*, node*);
	friend void r_rotate(tree*, node*);

	tree(int r) {
		root = new node(r, NULL);
		count = 1;
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
		count++;
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
		if(count>2)
		  fix_insert(newnode);
		root->color = black;
	}

	void fix_insert(node *z) {
		while (z->p && z->p->color == red) {
				if (z->p == z->p->p->l) {
				node* y = z->p->p->r;
				if (y && y->color == red) {
					y->color = black;
					z->p->color = black;
					z->p->p->color = red;
					z = z->p->p;
				}
				else {
					if (z == z->p->r) {
						z = z->p;
						l_rotate(this, z);
					}
					z->p->color = black;
					z->p->p->color = red;
					r_rotate(this, z->p->p);						
				}
			} else {
				node* y = z->p->p->l;
				if (y && y->color == red) {
					y->color = black;
					z->p->color = black;
					z->p->p->color = red;
					z = z->p->p;
				}
				else {
					if (z == z->p->l) {
						z = z->p;
						r_rotate(this, z);
					}
					z->p->color = black;
					z->p->p->color = red;
					l_rotate(this, z->p->p);
				}
			}
		}
		root->color = black;
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
};

void l_rotate(tree* t, node* n) {
	node *b = n->r ? n->r->l : NULL,
		*y = n->r;

	if (n->p) {
		if (n == n->p->r)
			n->p->r = y;
		else
			n->p->l = y;
		y->p = n->p;
	}
	else {
		t->root = n->r;
	}

	if (y)
		y->l = n;
	n->p = y;
	n->r = b;
	if (b)
		b->p = n;
}

void r_rotate(tree* t, node* n) {
	node* b = n->l ? n->l->r : NULL,
		*y = n->l;

	if (n->p) {
		if (n == n->p->r)
			n->p->r = y;
		else
			n->p->l = y;
		y->p = n->p;
	}
	else
		t->root = n->l;
	if (y) {
		y->r = n;
	}
	n->p = y;
	n->l = b;
	if (b)
		b->p = n;
}

int main() {
	tree *t = new tree(20);
	t->insertNode(25);
	t->insertNode(14);
	t->insertNode(19);
	t->insertNode(5);
	t->insertNode(67);
	t->insertNode(35);
	t->insertNode(81);
	t->insertNode(17);
	t->preorder();
	cout << endl;
	t->inorder();
	cout << endl;
	return 0;
}