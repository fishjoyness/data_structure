#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int KeyType;
typedef struct {
    KeyType key;
} RedType;

typedef struct {
    RedType r[MAXSIZE + 1]; // r[0]闲置
    int length;
} SqList;

void Swap(RedType* a, RedType* b) {
    RedType temp = *a;
    *a = *b;
    *b = temp;
}

void PrintList(SqList L) {
    for (int i = 1; i <= L.length; i++) printf("%d ", L.r[i].key);
    printf("\n");
}

// --- (1) 冒泡排序 ---
void BubbleSort(SqList* L) {
    int m, j, flag;
    RedType t;
    // m代表需要进行冒泡的趟数，共n-1趟
    for (m = 1; m <= L->length - 1; m++) {
        flag = 0; // flag用于标记本趟是否发生了交换
        // j从1开始，到 length-m 结束（因为每趟结束后最大的元素就像气泡一样冒到了最后）
        for (j = 1; j <= L->length - m; j++) {
            if (L->r[j].key > L->r[j + 1].key) {
                // 逆序则交换
                t = L->r[j]; L->r[j] = L->r[j + 1]; L->r[j + 1] = t;
                flag = 1;
            }
        }
        // 如果本趟没有发生任何交换，说明序列已经有序，提前结束算法
        if (!flag) return;
    }
}

// --- (2) 快速排序 ---
// Partition函数：选取一个枢轴，将表划分为左右两个子表，左边小，右边大
int Partition(SqList* L, int low, int high) {
    KeyType pivotkey = L->r[low].key; // 严版教材此处通常取当前子表的第一个记录作枢轴
    while (low < high) {
        // 从右向左扫描，找到比pivotkey小的记录
        while (low < high && L->r[high].key >= pivotkey) --high;
        Swap(&L->r[low], &L->r[high]); // 将小记录移到低端
        // 从左向右扫描，找到比pivotkey大的记录
        while (low < high && L->r[low].key <= pivotkey) ++low;
        Swap(&L->r[low], &L->r[high]); // 将大记录移到高端
    }
    return low; // 此时low==high，返回枢轴最终所在位置
}

void QSort(SqList* L, int low, int high) {
    if (low < high) {
        int pivotloc = Partition(L, low, high); // 将L.r[low..high]一分为二
        QSort(L, low, pivotloc - 1);  // 递归排序左子表
        QSort(L, pivotloc + 1, high); // 递归排序右子表
    }
}

void QuickSort(SqList* L) {
    QSort(L, 1, L->length);
}

int main() {
    SqList L;
    int data[] = { 0, 49, 38, 65, 97, 76, 13, 27 };
    L.length = 7;
    for (int i = 0; i <= L.length; i++) L.r[i].key = data[i];

    printf("交换排序\n原始: "); PrintList(L);
    SqList L1 = L; BubbleSort(&L1);
    printf("冒泡: "); PrintList(L1);
    SqList L2 = L; QuickSort(&L2);
    printf("快速: "); PrintList(L2);
    return 0;
}
