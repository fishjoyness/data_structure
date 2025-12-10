#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cctype>
using namespace std;

#define MAXSIZE 1001
#define OK 1
#define ERROR 0
typedef int Status;
typedef char QElemType;

// 栈定义（用于回文判断）
typedef struct {
    QElemType data[MAXSIZE];
    int top;
} SqStack;

// 链队列定义（复用之前的定义）
typedef struct QNode {
    QElemType data;
    struct QNode* next;
} QNode, * QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

// 栈操作
Status InitStack(SqStack& S) {
    S.top = -1;
    return OK;
}

Status Push(SqStack& S, QElemType e) {
    if (S.top >= MAXSIZE - 1) return ERROR;
    S.data[++S.top] = e;
    return OK;
}

Status Pop(SqStack& S, QElemType& e) {
    if (S.top == -1) return ERROR;
    e = S.data[S.top--];
    return OK;
}

// 队列操作（只实现需要的）
Status InitQueue(LinkQueue& Q) {
    Q.front = Q.rear = new QNode;
    Q.front->next = NULL;
    return OK;
}

Status EnQueue(LinkQueue& Q, QElemType e) {
    QueuePtr p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

Status DeQueue(LinkQueue& Q, QElemType& e) {
    if (Q.front == Q.rear) return ERROR;
    QueuePtr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    delete p;
    return OK;
}

// 回文判断核心函数
bool IsPalindrome(char str[]) {
    SqStack S;
    LinkQueue Q;
    QElemType stackChar, queueChar;
    int i = 0;

    InitStack(S);
    InitQueue(Q);

    // 把字符串中的字符逐个分别存入队列和堆栈
    // 忽略空格和标点，统一转为小写
    while (str[i] != '\0') {
        if (isalnum(str[i])) {
            char c = tolower(str[i]);
            Push(S, c);
            EnQueue(Q, c);
        }
        i++;
    }

    // 逐个比较出队字符和出栈字符是否相等
    while (S.top != -1) {
        Pop(S, stackChar);
        DeQueue(Q, queueChar);
        if (stackChar != queueChar) {
            // 清理队列内存
            while (Q.front) {
                Q.rear = Q.front->next;
                delete Q.front;
                Q.front = Q.rear;
            }
            return false;
        }
    }

    // 清理队列内存
    while (Q.front) {
        Q.rear = Q.front->next;
        delete Q.front;
        Q.front = Q.rear;
    }
    return true;
}

// 主函数，用于测试回文判断
int main() {
    char str[256];
    cout << "回文判断测试" << endl;
    cout << "请输入一个字符串: ";
    cin.getline(str, 256);

    if (IsPalindrome(str)) {
        cout << "结果: \"" << str << "\" 是回文" << endl;
    }
    else {
        cout << "结果: \"" << str << "\" 不是回文" << endl;
    }

    return 0;
}
