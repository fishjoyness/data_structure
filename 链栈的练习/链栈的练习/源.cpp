#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#define OK 1
#define ERROR -2
typedef int status;
typedef char qelemtype;

//链队列的节点
typedef struct qnode {
	qelemtype data;
	struct qnode* next;
}qnode,*queueptr;
//在队尾入队”和“在队头出队

//链队列的定义
typedef struct {
	queueptr front;
	queueptr rear;
}linkqueue;

//初始化
status initqueue(linkqueue& q) {
	q.front = q.rear = new qnode;
	q.front->next = NULL;
	return OK;
}

//入栈
status enqueue(linkqueue& q, qelemtype e) {
	queueptr p = new qnode;
	p->data = e;
	p->next = NULL;
	q.rear->next = p;
	q.rear = p;
	return OK;
}

//出栈
status dequeue(linkqueue& q, qelemtype& e) {
	if (q.front == q.rear)
		return ERROR;
	queueptr p = q.front->next;
	e = p->data;

}