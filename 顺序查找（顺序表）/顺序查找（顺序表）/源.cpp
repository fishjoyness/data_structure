#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

// --- 宏定义 ---
#define MAX_SIZE 100       // 顺序表的最大长度
#define OK 1
#define ERROR 0

// --- 数据类型定义 ---
typedef int KeyType;        // 定义关键字类型为整型
typedef int Status;         // 函数返回状态

// 1. 顺序表结构定义
typedef struct {
    KeyType elem[MAX_SIZE]; // 存储数据元素，0号单元留作哨兵
    int length;             // 当前长度
} SeqList;

// 2. 链表结点结构定义
typedef struct LNode {
    KeyType data;           // 数据域
    struct LNode* next;     // 指针域
} LNode, * LinkList;


// (1) 顺序查找（顺序表）
int SeqSearch(SeqList L, KeyType key) {
    L.elem[0] = key;                     // 【哨兵】将待查值存入下标0的位置
    for (int i = L.length; i >= 1; --i)  // 从表尾开始向前遍历
        if (L.elem[i] == key)            // 判断当前元素是否等于key
            return i;                    // 找到则返回下标i
    return 0;                            // 未找到，返回0
}

// (2) 顺序查找（链表）
LNode* LocateElem_L(LinkList L, KeyType key) {
    LNode* p = L->next;                  // 初始化p，指向首元结点
    while (p && p->data != key)         // p不为空且未找到时继续循环
        p = p->next;                    // 指针后移
    return p;                           // 返回结点指针（找到为目标结点，未找到为NULL）
}

// (3) 折半查找（顺序表 - 要求表有序）
int BinarySearch(SeqList L, KeyType key) {
    int low = 1, high = L.length;        // 初始化查找区间上、下界
    while (low <= high) {                // 区间有效时循环
        int mid = (low + high) / 2;     // 计算中间位置
        if (L.elem[mid] == key)          // 找到目标值
            return mid;                  // 返回下标
        else if (L.elem[mid] < key)      // 中间值小于关键字
            low = mid + 1;               // 查找右半区
        else                             // 中间值大于关键字
            high = mid - 1;              // 查找左半区
    }
    return 0;                            // 查找失败
}


int main() {
    // --- 测试顺序查找和折半查找 ---
    SeqList L;
    // 注意：严蔚敏教材中顺序表通常从下标1开始存储有效数据
    L.length = 10;
    // 初始化有序数据，用于测试折半查找：1, 3, 5, ..., 19
    for (int j = 1; j <= L.length; j++) {
        L.elem[j] = 2 * j - 1;
    }

    int key1 = 7;
    printf("顺序表测试\n");

    // 测试顺序查找
    int pos_seq = SeqSearch(L, key1);
    if (pos_seq) printf("顺序查找 %d: 找到，下标为 %d\n", key1, pos_seq);
    else printf("顺序查找 %d: 未找到\n", key1);

    // 测试折半查找
    int pos_bin = BinarySearch(L, key1);
    if (pos_bin) printf("折半查找 %d: 找到，下标为 %d\n", key1, pos_bin);
    else printf("折半查找 %d: 未找到\n", key1);

    printf("\n链表测试\n");
    // --- 测试链表顺序查找 ---
    LinkList head = (LNode*)malloc(sizeof(LNode)); // 创建头结点
    head->next = NULL;
    LNode* tail = head;

    // 尾插法创建链表，存入数据：2, 4, 6, 8, 10
    for (int k = 1; k <= 5; k++) {
        LNode* s = (LNode*)malloc(sizeof(LNode));
        s->data = 2 * k;
        s->next = NULL;
        tail->next = s;
        tail = s;
    }

    int key2 = 8;
    LNode* result = LocateElem_L(head, key2);
    if (result) printf("链表查找 %d: 找到，结点值为 %d\n", key2, result->data);
    else printf("链表查找 %d: 未找到\n", key2);

    // 释放链表内存（简单处理）
    while (head) {
        LNode* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
