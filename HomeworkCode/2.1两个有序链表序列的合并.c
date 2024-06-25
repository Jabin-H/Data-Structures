#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2)
{
    List head = (List)malloc(sizeof(struct Node));

    List rear = head;
    List t1 = L1->Next;
    List t2 = L2->Next;

    while (t1 && t2)
    {
        if (t1->Data <= t2->Data)
        {
            rear->Next = t1;
            t1 = t1->Next;
        }
        else
        {
            rear->Next = t2;
            t2 = t2->Next;
        }
        rear = rear->Next;
    }

    rear->Next = t1 ? t1 : t2;

    L1->Next = NULL;
    L2->Next = NULL;

    return head;
}