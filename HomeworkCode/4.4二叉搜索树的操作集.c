#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf_s("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf_s("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    InorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf_s("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf_s("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    printf("输入要删除的数字个数:");
    scanf_s("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf_s("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}

void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void InorderTraversal(BinTree BT)
{
    if (BT)
    {
        InorderTraversal(BT->Left);
        printf("%d ", BT->Data);
        InorderTraversal(BT->Right);
    }
}

/* 你的代码将被嵌在这里 */
BinTree Insert(BinTree BST, ElementType X)
{
    if (!BST)
    {
        BST = malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else
    {
        if (X < BST->Data)
            BST->Left = Insert(BST->Left, X);
        else
            BST->Right = Insert(BST->Right, X);
    }
    return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{
    BinTree temp;
    if (!BST)
        printf("Not Found\n");
    else if (X < BST->Data)
        BST->Left = Delete(BST->Left, X);
    else if (X > BST->Data)
        BST->Right = Delete(BST->Right, X);
    else // 找到要删除的结点
    {
        if (BST->Left && BST->Right)
        {
            temp = FindMax(BST->Left);
            BST->Data = temp->Data;
            BST->Left = Delete(BST->Left, BST->Data);
        }
        else
        {
            temp = BST;
            if (!BST->Left)
                BST = BST->Right;
            else if (!BST->Right)
                BST = BST->Left;
            free(temp);
        }
    }
    return BST;
}

Position Find(BinTree BST, ElementType X)
{
    while (BST)
    {
        if (X == BST->Data)
            return BST;
        else if (X < BST->Data)
            BST = BST->Left;
        else
            BST = BST->Right;
    }
    return NULL;
}

Position FindMin(BinTree BST)
{
    if (BST)
        while (BST->Left)
            BST = BST->Left;
    return BST;
}

Position FindMax(BinTree BST)
{
    if (BST)
        while (BST->Right)
            BST = BST->Right;
    return BST;
}