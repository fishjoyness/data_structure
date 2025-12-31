#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

// 哈夫曼树结点结构定义
typedef struct {
    int weight;              // 结点的权值
    int parent, lchild, rchild;  // 结点的双亲、左孩子、右孩子的下标
} HTNode, * HuffmanTree;

// 在HT[1..k]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
//在哈夫曼树中找到权值最小且还没被合并的两个节点
void Select(HuffmanTree HT, int k, int& s1, int& s2) {
    int i, min1, min2;
    min1 = min2 = 9999;       // 初始化为很大的值
    s1 = s2 = 0;              // 初始化s1和s2

    for (i = 1; i <= k; i++) {
        if (HT[i].parent == 0) {  // 只考虑还未被选中的结点
            if (HT[i].weight < min1) {
                min2 = min1;      // 更新第二小的值
                s2 = s1;
                min1 = HT[i].weight;  // 更新最小的值
                s1 = i;
            }
            else if (HT[i].weight < min2) {
                min2 = HT[i].weight;  // 更新第二小的值
                s2 = i;
            }
        }
    }
}

// 构造哈夫曼树 HT
void CreateHuffmanTree(HuffmanTree& HT, int n) {
    int m, s1, s2, i;

    if (n <= 1) return;       // 如果结点数小于等于1，直接返回

    m = 2 * n - 1;            // 哈夫曼树总结点数
    HT = new HTNode[m + 1];   // 0号单元未用，所以需要动态分配m+1个单元

//一开始，所有节点都是孤立的，所以它们的这些关系都是空的。
    for (i = 1; i <= m; ++i) {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }

    // 输入前n个单元中叶子结点的权值
    cout << "请输入" << n << "个叶子结点的权值：" << endl;
    for (i = 1; i <= n; ++i) {
        cin >> HT[i].weight;
    }

    // 初始化工作结束，下面开始创建哈夫曼树
    for (i = n + 1; i <= m; ++i) {
        // 通过n-1次的选择、删除、合并来创建哈夫曼树
        Select(HT, i - 1, s1, s2);  // 在前i-1个结点中选择权值最小的两个结点s1和s2

        HT[s1].parent = i;          // 得到新结点i，从森林中删除s1
        HT[s2].parent = i;          // 将s2的双亲域由0改为i

        HT[i].lchild = s1;          // s1作为i的左孩子
        HT[i].rchild = s2;          // s2作为i的右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight;  // i的权值为左右孩子权值之和
    }
}

// 打印哈夫曼树
void PrintHuffmanTree(HuffmanTree HT, int n) {
    int m = 2 * n - 1;
    cout << "\n哈夫曼树的存储结构：" << endl;
    cout << "序号\t权值\t双亲\t左孩子\t右孩子" << endl;
    for (int i = 1; i <= m; i++) {
        cout << i << "\t" << HT[i].weight << "\t" << HT[i].parent
            << "\t" << HT[i].lchild << "\t" << HT[i].rchild << endl;
    }
}

int main() {
    HuffmanTree HT;
    int n;

    cout << "请输入叶子结点的个数：";
    cin >> n;

    CreateHuffmanTree(HT, n);
    PrintHuffmanTree(HT, n);

    delete[] HT;  // 释放内存
    return 0;
}
