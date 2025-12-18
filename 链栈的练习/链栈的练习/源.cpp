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
	queueptr p = q.front->next;//用p来存储对头的元素
	e = p->data;
	q.front->next = p->next;//进行连接操作
	delete p;
	return OK;
}

//打印
//链队列里面front：它是一个指针，永远指向头节点。
// 头节点本身不存储任何有效数据，它的 next 指针才指向真正的队头元素。
//rear：它也是一个指针，永远指向队尾的最后一个有效元素节点。
//顺序队列里面front：指向队头元素的索引。
//rear：指向队尾元素的下一个位置的索引
//在链队列里，front 和 rear 通常不直接装元素，
// 而是作为指针，指向装元素的节点。
// 在顺序队列里，它们是数组的索引，直接参与定位元素。
status printqueue(linkqueue q) {
	if (q.front = q.rear) {
		cout << "队列空" << '\n';
		return ERROR;
	}
	queueptr p = q.front->next;
	while (p) {
		cout << p->data;
		p = p->next;//用于不连续的空间，如链表
		//p++用于连续的数组空间
	}
	return OK;
}

//销毁
// 循环结束后，Q.front 已经是 NULL 了
status destoryqueuqe(linkqueue& q) {
	while (q.front) {

	}
}