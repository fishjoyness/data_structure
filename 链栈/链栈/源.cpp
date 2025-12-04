#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
typedef int status;
typedef char elemtype;
const int ok = 1;
const int error = 0;
typedef struct stacknode {
	elemtype data;
	struct stacknode* next;
} stacknode, * linkstack;
status initstack(linkstack& s) {
	s = NULL;
	return ok;
}
status push(linkstack& s, elemtype e) {
	stacknode* p = new stacknode;
	if (!p) {
		return error;
	}
	p->data = e;
	p->next = s;
	s = p;//更新主头指针 s，让它指向我们的新节点 
	return ok;
}
status pop(linkstack& s, elemtype& e) {
	if (s == NULL) {
		return error;
	}
	e = s->data;
	stacknode* p = s;
	s->next = s;
	delete p;
	return ok;
}
using namespace std;
status print(linkstack s) {
	if (s == NULL) {
		cout << "栈为空";
		return error;
	}
	stacknode* p = s;
	while (p != NULL) {
		cout << p->data;
		p = p->next;
	}
	return ok;
}

status destorystack(linkstack& s) {
	stacknode* p = s;
	while (s != NULL) {
		p = s;
		s = s->next;
		delete p;
	}
	s = NULL;
	return error;
}

status gettop(linkstack s, elemtype& e) {
	if (s != NULL) {
		e = s->data;
		return ok;
	}
	return error;
}

