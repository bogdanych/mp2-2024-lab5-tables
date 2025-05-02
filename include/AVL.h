#pragma once

#include <iostream>
#include <string>
#include <polynoms.h>

class Node_tree {
public:
    std::string key;
    Node_tree* left;
    Node_tree* right;
    int height;
    Polynom pol;

    Node_tree(const std::string& value, const Polynom& pol) : key(value), left(nullptr), right(nullptr), height(1), pol(pol) {}
};

class AVLTree {
private:
    Node_tree* root;
    int oper = 0;

    int getHeight(Node_tree* node) {
        oper++;
        if (node) {
            return node->height;
        }
        return 0;
    }

    int getBalance(Node_tree* node) {
        oper++;
        if (node) {
            return getHeight(node->left) - getHeight(node->right);
        }
        return 0;
    }

    Node_tree* rightRotate(Node_tree* y) {
        Node_tree* x = y->left;
        Node_tree* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        oper += 4;
        return x;
    }

    Node_tree* leftRotate(Node_tree* x) {
        Node_tree* y = x->right;
        Node_tree* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        oper += 4;
        return y;
    }

    Node_tree* balance(Node_tree* node) {
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0) {
            oper++;
            return rightRotate(node);
        }
        else if (balance < -1 && getBalance(node->right) <= 0) {
            oper += 2;
            return leftRotate(node);
        }
        else if (balance > 1 && getBalance(node->left) < 0) {
            oper += 3;
            node->left = leftRotate(node->left);
            oper++;
            return rightRotate(node);
        }
        else if (balance < -1 && getBalance(node->right) > 0) {
            oper += 4;
            node->right = rightRotate(node->right);
            oper++;
            return leftRotate(node);
        }
        return node;
    }

    Node_tree* insert(Node_tree* node, const std::string& key, const Polynom& pol) {
        if (!node) {
            oper++;
            return new Node_tree(key, pol);
        }
        else if (key < node->key) {
            oper += 2;
            node->left = insert(node->left, key, pol);
            oper++;
        }
        else if (key > node->key) {
            oper += 3;
            node->right = insert(node->right, key, pol);
            oper++;
        }
        else {
            oper += 4;
            return new Node_tree(key, pol); // ����� �� ���������
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        oper++;
        return balance(node);
    }

    Node_tree* get_value(Node_tree* node, const std::string& key) {
        if (!node) {
            oper++;
            return node;
        }
        if (key < node->key) {
            oper += 2;
            return get_value(node->left, key);
        }
        else if (key > node->key) {
            oper += 3;
            return get_value(node->right, key);
        }
        else {
            oper += 4;
            return node;
        }
    }

    Node_tree* ListFind(Node_tree* node) {
        Node_tree* current = node;
        while (current->left) {
            oper++;
            current = current->left;
        }
        return current;
    }

    Node_tree* remove(Node_tree* node, const std::string& key) {
        if (!node) {
            oper++;
            return node; // ���� �� ������
        }
        else if (key < node->key) {
            oper += 2;
            node->left = remove(node->left, key);
            oper++;
        }
        else if (key > node->key) {
            oper += 3;
            node->right = remove(node->right, key);
            oper++;
        }
        else {
            oper += 4;
            // ���� � ����� �������� ��� ��� ��������
            if (!node->left) {
                oper++;
                Node_tree* temp = node->right;
                delete node;
                return temp;
            }
            else {
                oper++;
                Node_tree* temp = node->left;
                delete node;
                return temp;
            }
            // ���� � ����� ���������, �������� ���������� ���� � ������ ���������
            Node_tree* temp = ListFind(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
            oper++;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        oper++;
        return balance(node);
    }

    void print(Node_tree* node) {
        if (node) {
            print(node->left);
            std::cout << node->key << " ";
            node->pol.display();
            print(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    bool search(const std::string& key) {
        return (get_value(root, key) != nullptr);
    }

    void insert(const std::string& key, const Polynom& pol) {
        root = insert(root, key, pol);
    }

    void remove(const const std::string& key) {
        root = remove(root, key);
    }

    void print() {
        print(root);
        //std::cout << '\n';
    }

    void get_cnt() {
        std::cout << oper << '\n';
        oper = 0;
    }

    Polynom& operator[] (const std::string& key)
    {
        Node_tree* ind = get_value(root, key);
        if (ind)
            return ind->pol;
        throw std::exception("������� �� ������");
    }

    void set_cnt() {
        oper = 0;
    }

};