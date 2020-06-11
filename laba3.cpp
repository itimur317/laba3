#include <iostream>
#include <vector>
#include <string>
/*
базовые операции 5+
сохранение в строку по фикс обходу 1+ 
по задаваему параметру 3+
поиск на вхожд 3
*/
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
    int count;
    void destroy_tree(node* branch) {
        if (branch != nullptr) {
            destroy_tree(branch->left);
            destroy_tree(branch->right);
            delete branch;
        }
    }

    void insert_help(node* branch, T item) {
        node* cur = branch;
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
 
    node* search_help(T item, node* cur) {
        node* branch = cur;
        if (branch != nullptr) {
            if (item == branch->data)
                return branch;
            else if (item < branch->data)
                return search_help(item, branch->left);
            else
                return search_help(item, branch->right);
        }
        else 
            return nullptr;
    }

    void print_help(node* cur) {
        node* tmp = cur;
        if (tmp != nullptr) {
            if (tmp->left)
                print_help(tmp->left);
            cout << tmp->data << " ";
            if (tmp->right)
                print_help(tmp->right);
        }
        else
            return;
    }

    node* tree_min_help(node* cur) {
        node* min = cur;
        while (min->left) {
            min = min->left;
        }
        return min;
    }

    node* tree_max_help(node* cur) {
        node* max = cur;
        while (max->right) {
            max = max->right;
        }
        return max;
    }

    node* delete_help(T item, node* branch) {
        if (!branch) {
            return nullptr;
        }
        if (branch->data > item) {
            branch->left = delete_help(item, branch->left);
        }
        else if (branch->data < item) {
            branch->right = delete_help(item, branch->right);
        }

        // дошёл до нужного
        else {
            if (branch->left == nullptr && branch->right == nullptr) { // бездетный
                delete branch;
                branch = nullptr;
                return branch;
            }
            else if (branch->left == nullptr) { // 1 ребенок справа
                node* tmp = branch;
                branch = branch->right;
                delete tmp;
                return branch;
            }
            else if (branch->right == nullptr) { // 1 ребенок слева 
                node* tmp = branch;
                branch = branch->left;
                delete tmp;
                return branch;
            } // было если по одному, теперь по 2 ребенка
            else { 
                node* tmp = tree_min_help(branch->right);
                branch->data = tmp->data;
                branch->right = delete_help(tmp->data, branch->right);
            }
        }
        return branch;
    }

    vector<T>* KLP_help(node* branch, vector<T>* vect) {
        node* tmp = branch; // KLP
        if (tmp) {
            vect->push_back(branch->data);
            KLP_help(branch->left, vect);
            KLP_help(branch->right, vect);
        }
        return vect;
    }

    vector<T>* KPL_help(node* branch, vector<T>* vect) {
        node* tmp = branch; // KLP
        if (tmp) {
            vect->push_back(branch->data);
            KPL_help(branch->right, vect);
            KPL_help(branch->left, vect);
        }
        return vect;
    }

    vector<T>* LKP_help(node* branch, vector<T>* vect) {
        node* tmp = branch; // KLP
        if (tmp) {
            LKP_help(branch->left, vect);
            vect->push_back(branch->data);
            LKP_help(branch->right, vect);
        }
        return vect;
    }
    
    vector<T>* PKL_help(node* branch, vector<T>* vect) {
        node* tmp = branch; // KLP
        if (tmp) {
            PKL_help(branch->right, vect);
            vect->push_back(branch->data);
            PKL_help(branch->left, vect);
        }
        return vect;
    }

    vector<T>* LPK_help(node* branch, vector<T>* vect) {
        node* tmp = branch; // KLP
        if (tmp) {
            LPK_help(branch->left, vect);
            LPK_help(branch->right, vect);
            vect->push_back(branch->data);
        }
        return vect;
    }

    vector<T>* PLK_help(node* branch, vector<T>* vect) {
        node* tmp = branch; // KLP
        if (tmp) {
            PLK_help(branch->right, vect);
            PLK_help(branch->left, vect);
            vect->push_back(branch->data);
        }
        return vect;
    }

    bool find_subtree_help(node* cur1, node* cur2) {
        if (cur2 == nullptr)
            return 1;
        return (cur1->data == cur2->data) &&
            find_subtree_help(cur1->left, cur2->left) &&
            find_subtree_help(cur1->right, cur2->right);
    }

public:
    BST() {
        this->root = nullptr;
        this->count = 0;
    };

    ~BST() {
        destroy_tree(this->root);
    };

    bool is_empty() {
        if (this->root == nullptr)
            return 1;
        return 0;
    }

    T what_in_root() {
        return this->root->data;
    }

    node* tree_max() {
        return tree_max_help(this->root);
    }

    node* tree_min() {
        return tree_min_help(this->root);
    }

    vector <T>* KLP() {
        vector<T>* cur = new vector<T>;
        return KLP_help(this->root, cur);
    }

    vector <T>* KPL() {
        vector <T>* cur = new vector <T>;
        return KPL_help(this->root, cur);
    }

    vector <T>* LKP() {
        vector <T>* cur = new vector <T>;
        return LKP_help(this->root, cur);
    }

    vector <T>* PKL() {
        vector <T>* cur = new vector <T>;
        return PKL_help(this->root, cur);
    }

    vector <T>* PLK() {
        vector <T>* cur = new vector <T>;
        return PLK_help(this->root, cur);
    }
    vector <T>* LPK() {
        vector <T>* cur = new vector <T>;
        return LPK_help(this->root, cur);
    }

    void insert(T item) {
        this->count++;
        if (this->root != nullptr)
            insert_help(this->root, item);
        else {
            this->root = new node;
            this->root->data = item;
            this->root->right = nullptr;
            this->root->left = nullptr;
        }
    }

    node* search(T item) {
        return search_help(item, this->root);
    }

    void delete_node(T item) {
        this->count--;
        this->root = delete_help(item, this->root);
    }

    int check_count() {
        return this->count;
    }

    bool find_subtree(BST<T>* little_tree) {
        if (is_empty()) {
            return 0;
        }
        if (little_tree->is_empty()) {
            return 1;
        }
        node* cur1 = search(little_tree->what_in_root());
        if (!cur1)
            return 0;
        if (find_subtree_help(cur1, little_tree->root)){
            return 1;
        }
        return 0;
    }

    void print() {
        print_help(this->root);
        cout << endl;
    }
    
};

