#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef int KeyType;
typedef struct {
    KeyType key;
} RedType;

typedef struct {
    RedType r[MAXSIZE + 1];
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

// --- (3) 简单选择排序 ---
void SelectSort(SqList* L) {
    int i, j, k;
    // 共进行n-1趟选择，第i趟将第i小的元素放到位置i
    for (i = 1; i < L->length; i++) {
        k = i; // k用于记录当前无序区中最小元素的下标，初始设为i
        // 在 L.r[i..length] 中选择关键字最小的记录
        for (j = i + 1; j <= L->length; j++) {
            if (L->r[j].key < L->r[k].key) k = j; // 发现更小的记录，更新k
        }
        // 如果最小元素不在位置i，则交换
        if (k != i) {
            Swap(&L->r[i], &L->r[k]);
        }
    }
}

// --- (4) 堆排序 ---
// HeapAdjust：堆调整的核心函数。
// 假设 r[s+1..m] 已经是大顶堆，将 r[s..m] 调整为以 r[s] 为根的大顶堆
void HeapAdjust(SqList* L, int s, int m) {
    RedType rc = L->r[s]; // 暂存根节点记录
    int j;
    // j初始化为s的左孩子(j=2s)，沿key较大的孩子节点向下筛选
    for (j = 2 * s; j <= m; j *= 2) {
        // 如果左孩子小于右孩子，j指向右孩子（j < m 保证有右兄弟）
        if (j < m&& L->r[j].key < L->r[j + 1].key) j++;
        // 如果rc（原根节点）比较大的孩子还大，说明满足大顶堆定义，无需调整
        if (rc.key >= L->r[j].key) break;
        // 否则，将大孩子上移
        L->r[s] = L->r[j];
        s = j; // s更新为孩子的位置，继续向下筛选
    }
    L->r[s] = rc; // 将rc放入最终合适的位置
}

void HeapSort(SqList* L) {
    int i;
    // 1. 初始建堆：从最后一个非叶子节点(length/2)开始，向前依次调整
    for (i = L->length / 2; i > 0; i--) {
        HeapAdjust(L, i, L->length);
    }
    // 2. 逐个输出堆顶元素（最大值），并调整剩余元素为堆
    for (i = L->length; i > 1; i--) {
        Swap(&L->r[1], &L->r[i]); // 将堆顶记录(最大值)与当前末尾记录交换
        HeapAdjust(L, 1, i - 1);  // 将剩下的 i-1 个记录重新调整为大顶堆
    }
}

int main() {
    SqList L;
    int data[] = { 0, 49, 38, 65, 97, 76, 13, 27 };
    L.length = 7;
    for (int i = 0; i <= L.length; i++) L.r[i].key = data[i];

    printf("选择排序\n原始: "); PrintList(L);
    SqList L1 = L; SelectSort(&L1);
    printf("简选: "); PrintList(L1);
    SqList L2 = L; HeapSort(&L2);
    printf("堆排: "); PrintList(L2);
    return 0;
}
