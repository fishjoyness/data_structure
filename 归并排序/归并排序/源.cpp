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

void PrintList(SqList L) {
    for (int i = 1; i <= L.length; i++) printf("%d ", L.r[i].key);
    printf("\n");
}

// --- (5) 归并排序 ---
// Merge：将两个有序表 SR[i..m] 和 SR[m+1..n] 归并为一个有序表 TR[i..n]
void Merge(RedType SR[], RedType TR[], int i, int m, int n) {
    int j, k, l;
    // k指向TR中待存放的位置，初始为i
    // j指向第二个有序表的首元素，初始为m+1
    for (j = m + 1, k = i; i <= m && j <= n; k++) {
        // 比较SR两端的首元素，取较小者放入TR，并移动指针
        if (SR[i].key <= SR[j].key) TR[k] = SR[i++];
        else TR[k] = SR[j++];
    }
    // 如果第一个有序表 SR[i..m] 没有处理完，将剩余部分复制到TR
    if (i <= m) {
        for (l = 0; l <= m - i; l++) TR[k + l] = SR[i + l];
    }
    // 如果第二个有序表 SR[j..n] 没有处理完，将剩余部分复制到TR
    if (j <= n) {
        for (l = 0; l <= n - j; l++) TR[k + l] = SR[j + l];
    }
}

// MSort：递归地将 SR[s..t] 归并排序为 TR1[s..t]
void MSort(RedType SR[], RedType TR1[], int s, int t) {
    int m;
    RedType TR2[MAXSIZE + 1]; // TR2作为辅助存储空间
    if (s == t) {
        TR1[s] = SR[s]; // 递归终止条件：只有一个元素，视为有序，直接赋值
    }
    else {
        m = (s + t) / 2; // 将当前序列一分为二
        MSort(SR, TR2, s, m);      // 递归将左半部分排序，结果存入TR2
        MSort(SR, TR2, m + 1, t);  // 递归将右半部分排序，结果存入TR2
        Merge(TR2, TR1, s, m, t);  // 将TR2中已排序的左右两部分合并到TR1
    }
}

void MergeSort(SqList* L) {
    MSort(L->r, L->r, 1, L->length);
}

int main() {
    SqList L;
    int data[] = { 0, 49, 38, 65, 97, 76, 13, 27 };
    L.length = 7;
    for (int i = 0; i <= L.length; i++) L.r[i].key = data[i];

    printf("归并排序\n原始: "); PrintList(L);
    SqList L1 = L; MergeSort(&L1);
    printf("归并: "); PrintList(L1);
    return 0;
}
