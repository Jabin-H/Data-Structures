#include <iostream>
#include <string>
#include <stack>
#define MaxSize 30
using namespace std;

typedef struct TreeNode *Tree;
struct TreeNode
{
    string data;
    Tree left;
    Tree right;
} T[MaxSize];

// 根据输入建立树
void BuildTree()
{
    int N;
    scanf("%d\n", &N);

    stack<Tree> st;
    Tree root = T;
    root->left = NULL;
    root->right = NULL;

    string str, value;

    getline(cin, str);
    value = str.substr(5); // 从第五个开始截取
    root->data = value;    // 给根节点赋值
    st.push(root);         // 根节点入栈

    for (int i = 0; i < 2 * N - 1; i++)
    {
        std::getline(cin, str);
        if (str == "Pop")
        {
            root = st.top();
            st.pop();
        }
        else
        {
            value = str.substr(5);
            Tree node = new TreeNode;
            node->data = value;
            node->left = NULL;
            node->right = NULL;

            if (root->left == NULL) // 如果左儿子为空，新节点就是左儿子
            {
                root->left = node;
                root = root->left;
            }
            else if (root->right == NULL) // 如果右儿子为空，新节点就是右儿子
            {
                root->right = node;
                root = root->right;
            }
            st.push(node);
        }
    }
}

// 迭代实现后序遍历
void PostOrderTraversal(Tree root)
{
    int flag = 0;
    stack<Tree> st;
    Tree prev = NULL;
    while (root != NULL || !st.empty())
    {
        while (root != NULL)
        {
            st.push(root);
            root = root->left;
        }
        root = st.top();
        st.pop();
        if (root->right == NULL || root->right == prev)
        {
            if (!flag)
                flag = 1;
            else
                cout << " ";
            cout << root->data;

            prev = root;
            root = NULL;
        }
        else
        {
            st.push(root);
            root = root->right;
        }
    }
}

// 递归后序遍历
void PostOrderTraversal(Tree root, bool &flag)
{
    if (root)
    {
        PostOrderTraversal(root->left, flag);
        PostOrderTraversal(root->right, flag);
        if (!flag)
            flag = true;
        else
            cout << " ";
        cout << root->data;
    }
}

int main()
{
    BuildTree();
    bool flag = false;
    PostOrderTraversal(T);
    // PostOrderTraversal(T, flag);
    return 0;
}