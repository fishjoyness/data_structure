#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdlib>
using namespace std;

#define MAXQSIZE 1001  //队列可能达到的最大长度
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char QElemType; // 假设队列存储字符

// 循环队列结构定义
typedef struct {
    QElemType* base; //存储空间的基地址
    int front;       //头指针
    int rear;        //尾指针
} SqQueue;

// 构造一个空队列Q
Status InitQueue(SqQueue& Q) {
    Q.base = new QElemType[MAXQSIZE];
    if (!Q.base) exit(OVERFLOW);
    Q.front = Q.rear = 0;
    return OK;
}

// 插入元素e为Q的新的队尾元素
Status EnQueue(SqQueue& Q, QElemType e) {
    if ((Q.rear + 1) % MAXQSIZE == Q.front)
        return ERROR; // 队列满
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

// 删除Q的队头元素，用e返回其值
Status DeQueue(SqQueue& Q, QElemType& e) {
    if (Q.front == Q.rear) return ERROR; // 队列空
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

// 返回Q的队头元素，不修改队头指针
Status GetHead(SqQueue Q, QElemType& e) {
    if (Q.front == Q.rear) return ERROR;
    e = Q.base[Q.front];
    return OK;
}

// 求队列长度
int QueueLength(SqQueue Q) {
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// 打印队列元素
Status PrintQueue(SqQueue Q) {
    if (Q.front == Q.rear) {
        cout << "队列为空" << endl;
        return ERROR;
    }
    cout << "队列元素: ";
    int p = Q.front;
    while (p != Q.rear) {
        cout << Q.base[p] << " ";
        p = (p + 1) % MAXQSIZE;
    }
    cout << endl;
    return OK;
}

// 销毁队列
Status DestroyQueue(SqQueue& Q) {
    if (Q.base) {
        delete[] Q.base;
        Q.base = NULL;
    }
    Q.front = Q.rear = 0;
    return OK;
}

// 主函数，用于测试循环队列
int main() {
    SqQueue Q;
    cout << "循环队列测试" << endl;

    // 1. 初始化
    cout << "初始化队列" << endl;
    if (InitQueue(Q) == OK) {
        cout << "初始化成功" << endl;
    }
    PrintQueue(Q);
    cout << "   当前队列长度: " << QueueLength(Q) << endl;

    // 2. 入队
    cout << "\n依次入队 A, B, C" << endl;
    EnQueue(Q, 'A');
    EnQueue(Q, 'B');
    EnQueue(Q, 'C');
    PrintQueue(Q);
    cout << "   当前队列长度: " << QueueLength(Q) << endl;

    // 3. 取队头元素
    cout << "\n获取队头元素..." << endl;
    QElemType headElem;
    if (GetHead(Q, headElem) == OK) {
        cout << "队头元素是: " << headElem << endl;
    }

    // 4. 出队
    cout << "\n执行一次出队" << endl;
    QElemType e;
    if (DeQueue(Q, e) == OK) {
        cout << "出队元素是: " << e << endl;
    }
    PrintQueue(Q);
    cout << "当前队列长度: " << QueueLength(Q) << endl;

    // 5. 销毁
    cout << "\n销毁队列" << endl;
    DestroyQueue(Q);
    cout << "队列已销毁。" << endl;

    return 0;
}
