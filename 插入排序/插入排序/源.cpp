#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm> 
using namespace std;

#define MAX_SIZE 100
typedef int KeyType; // 使关键字类型为整型
typedef int Status;


typedef struct {
    KeyType elem[MAX_SIZE]; // elem[0]通常作哨兵或闲置，数据从elem[1]开始
    int length;             // 顺序表长度
} Sqlist;

// (1) 直接插入排序
void InsertSort(Sqlist& L) {
    // 算法10.1
    // 默认elem[1]是有序的，所以从elem[2]开始遍历整个表
    for (int i = 2; i <= L.length; ++i) {
        // 判断当前元素是否小于前一个元素，如果小于则需要插入
        if (L.elem[i] < L.elem[i - 1]) {
            L.elem[0] = L.elem[i]; // 【哨兵】将当前元素暂存到elem[0]，防止后移时被覆盖，同时也作为循环结束的标志
            int j;
            // 内层循环：从当前元素的前一个位置开始，向前寻找插入位置
            // 只要哨兵值（待插值）小于当前比较值elem[j]，就继续向前找
            for (j = i - 1; L.elem[0] < L.elem[j]; --j)
                L.elem[j + 1] = L.elem[j]; // 将大于待插值的元素向后挪一位
            L.elem[j + 1] = L.elem[0];     // 循环结束，j+1就是插入位置，将哨兵值填入
        }
    }
}

// (2) 折半插入排序
void BInsertSort(Sqlist& L) {
    // 算法10.2
    // 折半插入排序仅在查找插入位置时使用折半查找，移动次数与直接插入排序相同
    for (int i = 2; i <= L.length; ++i) {
        L.elem[0] = L.elem[i]; // 将待插入元素暂存到哨兵单元
        int low = 1, high = i - 1; // 设置折半查找的初始区间：[1, i-1]

        while (low <= high) {      // 当查找区间有效时进行循环
            int mid = (low + high) / 2; // 取中间位置
            if (L.elem[0] < L.elem[mid]) // 如果待插值小于中间值
                high = mid - 1;     // 插入点在左半区，调整上限high
            else                    // 如果待插值大于等于中间值
                low = mid + 1;      // 插入点在右半区（包含中间位置），调整下限low
        }                           // 循环结束后，low即为第一个大于待插值的位置（插入点）

        // 统一后移元素
        for (int j = i - 1; j >= low; --j)
            L.elem[j + 1] = L.elem[j]; // 元素向后挪一位
        L.elem[low] = L.elem[0];       // 将待插元素插入到low位置
    }
}

// 希尔排序的辅助函数：一趟希尔排序
void ShellInsert(Sqlist& L, int dk) {
    // 算法10.4
    // dk是当前增量（步长）。相隔dk个位置的元素属于同一组
    // 从第dk+1个元素开始，依次对每组进行直接插入排序
    for (int i = dk + 1; i <= L.length; ++i) {
        // 如果当前元素小于同组的前驱元素（前dk个位置）
        if (L.elem[i] < L.elem[i - dk]) {
            L.elem[0] = L.elem[i]; // 【哨兵】暂存当前元素
            int j;
            // 在同组内向前寻找插入位置，步长为dk（即每次向前跳dk个位置）
            for (j = i - dk; j > 0 && L.elem[0] < L.elem[j]; j -= dk)
                L.elem[j + dk] = L.elem[j]; // 记录后移dk位
            L.elem[j + dk] = L.elem[0];    // 插入元素到正确位置
        }
    }
}

// (3) 希尔排序
void ShellSort(Sqlist& L) {
    // 算法10.5
    int dlta[] = { 5, 3, 1 }; // 定义增量序列，增量必须递减，最后为1
    int t = 3;              // 增量序列的长度
    for (int k = 0; k < t; ++k)
        ShellInsert(L, dlta[k]); // 依此按增量5、3、1进行排序
}

// 辅助函数：打印顺序表
void PrintList(Sqlist L) {
    cout << "当前序列: ";
    // 严蔚敏教材中数据从1开始，所以i从1开始打印
    for (int i = 1; i <= L.length; ++i) {
        cout << L.elem[i] << " ";
    }
    cout << endl;
}

// 辅助函数：复制列表（为了多次测试不同算法）
void CopyList(Sqlist src, Sqlist& dest) {
    dest.length = src.length;
    for (int i = 0; i <= src.length; ++i) dest.elem[i] = src.elem[i];
}

int main() {
    // 初始化一个顺序表
    Sqlist L_original;
    // 注意：为了演示方便，数据从下标1开始填充
    // 这里的数据是无序的
    int initData[] = { 0, 49, 38, 65, 97, 76, 13, 27, 49, 55, 04 };
    L_original.length = 10;
    for (int i = 0; i <= L_original.length; ++i) {
        L_original.elem[i] = initData[i];
    }

    cout << "初始序列" << endl;
    PrintList(L_original);
    cout << endl;

    // 1. 测试直接插入排序
    Sqlist L1;
    CopyList(L_original, L1); // 复制原始数据，避免影响后续测试
    cout << "1.直接插入排序结果:" << endl;
    InsertSort(L1);
    PrintList(L1);
    cout << endl;

    // 2. 测试折半插入排序
    Sqlist L2;
    CopyList(L_original, L2);
    cout << "2.折半插入排序结果:" << endl;
    BInsertSort(L2);
    PrintList(L2);
    cout << endl;

    // 3. 测试希尔排序
    Sqlist L3;
    CopyList(L_original, L3);
    cout << "3.希尔排序结果:" << endl;
    ShellSort(L3);
    PrintList(L3);

    return 0;
}
