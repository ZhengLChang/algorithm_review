#include <iostream>
using namespace std;

template <typename T>
struct BSTNode
{
    T data;
    BSTNode<T> *left, *right;
    BSTNode():left(NULL), right(NULL) {}
    BSTNode(const T d, BSTNode<T> *L = NULL, BSTNode<T>* R = NULL):data(d), left(L),right(R) {}
};

template <class T>
class BST
{
public:
    BST():root(NULL) {}
    BST(T value):root(NULL), RefValue(value)
    {
        T x;
        cin >> x;
        while(x != RefValue)
        {
            Insert(x, root);
            cin >> x;
        }
    }
    ~BST() { Destroy(root); }
    bool Remove(T x) { return Remove(x, root); }
    bool Search(T x) { return (Search(x, root) != NULL) ? true:false; }
    void InOrder() { InOrder(root);}
protected:
    bool Insert(const T &el, BSTNode<T> * &ptr)
    {
        if(ptr == NULL)
        {
            ptr = new BSTNode<T>(el);
            if(ptr == NULL)
            {
                cout << "Memory allocation failed!" << endl;
                exit(1);
            }
            return true;
        }
        else if(el < ptr->data)
        {
            Insert(el, ptr->left);
        }
        else if(el > ptr->data)
        {
            Insert(el, ptr->right);
        }
        else
        {
            return false;
        }
            return false;
    }
    bool Remove(T x, BSTNode<T>*  &ptr)
    {
        BSTNode<T> *temp;
        if(ptr != NULL)
        {
            if(x < ptr->data)
            {
                Remove(x, ptr->left);
            }
            else if(x > ptr->data)
            {
                Remove(x, ptr->right);
            }
            else if(ptr->left != NULL && ptr->right != NULL)
            {
                temp = ptr->right;
                while(temp->left != NULL)
                {
                    temp = temp->left;
                }
                ptr->data = temp->data;
                Remove(ptr->data, ptr->right);
            }
            else
            {
                temp = ptr;
                if(ptr->left == NULL)
                {
                    ptr = ptr->right;
                }
                else
                {
                    ptr = ptr->left;
                }
                delete temp;
                temp = NULL;
                return true;
            }

        }
        else
        {
            return false;
        }
    }
    BSTNode<T> *Search(T x, BSTNode<T> *ptr)
    {
        if(ptr == NULL)
        {
            return NULL;
        }
        else if(x < ptr->data)
        {
            return Search(x, ptr->left);
        }
        else if(x > ptr->data)
        {
            return Search(x, ptr->right);
        }
        else
        {
            return ptr;
        }
    }
    void InOrder(BSTNode<T> *root)
    {
        if(root != NULL)
        {
            InOrder(root->left);
            cout << root->data << " ";
            InOrder(root->right);
        }
    }
    void Destroy(BSTNode<T>* &root)
    {
        if(root == NULL)
        {
            return;
        }
        if(root->left != NULL)
        {
            Destroy(root->left);
        }
        if(root->right != NULL)
        {
            Destroy(root->right);
        }
        delete root;
        root = NULL;
    }
private:
    BSTNode<T> *root;
    T RefValue;
};

int main()
{
    BST<char> tree('#');
    tree.InOrder();
    cout << endl;
}