int main() {
    BST<int> a;
    cout << a.is_empty() << endl;
    a.insert(228);
    cout << a.is_empty() << endl;
    a.insert(13);
    cout << a.is_empty() << endl;
    a.insert(132);
    a.insert(600);
    a.insert(22);
    a.insert(411);
    a.insert(12);
    a.insert(421);
    a.insert(32);
    a.insert(87);
    a.insert(76);
    a.insert(27);
    a.insert(25);
    a.insert(8);
    a.print();
    cout << a.search(8)->data << endl;
    cout << a.tree_max()->data << "  " << a.tree_min()->data << endl;
    cout << "in root:  " << a.what_in_root() << endl;
    a.print();
    cout << a.check_count() << endl;
    cout << "KLP: ";
    for (int i = 0; i < a.check_count(); i++) {
        cout << (*a.KLP())[i] << " ";
    }
    cout << endl << "KPL: ";
    for (int i = 0; i < a.check_count(); i++) {
        cout << (*a.KPL())[i] << " ";
    }
    cout << endl << "LKP: ";
    for (int i = 0; i < a.check_count(); i++) {
        cout << (*a.LKP())[i] << " ";
    }
    cout << endl << "LPK: ";
    for (int i = 0; i < a.check_count(); i++) {
        cout << (*a.LPK())[i] << " ";
    }
    cout << endl << "PLK: ";
    for (int i = 0; i < a.check_count(); i++) {
        cout << (*a.PLK())[i] << " ";
    }
    cout << endl << "PKL: ";
    for (int i = 0; i < a.check_count(); i++) {
        cout << (*a.PKL())[i] << " ";
    }
    BST<int>* b = new BST<int>;
    cout << endl << b->is_empty() << endl;
    b->insert(32);
    b->insert(27);
    b->insert(87);
    cout << a.find_subtree(b);

    return 0;
}