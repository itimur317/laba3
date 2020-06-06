#include <iostream>
#include <locale.h>
using namespace std;

template <class T>
class BST {
private:
    struct node {
        T data; 
        node* left;
        node* right;
    };
    node* root;
    void destroy_tree(node* branch) {
        if (branch != nullptr) {
            destroy_tree(branch->left);
            destroy_tree(branch->right);
            delete branch;
        }
    }

    void insert_help(node* cur, T item) {
        if (item < cur->data) {
            if (cur->left != nullptr) {
                insert_help(cur->left, item);
            }
            else {
                cur->left = new node;
                cur->left->data = item;
                cur->left->left = nullptr;
                cur->left->right = nullptr;
            }
        }
        else if (item > cur->data) {
            if (cur->right != nullptr) {
                insert_help(cur->right, item);
            }
            else {
                cur->right = new node;
                cur->right->data = item;
                cur->right->left = nullptr;
                cur->right->right = nullptr;
            }
        }
    }
 
    void print_help(node* cur) {
        if (cur != nullptr) {
            if (cur->left)
                print_help(cur->left);
            cout << cur->data << " ";
            if (cur->right)
                print_help(cur->right);
        }
        else
            return;
    }

public:
    BST() {
        root = new node;
        root = nullptr;
    };

    BST(T item) {
        root = new node;
        root->data = item;
        root->right = nullptr;
        root->left = nullptr;
    };

    ~BST() {
        destroy_tree(this->root);
    };

    bool is_empty() {
        if (root == nullptr)
            return 1;
        return 0;
    }

    void insert(T item) {
        if (this->root != nullptr)
            insert_help(this->root, item);
        else {
            this->root = new node;
            this->root->data = item;
            this->root->right = nullptr;
            this->root->left = nullptr;
        }
    }

    void print() {
        print_help(this->root);
        cout << endl;
    }
};



int main() {
    setlocale(LC_ALL, "russian");
    BST<int> aaa;
    cout << aaa.is_empty() << endl;
    aaa.insert(228);
    cout << aaa.is_empty() << endl;
    aaa.insert(13);
    cout << aaa.is_empty() << endl;
    aaa.insert(132);
    aaa.insert(600);
    aaa.insert(100);
    aaa.insert(8);
    aaa.print();
    return 0;
}