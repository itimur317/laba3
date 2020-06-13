#include <iostream>
#include <vector>
#include <cassert>
/*
базовые операции 5+ tested
сохранение в строку по фикс обходу (1+)? tested
по задаваему параметру 3+ tested
поиск на вхожд 3+ tested
извлечение поддерева 2+ tested
== 13(14)
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

    BST<T>* KLP_for_eject(node* cur, BST<T>* tree) {
        node* tmp = cur;
        if (tmp) {
            tree->insert(cur->data);
            KLP_for_eject(cur->left, tree);
            KLP_for_eject(cur->right, tree);
        }
        return tree;
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
        if (!search(item)) {
            this->count++;
        }
        if (this->root != nullptr)
            insert_help(this->root, item);
        else {
            this->root = new node;
            this->root->data = item;
            this->root->right = nullptr;
            this->root->left = nullptr;
        }
    }

    void clear_tree() {
        destroy_tree(this->root);
        this->root = nullptr;
        this->count = 0;
    }

    node* search(T item) {
        return search_help(item, this->root);
    }

    void delete_node(T item) {
        if (search(item)) {
            this->count--;
        }
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

    BST<T>* eject(node* cur) {
        BST<T>* new_tree = new BST<T>;
        return KLP_for_eject(cur, new_tree);
    }
    T what_in_node(node* cur) {
        return cur->data;
    }
};

void interface() {
    int check;
    cout << "to create integer empty binary search tree press 1" << endl;
    cout << "to exit press 0" << endl;
    cin >> check;
    BST<int>* cur = new BST<int>;
    BST<int>* second_tree = new BST<int>;
    while (check) {
        cout << "press 1 to insert element" << endl;
        cout << "press 2 to search element" << endl;
        cout << "press 3 to delete element" << endl;
        cout << "press 4 to check maximum" << endl;
        cout << "press 5 to check minimum" << endl;
        cout << "press 6 to make vector from tree" << endl;
        cout << "press 7 to make subtree" << endl;
        cout << "press 8 to find subtree" << endl;
        cout << "press 9 to check empty or not" << endl;
        cout << "press 10 to check how many elements in tree" << endl;
        cout << "press 11 to check all elements in tree" << endl;
        cout << "press 0 to exit" << endl;
        cin >> check;
        if (check == 1) {
            int rabotaem;
            cout << "enter element" << endl;
            cin >> rabotaem;
            cur->insert(rabotaem);
            cout << rabotaem << " inserted! " << endl;
            while (check) {
                cout << "press 1 if you want insert one more element" << endl;
                cout << "press 0 to stop" << endl;
                cin >> check;
                if (check == 1) {
                    cin >> rabotaem;
                    cur->insert(rabotaem);
                }
            }
            check = 1;
        }
        else if (check == 2) {
            int rabotaem;
            cout << "enter element" << endl;
            cin >> rabotaem;
            if (cur->search(rabotaem)) {
                cout << rabotaem << " found, what to do?" << endl;
                cout << "press 1 to delete element" << endl;
                cout << "press 2 to make subtree with this root" << endl;
                cout << "press 3 to don`t touch it" << endl;
                cin >> check;
                if (check == 1)
                    cur->delete_node(rabotaem);
                else if (check == 2)
                    check = 8;
                else if (check == 3)
                    check = 2;
            }
        }
        else if (check == 3) {
            int rabotaem;
            cout << "enter element" << endl;
            cin >> rabotaem;
            if (cur->search(rabotaem)) {
                cur->delete_node(rabotaem);
                cout << rabotaem << " deleted" << endl;
            }
            else
                cout << "not found!" << endl;
        }
        else if (check == 4) { 
            cout << "maximum is " << cur->what_in_node(cur->tree_max()) << endl;
        }
        else if (check == 5) {
            cout << "minimum is " << cur->what_in_node(cur->tree_min()) << endl;
        }
        else if (check == 6) {
            cout << "you have 6 variants to make it:" << endl;
            cout << "press 1 to ROOT-LEFT-RIGHT" << endl;
            cout << "press 2 to ROOT-RIGHT-LEFT" << endl;
            cout << "press 3 to LEFT-ROOT-RIGHT" << endl;
            cout << "press 4 to LEFT-RIGHT-ROOT" << endl;
            cout << "press 5 to RIGHT-LEFT-ROOT" << endl;
            cout << "press 6 to RIGHT-ROOT-LEFT" << endl;
            cin >> check;
            if (check == 1) {
                cout << "in vector: ";
                for (int i = 0; i < cur->check_count(); i++) {
                    cout << (*cur->KLP())[i] << " ";
                }
                cout << endl;
            }
            if (check == 2) {
                cout << "in vector: ";
                for (int i = 0; i < cur->check_count(); i++) {
                    cout << (*cur->KPL())[i] << " ";
                }
                cout << endl;
            }
            if (check == 3) {
                cout << "in vector: ";
                for (int i = 0; i < cur->check_count(); i++) {
                    cout << (*cur->LKP())[i] << " ";
                }
                cout << endl;
            }
            if (check == 4) {
                cout << "in vector: ";
                for (int i = 0; i < cur->check_count(); i++) {
                    cout << (*cur->LPK())[i] << " ";
                }
                cout << endl;
            }
            if (check == 5) {
                cout << "in vector: ";
                for (int i = 0; i < cur->check_count(); i++) {
                    cout << (*cur->PLK())[i] << " ";
                }
                cout << endl;
            }
            if (check == 6) {
                cout << "in vector: ";
                for (int i = 0; i < cur->check_count(); i++) {
                    cout << (*cur->PKL())[i] << " ";
                }
                cout << endl;
            }
        }
        else if (check == 7) {
            cout << "how many elements you want to insert?" << endl;
            cin >> check;
            if (!second_tree->is_empty()) {
                second_tree->clear_tree();
            }
            for (int i = 0; i < check; i++) {
                int rabotaem;
                cout << i<< ": " << endl;
                cin >> rabotaem;
                second_tree->insert(rabotaem);
            }
            cout << "this tree saved like second tree" << endl;
            check = 7;
        }
        else if (check == 8) {
            cout << "press 1 to create new subtree" << endl;
            cout << "press 2 to use second tree" << endl;
            cin >> check;
            if (check == 1) {
                BST<int>* tmp_tree = new BST<int>;
                cout << "how many elements you want insert to tree?" << endl;
                cin >> check;
                for (int i = 0; i < check; i++) {
                    int rabotaem;
                    cin >> rabotaem;
                    tmp_tree->insert(rabotaem);
                }
                if (cur->find_subtree(tmp_tree))
                    cout << "subtree found!" << endl;
                else
                    cout << "subtree not found" << endl;
            }
            else if (check == 2) {
                if (second_tree->is_empty())
                    cout << "second tree is empty" << endl;
                else if (cur->find_subtree(second_tree))
                    cout << "subtree found!" << endl;
                else
                    cout << "subtree not found" << endl;
            }
            check = 8;
        }
        else if (check == 9) {
            if (cur->is_empty())
                cout << "tree is empty" << endl;
            else
                cout << "tree isn`t empty" << endl;
        }
        else if (check == 10) {
            cout << cur->check_count() << " elements in tree" << endl;
        }
        else if (check == 11) {
            cur->print();
        }
    }
}

void test_is_empty_1() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    assert(!a->is_empty());
}

void test_is_empty_2() {
    BST<int>* a = new BST<int>;
    assert(a->is_empty());
}

void test_check_count() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(22);
    assert(a->check_count() == 2);
}

void test_insert_1() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    assert(a->what_in_root() == 13);
}

void test_insert_2() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(22);
    assert(a->what_in_node(a->tree_max()) == 22);
}

void test_delete_1() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->delete_node(13);
    assert(a->is_empty() == 1);
}

void test_max() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    assert(a->what_in_node(a->tree_max()) == 25);
}

void test_min() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    assert(a->what_in_node(a->tree_min()) == 5);
}

void test_delete_2() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(22);
    a->insert(7);
    a->delete_node(7);
    assert(a->check_count() == 2);
    assert(a->what_in_node(a->tree_min()) == 13);
}

void test_search_1() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    assert(a->what_in_node(a->search(13)) == 13);
    assert(a->what_in_root() == 13);
}

void test_search_2() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(22);
    a->insert(7);
    assert(a->what_in_node(a->search(22)) == 22);
}

void test_KLP() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    vector <int> exp = { 13 , 7 , 5 , 10 , 22 , 17 , 25 };
    for (int i = 0; i < a->check_count(); i++) {
        assert((*a->KLP())[i] == exp[i]);
    }
}

void test_KPL() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    vector <int> exp = { 13 , 22 , 25 , 17 , 7 , 10 , 5 }; 
    for (int i = 0; i < a->check_count(); i++) {
        assert((*a->KPL())[i] == exp[i]);
    }
}

void test_LKP() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    vector <int> exp = { 5 , 7 , 10 , 13 , 17 , 22 , 25 };
    for (int i = 0; i < a->check_count(); i++) {
        assert((*a->LKP())[i] == exp[i]);
    }
}

void test_LPK() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    vector <int> exp = { 5 , 10 , 7 , 17 , 25 , 22 , 13 };
    for (int i = 0; i < a->check_count(); i++) {
        assert((*a->LPK())[i] == exp[i]);
    }
}

void test_PLK() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    vector <int> exp = { 25 , 17 , 22 , 10 , 5 , 7 , 13 };
    for (int i = 0; i < a->check_count(); i++) {
        assert((*a->PLK())[i] == exp[i]);
    }
}

void test_PKL() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    vector <int> exp = { 25 , 22 , 17 , 13 , 10 , 7 , 5 };
    for (int i = 0; i < a->check_count(); i++) {
        assert((*a->PKL())[i] == exp[i]);
    }
}

void test_vhozhdenie_1() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    BST<int>* b = new BST<int>;
    assert(b->is_empty());
    assert(a->find_subtree(b));
}

void test_vhozhdenie_2() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    BST<int>* b = new BST<int>;
    b->insert(13);
    b->insert(7);
    b->insert(22);
    assert(a->find_subtree(b));
}
void test_vhozhdenie_3() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    BST<int>* b = new BST<int>;
    b->insert(13);
    b->insert(22);
    b->insert(17);
    b->insert(25);
    assert(a->find_subtree(b));
}

void test_vhozhdenie_4() {
    BST<int>* a = new BST<int>;

    BST<int>* b = new BST<int>;
    b->insert(13);
    b->insert(22);
    b->insert(17);
    b->insert(25);
    assert(!a->find_subtree(b));
}

void test_vhozhdenie_5() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    BST<int>* b = new BST<int>;
    b->insert(13);
    b->insert(22);
    b->insert(17);
    b->insert(25);
    b->insert(7);
    b->insert(5);
    b->insert(13);
    assert(a->find_subtree(b));
}

void test_izvlechenie_1() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    BST<int>* b = new BST<int>;
    b = a->eject(a->search(22));
    assert(a->check_count() == 7); // проверили, что с а всё ок
    assert(b->check_count() == 3);
    assert(b->what_in_root() == 22);
    assert((*b->KLP())[0] == 22);
    assert((*b->KLP())[1] == 17);
    assert((*b->KLP())[2] == 25);
}

void test_izvlechenie_2() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    BST<int>* b = new BST<int>;
    b = a->eject(a->search(17));
    assert(a->check_count() == 7);
    assert(b->check_count() == 1);
    assert(b->what_in_root() == 17);
}

void test_izvlechenie_3() {
    BST<int>* a = new BST<int>;
    a->insert(13);
    a->insert(7);
    a->insert(22);
    a->insert(5);
    a->insert(10);
    a->insert(17);
    a->insert(25);
    BST<int>* b = new BST<int>;
    b = a->eject(a->search(13));
    assert(a->check_count() == 7);
    assert(b->check_count() == 7);
    for (int i = 0; i < 7; i++) {
        assert( (*a->KLP())[i] == (*b->KLP())[i]);
    }
    for (int i = 0; i < 7; i++) {
        assert((*a->LKP())[i] == (*b->LKP())[i]);
    }
    for (int i = 0; i < 7; i++) {
        assert((*a->PKL())[i] == (*b->PKL())[i]); // проверю 3 варианта
    }
}

void TestALL() {
    test_check_count();
    test_delete_1();
    test_delete_2();
    test_min();
    test_max();
    test_insert_1();
    test_insert_2();
    test_is_empty_1();
    test_is_empty_2();
    test_izvlechenie_1();
    test_izvlechenie_2();
    test_izvlechenie_3();
    test_vhozhdenie_1();
    test_vhozhdenie_2();
    test_vhozhdenie_3();
    test_vhozhdenie_4();
    test_vhozhdenie_5();
    test_KLP();
    test_KPL();
    test_PKL();
    test_PLK();
    test_LKP();
    test_LPK();
    test_search_1();
    test_search_2();
}





int main() {
    TestALL();
    interface();
    return 0;
}