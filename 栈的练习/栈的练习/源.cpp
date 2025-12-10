#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdlib>
using namespace std;
#define MAXQSIZE 1001
#define OK 1
#define ERROR 0
#define OVERFLOE -2
typedef int status;
typedef char qelemtype;

typedef struct {
	qelemtype* base;//指向数组第一个元素的指针,队列是租用一块内存空间来用的，以此为参照物
//base在创建之后就不变了
	int front;//它指向队列的队首元素，也就是下一个要被出队（删除）的元素
	//取走一个元素的时候，头指针先后移一位，在循环的时候会绕回数组的开头
	int rear;
}sqqueue;
//初始化
status initqueue(sqqueue& q) {
	q.base = new  qelemtype[MAXQSIZE];
	if (!q.base) exit(OVERFLOW);
	q.front = q.rear = 0;
	return OK;
}
//当执行 Q.front = Q.rear = 0; 时，front 指针（以及 rear 指针）
// 指向的是数组的第 0 个元素， 也就是我们常说的 arr[0] 这个位置

//入队
status enqueue(sqqueue& q, qelemtype e) {
	if ((q.rear + 1) % MAXQSIZE == q.front)
		return ERROR;
	q.base[q.rear] = e;//rear 指向队尾元素的下一个位
	q.rear = (q.rear + 1) % MAXQSIZE;
	return OK;
}
//队空条件：front == rear （头尾指针重合）
//队满条件：(rear + 1) % capacity == front ,尾指针再走一步就追上头指针了
//rear 指针就指向这个恒定的空位

//入队
status dequeue(sqqueue& q, qelemtype& e) {
	if (q.front == q.rear)
		return ERROR;
	e = q.base[q.front];
	q.front = (q.front + 1) % MAXQSIZE;
	return OK;
}

//打印
status printqueue(sqqueue q) {
	if (q.front = q.rear) {
		cout << "队为空" << '\n';
		return ERROR;
	}
	int p = q.front;
	while (p != q.rear) {//出现了问题
		cout << q.base[p];
		p = (p + 1) % MAXQSIZE;
	}
	return OK;
}

//销毁
status destoryqueue(sqqueue& q) {
	if (q.base) {
		delete[]q.base;
		q.base = NULL;
	}
	q.front = q.rear = 0;
	return OK;
}
//取队头元素
status gethead(sqqueue q, qelemtype& e) {
	if (q.front == q.rear) {
		return ERROR;
	}
	e = q.base[q.front];
	return OK;
}
//求队列长度
int queuelength(sqqueue q) {
	return (q.front - q.rear + MAXQSIZE) % MAXQSIZE;
}
//新建一个队列
sqqueue q;
