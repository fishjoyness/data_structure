#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

// 定义二叉树结点类型
typedef struct BiTNode {
    char data;                    // 结点数据域
    struct BiTNode* lchild, * rchild;  // 左右孩子指针
} BiTNode, * BiTree;

// 按照先序遍历顺序创建二叉链表
void CreateBiTree(BiTree& T) {
    char ch;
    cin >> ch;                   // 输入结点的值

    if (ch == '#') {             // 如果输入的是'#'，表示创建空树
        T = NULL;
    }
    else {
        T = new BiTNode;         // 为新结点分配内存空间
        T->data = ch;            // 将输入的值赋给结点的数据域
        CreateBiTree(T->lchild); // 递归创建左子树（先序遍历：根->左->右）
        CreateBiTree(T->rchild); // 递归创建右子树
    }
}

// 中序遍历二叉树
void InOrderTraverse(BiTree T) {
    if (T) {                     // 如果树不为空
        InOrderTraverse(T->lchild);  // 中序遍历左子树
        cout << T->data << " ";  // 访问根结点
        InOrderTraverse(T->rchild);  // 中序遍历右子树
    }
}

// 先序遍历二叉树
void PreOrderTraverse(BiTree T) {
    if (T) {                     // 如果树不为空
        cout << T->data << " ";  // 访问根结点
        PreOrderTraverse(T->lchild); // 先序遍历左子树
        PreOrderTraverse(T->rchild); // 先序遍历右子树
    }
}

// 后序遍历二叉树
void PostOrderTraverse(BiTree T) {
    if (T) {                     // 如果树不为空
        PostOrderTraverse(T->lchild); // 后序遍历左子树
        PostOrderTraverse(T->rchild); // 后序遍历右子树
        cout << T->data << " ";  // 访问根结点
    }
}

int main() {
    BiTree T;                    // 定义二叉树根结点
    cout << "请按先序顺序输入二叉树结点值：" << endl;
    CreateBiTree(T);             // 创建二叉树

    cout << "\n先序遍历结果：";
    PreOrderTraverse(T);

    cout << "\n中序遍历结果：";
    InOrderTraverse(T);

    cout << "\n后序遍历结果：";
    PostOrderTraverse(T);

    cout << endl;
    return 0;
}
