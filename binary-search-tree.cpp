#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;

    Node(int value)
    {
        this->key = value;
    }
};

void insert(Node *&root, int value)
{
    if (root == NULL)
    {
        root = new Node(value);
        return;
    }

    if (root->key < value)
    {
        insert(root->right, value);
    }
    else
    {
        insert(root->left, value);
    }
}

void inorder_stack(Node *root)
{
    stack<Node *> st;

    while (root != NULL || !st.empty())
    {
        while (root != NULL)
        {
            st.push(root);
            root = root->left;
        }

        root = st.top();
        st.pop();
        cout << root->key << " ";
        root = root->right;
    }
}

void pre_orderstack(Node *root)
{
    stack<Node *> st;
    st.push(root);
    while (!st.empty())
    {
        root = st.top();
        st.pop();

        cout << root->key << " ";

        if (root->right)
        {
            st.push(root->right);
        }

        if (root->left)
        {
            st.push(root->left);
        }
    }
}

void post_orderstack(Node *root)
{
    stack<Node *> st;
    while (true)
    {
        while (root != NULL)
        {
            st.push(root);
            st.push(root);
            root = root->left;
        }

        if (st.empty())
        {
            break;
        }

        root = st.top();
        st.pop();

        if (!st.empty() && root == st.top())
        {
            root = root->right;
        }
        else
        {
            cout << root->key << " ";
            root = NULL;
        }
    }
}

Node *deleteNode(Node *root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->key < value)
    {
        root->right = deleteNode(root->right, value);
        return root;
    }
    else if (root->key > value)
    {
        root->left = deleteNode(root->left, value);
        return root;
    }
    // Case 2: Only 1 child left/right
    if (root->left == NULL)
    {
        Node *tmp = root->right;
        delete root;
        return tmp;
    }
    else if (root->right == NULL)
    {
        Node *tmp = root->left;
        delete root;
        return tmp;
    }
    else
    {
        Node *parent = root;
        Node *succ = root->right;

        while (succ->left != NULL)
        {
            parent = succ;
            succ = succ->left;
        }

        if (parent == root)
        {
            parent->right = succ->right;
        }
        else
        {
            parent->left = succ->right;
        }

        root->key = succ->key;
        delete succ;
        return root;
    }
}

void findMax(Node *root)
{
    if (root == NULL)
    {
        cout << "Tree is empty";
    }

    Node *current = root->right;

    while (current->right != NULL)
    {
        current = current->right;
    }

    if (current == NULL)
    {
        cout << "No elements greater than the root";
    }
    else
    {
        cout << "Max is: " << current->key;
    }
}

void findMin(Node *root)
{
    if (root == NULL)
    {
        cout << "Tree is empty";
    }

    Node *current = root->left;

    while (current->left != NULL)
    {
        current = current->left;
    }

    if (current == NULL)
    {
        cout << "No elements lesser than the root";
    }
    else
    {
        cout << "Min is: " << current->key;
    }
}

Node *findKthMin(Node *root, int &count, int k)
{
    if (root == NULL)
    {
        return root;
    }

    Node *left = findKthMin(root->left, count, k);

    if (left != NULL)
    {
        return left;
    }

    count++;
    if (count == k)
    {
        return root;
    }

    return findKthMin(root->right, count, k);
}

int main()
{
    Node *root = NULL;
    int list[] = {15, 7, 16, 6, 8, 19, 9, 18};
    int n = sizeof(list) / sizeof(list[0]);
    for (int i = 0; i < n; i++)
    {
        insert(root, list[i]);
    }

    post_orderstack(root);
    // findMax(root);
    // findMin(root);
    int count = 0;
    int k = 3;
    // Tim node nho nhat thu 3
    cout << "\n";
    Node *kthMin = findKthMin(root, count, k);
    if (kthMin == NULL)
    {
        cout << "OOPS!";
    }
    else
        cout << k << "-th min: " << kthMin->key;
}