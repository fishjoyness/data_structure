#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
typedef struct bitnode{
	char data;
	struct bitnode* lchild, * rchild;
}bitnode,*bitree;

typedef struct {
	int weight;
	int parent, lchild, rchild;
}htnode,huffmantree;

void createbitree(bitree& t) {
	char ch;
	cin >> ch;
	if (ch == '#') {
		t = NULL;
	}
	else {
		t = new bitnode;
		t->data = ch;
		createbitree(t->lchild);
		createbitree(t->rchild);
	}
}

void preordertraverse(bitree t) {
	if (t) {
		cout << t->data << " ";
		preordertraverse(t->lchild);
		preordertraverse(t->rchild);
	}
}
