#include <cassert>
#include <iostream>
#include <memory>

///////////////////////////////
// Здесь во всем коде,который скопирован из урока про бинарные деревья
// из unique_ptr указателей получаем сырые указатели при помощи метода .get()
//////////////////////////////////

template <typename T>
struct TreeNode;

template <typename T>
using TreeNodePtr = std::unique_ptr<TreeNode<T>>;

template <typename T>
struct TreeNode {
    // Используйте TreeNodePtr<T> вместо сырых указателей
    // Примите умные указатели по rvalue-ссылке
    TreeNode(T val, TreeNodePtr<T>&& left, TreeNodePtr<T>&& right)
        : value(std::move(val))
        , left(std:: move(left))
        , right(std::move(right)) {
    }

    T value;
    //////////////////////////////////////////////////////////////////////////////////
    TreeNodePtr<T> left;  // Замените TreeNode* на TreeNodePtr<T>
    TreeNodePtr<T> right; // Замените TreeNode* на TreeNodePtr<T>

    TreeNode(TreeNode&&) = default;

    TreeNode& operator= (TreeNode&&) = default;
    ///////////////////////////////////////////////////////////////////////////////

    TreeNode* parent = nullptr;
};

template <typename T>
bool CheckTreeProperty(const TreeNode<T>* node) noexcept {
    //флаг проверки того, что функция соответствует свойствам бинарного дерева
    bool flag = false;
    //если величина value левого узла не равна nullptr
    if (&node->left->value != nullptr) {
        //если величина узла value больше чем величина value левой ветви этого узла
        if (node->value > node->left->value) {
            flag = true;
        }
        //если не так - то дерево не является бинарным отсортированным
        else {
            return false;
        }
        //также проверяем что величина левого от левого от основного узла не равна nullptr
        //или что величина левого от правого от основного узла не равна nullptr
        //если так то проваливаемся в следующие условия
        //здесь обходим только конкретные деревья из условия? Откуда именно такая логика? 
        if (&node->left->left->value != nullptr || &node->left->right->value != nullptr) {
            //если в левой ветви узла ничего нет
            ///////////////////////////////////////////////////////////////////
            if (!CheckTreeProperty<T>(node->left.get())) {
                ////////////////////////////////////////////////////////////////
                //то дерево не соответствует условиям
                return false;
            }
            else {
                //если есть - то соответствует
                flag = true;
            }
        }
    }

    //проходим по правым ветвям
    if (&node->right->value != nullptr) {
        if (node->value < node->right->value) {
            flag = true;
        }
        else {
            return false;
        }
        if (&node->right->left->value != nullptr || &node->right->right->value != nullptr) {
            ////////////////////////////////////////////////////
            if (!CheckTreeProperty<T>(node->right.get())) {
                //////////////////////////////////////////////////
                return false;
            }
            else {
                flag = true;
            }
        }
    }

    if (&node->left->value != nullptr && &node->right->value != nullptr) {
        if (&node->left->right->value != nullptr) {
            if (node->left->right->value > node->right->value) {
                return false;
            }
        }
        if (&node->right->left->value != nullptr) {
            if (node->right->left->value < node->left->value) {
                return false;
            }
        }
    }

    return flag;
}

template <typename T>
TreeNode<T>* begin(TreeNode<T>* node) noexcept {
    // Реализуйте функцию
    // место для вашей реализации
    if (node->left != nullptr) {
        return begin(node->left.get());
    }
    return node;
}

template <typename T>
TreeNode<T>* next(TreeNode<T>* node) noexcept {
    if (node->right != nullptr) {
        return begin(node->right.get());
    }
    auto x = node;
    auto y = node->parent;
    while ((y != nullptr) && (x == y->right.get())) {
        x = y;
        y = y->parent;
    }
    return y;
}

// функция создаёт новый узел с заданным значением и потомками
TreeNodePtr<int> N(int val, TreeNodePtr<int>&& left = {}, TreeNodePtr<int>&& right = {}) {
    TreeNodePtr<int> result = std::make_unique<TreeNode<int>>(val, std::move(left), std::move(right));

    if (result->left != nullptr) {
        result->left->parent = result.get();
    }
    if (result->right != nullptr) {
        result->right->parent = result.get();
    }

    return result;
}

int main() {
    using namespace std;
    using T = TreeNode<int>;
    auto root1 = N(6, N(4, N(3), N(5)), N(7));
    assert(CheckTreeProperty(root1.get()));

    T* iter = begin(root1.get());
    while (iter) {
        cout << iter->value << " "s;
        iter = next(iter);
    }
    cout << endl;

    auto root2 = N(6, N(4, N(3), N(5)), N(7, N(8)));
    assert(!CheckTreeProperty(root2.get()));

    // Функция DeleteTree не нужна. Узлы дерева будут рекурсивно удалены
    // благодаря деструкторам unique_ptr
}
