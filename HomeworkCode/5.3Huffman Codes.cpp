#include <iostream>
#include <string>
#include <map>
#define MaxWeight 1001
using namespace std;

map<char, int> mp; // 保存字符及其频率

typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    char ch;
    int weight;
    HuffmanTree left, right;
};

typedef struct HeapStruct *MinHeap;
struct HeapStruct
{
    HuffmanTree *nodes;
    int size;
    int capacity;
};

// 创造树结点
HuffmanTree createTreeNode()
{
    HuffmanTree node = new TreeNode;
    node->ch = ' ';
    node->weight = MaxWeight;
    node->left = node->right = NULL;
    return node;
}

// 创建并初始化最小堆
MinHeap createHeap(int n)
{
    int size = n;
    MinHeap h = new HeapStruct;
    h->nodes = new HuffmanTree[size + 1];
    for (int i = 0; i <= size; i++)
    {
        h->nodes[i] = createTreeNode();
    }
    h->nodes[0]->weight = -1;
    h->size = size;
    h->capacity = size;
    return h;
}

// 将h中以结点i为根的子堆调整为最小堆
void curcDown(MinHeap h, int i)
{
    HuffmanTree temp = h->nodes[i];
    int parent, child;
    for (parent = i; parent * 2 <= h->size; parent = child)
    {
        child = parent * 2;
        if (child != h->size && h->nodes[child]->weight > h->nodes[child + 1]->weight)
            child++;
        if (h->nodes[child]->weight >= temp->weight)
            break;
        else
            h->nodes[parent] = h->nodes[child];
    }
    h->nodes[parent] = temp;
}

// 调整堆
void buildMinHeap(MinHeap h)
{
    // 从第一个有儿子的结点开始调整
    for (int i = h->size / 2; i > 0; i--)
        curcDown(h, i);
}

// 删除并返回堆的最小元素
HuffmanTree deleteMin(MinHeap h)
{
    if (!h->size)
        return NULL;
    HuffmanTree minItem = h->nodes[1];
    HuffmanTree temp = h->nodes[h->size--];
    int parent, child;
    for (parent = 1; parent * 2 <= h->size; parent = child)
    {
        child = parent * 2;
        if (child != h->size && h->nodes[child]->weight > h->nodes[child + 1]->weight)
            child++;
        if (h->nodes[child]->weight >= temp->weight)
            break;
        else
            h->nodes[parent] = h->nodes[child];
    }
    h->nodes[parent] = temp;
    return minItem;
}

// 堆的插入
void insertMinHeap(MinHeap h, HuffmanTree root)
{
    if (h->size == h->capacity) // 判断堆是否已满
        return;
    int i = ++h->size;
    for (; h->nodes[i / 2]->weight > root->weight; i /= 2)
        h->nodes[i] = h->nodes[i / 2];
    h->nodes[i] = root;
}

HuffmanTree huffman(MinHeap h)
{
    int size = h->size;
    HuffmanTree root;
    for (int i = 1; i < size; i++)
    {
        root = createTreeNode();
        root->left = deleteMin(h);
        root->right = deleteMin(h);
        root->weight = root->left->weight + root->right->weight;
        insertMinHeap(h, root);
    }
    root = deleteMin(h);
    return root;
}

// 测试用，前序遍历，打印字符及编码
int preOrderTraversal(HuffmanTree hTree, string s)
{
    int res = 0;
    if (hTree)
    {
        if (!hTree->left && !hTree->right)
        {
            // cout << hTree->ch << " " << s << endl;
            res += hTree->weight * s.size();
        }
        else
        {
            res += preOrderTraversal(hTree->left, s + "0");
            res += preOrderTraversal(hTree->right, s + "1");
        }
    }
    return res;
}

// 计算HuffmanTree的编码长度
int WPL(HuffmanTree huff, int depth)
{
    if (!huff->left && !huff->right) // 如果是叶结点，返回编码长度
        return depth * huff->weight;
    else // 否则返回其左右子结点的编码长度
        return WPL(huff->left, depth + 1) + WPL(huff->right, depth + 1);
}

// 检测提交的编码
void checkSubmit(int n, int length)
{
    HuffmanTree huff = createTreeNode();
    HuffmanTree cur;
    int cnt = 1;
    bool flag = true;
    char c;
    string code;
    for (int i = 0; i < n; i++)
    {
        cur = huff;
        cin >> c >> code;
        for (int j = 0; j < code.size(); j++) // 遍历编码
        {
            if (code[j] == '0') // 当前编码为0，左子树
            {
                if (!cur->left) // 左子树不存在，创建
                {
                    cur->left = createTreeNode();
                    cnt++;
                }
                if (cur->weight != MaxWeight)
                    flag = false;
                cur = cur->left;
            }
            else if (code[j] == '1') // 当前编码为1，右子树
            {
                if (!cur->right)
                {
                    cur->right = createTreeNode();
                    cnt++;
                }
                if (cur->weight != MaxWeight)
                    flag = false;
                cur = cur->right;
            }
        }
        if (cur->left || cur->right)
            flag = false;
        cur->weight = mp[c];
    }
    if (cnt != n * 2 - 1 || !flag || WPL(huff, 0) != length)
    {
        cout << "No" << endl;
        return;
    }
    else
    {
        cout << "Yes" << endl;
        return;
    }
}

int main()
{
    int n; // 结点个数
    cin >> n;
    MinHeap h = createHeap(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> h->nodes[i]->ch >> h->nodes[i]->weight;
        mp.insert(pair<char, int>(h->nodes[i]->ch, h->nodes[i]->weight));
    }
    buildMinHeap(h);
    HuffmanTree hTree = huffman(h);
    // int length = curOrderTraversal(hTree, "");
    int length = WPL(hTree, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        checkSubmit(n, length);
    }
    return 0;
}