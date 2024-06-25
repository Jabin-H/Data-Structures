#include <iostream>
using namespace std;

typedef struct PolyNode* Polynomial;
struct PolyNode
{
    int coef;
    int expon;
    Polynomial next = NULL;
};

//添加项
void Attach(int coef, int expon, Polynomial& now)
{
    if (coef == 0)
        return;
    
    Polynomial temp = new PolyNode;
    temp->coef = coef;
    temp->expon = expon;
    now->next = temp;
    now = now->next;
}

// 读取多项式
Polynomial ReadPoly()
{
    int N, a, b;
    cin >> N;

    Polynomial p = new PolyNode;
    Polynomial now = p;
    while (N--)
    {
        cin >> a >> b;
        Attach(a, b, now);
    }
    now->next = NULL;

    Polynomial head = p;
    p = p->next;
    delete head;

    return p;
}

//打印多项式
void PrintPolynomial(Polynomial head)
{
    int flag = 0;
    while (head)
    {
        if (flag && head->coef)
            cout << " ";
        if (head->coef)
        {
            cout << head->coef << " " << head->expon;
            flag = 1;
        }
        head = head->next;
    }
    if (!flag)
        cout << 0 << " " << 0;
    cout << endl;
}

//多项式相加
Polynomial PolyAdd(Polynomial p1, Polynomial p2)
{
    Polynomial p = new PolyNode, now = p;
    Polynomial t1 = p1, t2 = p2;
    while (t1 && t2)
    {
        if (t1->expon == t2->expon)
        {
            Attach(t1->coef + t2->coef, t1->expon, now);
            t1 = t1->next;
            t2 = t2->next;
        }
        else if (t1->expon > t2->expon)
        {
            Attach(t1->coef, t1->expon, now);
            t1 = t1->next;
        }
        else
        {
            Attach(t2->coef, t2->expon, now);
            t2 = t2->next;
        }
    }

    Polynomial t = t1 ? t1 : t2;
    while (t)
    {
        Attach(t->coef, t->expon, now);
        t = t->next;
    }
    now->next = NULL;

    Polynomial head = p;
    p = p->next;
    delete head;

    return p;
}

//将temp节点插入多项式p中，保持p系数降序
void insert(int coef, int expon, Polynomial& p)
{
    Polynomial t = p;
    while (t->next)
    {
        if (t->next->expon == expon)
        {
            //修改 t->next
            t->next->coef += coef;
            if (t->next->coef == 0)
                t->next = t->next->next;
            return;
        }
        else if (t->next->expon < expon)
        {
            //插在 t 和 t->next 之间
            Polynomial temp = new PolyNode;
            temp->coef = coef;
            temp->expon = expon;
            temp->next = t->next;
            t->next = temp;
            return;
        }
        else
        {
            t = t->next;
        }
    }

    //插在多项式p尾部
    if (!t->next)
    {
        Polynomial temp = new PolyNode;
        temp->coef = coef;
        temp->expon = expon;
        t->next = temp;
        temp->next = NULL;
    }
}

Polynomial PolyMul(Polynomial p1, Polynomial p2)
{
    if (!p1 || !p2)
        return NULL;

    Polynomial p = new PolyNode;
    p->next = NULL;
    Polynomial t1 = p1, t2 = p2;

    while (t1)
    {
        t2 = p2;
        while (t2)
        {
            int coef = t1->coef * t2->coef;
            int expon = t1->expon + t2->expon;

            insert(coef, expon, p);

            t2 = t2->next;
        }
        t1 = t1->next;
    }

    Polynomial head = p;
    p = p->next;
    delete head;

    return p;
}

int main()
{
    //读取多项式
    PolyNode* p1 = ReadPoly();
    PolyNode* p2 = ReadPoly();

    //多项式乘法
    Polynomial res = PolyMul(p1, p2);
    PrintPolynomial(res);

    //多项式加法
    Polynomial polySum = PolyAdd(p1, p2);
    PrintPolynomial(polySum);

    return 0;
}