#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
typedef int Status;
typedef char QElemType; // 假设队列存储字符

// 链队列结点定义
typedef struct QNode {
    QElemType data;
    struct QNode* next;
} QNode, * QueuePtr;

// 链队列定义
typedef struct {
    QueuePtr front; //队头指针
    QueuePtr rear;  //队尾指针
} LinkQueue;

// 构造一个空队列Q
Status InitQueue(LinkQueue& Q) {
    Q.front = Q.rear = new QNode; // 生成新结点作为头结点
    Q.front->next = NULL;          // 头结点的指针域置空
    return OK;
}

// 插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue& Q, QElemType e) {
    QueuePtr p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

// 删除Q的队头元素，用e返回其值
Status DeQueue(LinkQueue& Q, QElemType& e) {
    if (Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next; // p指向队头元素
    e = p->data;                 // e保存队头元素的值
    Q.front->next = p->next;     // 修改头结点的指针域
    if (Q.rear == p)             // 最后一个元素被删，队尾指针指向头结点
        Q.rear = Q.front;
    delete p;                    // 释放原队头元素的空间
    return OK;
}

// 返回Q的队头元素，不修改队头指针
QElemType GetHead(LinkQueue Q) {
    if (Q.front != Q.rear)
        return Q.front->next->data;
    return ERROR; // 队列为空
}

// 求队列长度
int QueueLength(LinkQueue Q) {
    int len = 0;
    QueuePtr p = Q.front->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

// 打印队列元素
Status PrintQueue(LinkQueue Q) {
    if (Q.front == Q.rear) {
        cout << "队列为空" << endl;
        return ERROR;
    }
    cout << "队列元素: ";
    QueuePtr p = Q.front->next;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
    return OK;
}

// 销毁队列
Status DestroyQueue(LinkQueue& Q) {
    while (Q.front) {
        Q.rear = Q.front->next;
        delete Q.front;
        Q.front = Q.rear;
    }
    return OK;
}

// 主函数，用于测试链队列
int main() {
    LinkQueue Q;
    cout << "链队列测试" << endl;

    // 1. 初始化
    cout << "1. 初始化队列" << endl;
    InitQueue(Q);
    cout << "初始化成功" << endl;
    PrintQueue(Q);
    cout << "当前队列长度: " << QueueLength(Q) << endl;

    // 2. 入队
    cout << "\n2. 依次入队 X, Y, Z" << endl;
    EnQueue(Q, 'X');
    EnQueue(Q, 'Y');
    EnQueue(Q, 'Z');
    PrintQueue(Q);
    cout << "当前队列长度: " << QueueLength(Q) << endl;

    // 3. 取队头元素
    cout << "\n3. 获取队头元素" << endl;
    QElemType headElem = GetHead(Q);
    if (headElem != ERROR) {
        cout << "队头元素是: " << headElem << endl;
    }

    // 4. 出队
    cout << "\n4. 执行一次出队" << endl;
    QElemType e;
    if (DeQueue(Q, e) == OK) {
        cout << "出队元素是: " << e << endl;
    }
    PrintQueue(Q);
    cout << "当前队列长度: " << QueueLength(Q) << endl;

    // 5. 销毁
    cout << "\n5. 销毁队列" << endl;
    DestroyQueue(Q);
    cout << "队列已销毁。" << endl;

    return 0;
}
