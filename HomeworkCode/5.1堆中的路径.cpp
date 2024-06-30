#include <iostream>
#define MaxSize 1005
#define MinData -10005
using namespace std;

typedef struct HeapStruct *MinHeap;
struct HeapStruct
{
    int *data;
    int size;
    int capacity;
};

MinHeap createHeap()
{
    MinHeap h = new HeapStruct;
    h->data = new int[MaxSize];
    h->data[0] = MinData;
    h->size = 0;
    h->capacity = MaxSize;
    return h;
}

void insert(MinHeap h, int val)
{
    if (h->size == h->capacity)
        return;
    int i = ++h->size;
    for (; h->data[i / 2] > val; i /= 2)
        h->data[i] = h->data[i / 2];
    h->data[i] = val;
}

// void precDown(MinHeap h, int i)
// {
//     int temp = h->data[i];
//     int parent, child;
//     for (parent = i; parent * 2 <= h->size; parent = child)
//     {
//         child = parent * 2;
//         if (child != h->size && h->data[child] > h->data[child + 1])
//             child++;
//         if (temp <= h->data[child])
//             break;
//         else
//             h->data[parent] = h->data[child];
//     }
//     h->data[parent] = temp;
// }

// void buildHeap(MinHeap h)
// {
//     for (int i = h->size / 2; i > 0; i--)
//         precDown(h, i);
// }

int main()
{
    int n, m, val;
    cin >> n >> m;
    // 建立堆
    MinHeap h = createHeap();
    for (int i = 1; i <= n; i++)
    {
        cin >> val;
        insert(h, val);
    }
    // 输出
    while (m--)
    {
        int index;
        cin >> index;
        int flag = 0;
        for (int i = index; i > 0; i /= 2)
        {
            if (flag)
                cout << " ";
            else
                flag = 1;
            cout << h->data[i];
        }
        cout << endl;
    }
    return 0;
}