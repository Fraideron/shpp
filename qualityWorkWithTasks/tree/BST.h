//
// Created by Fraid on 05.01.2016.
//

#ifndef BINARYTREE_BINTREE_H
#define BINARYTREE_BINTREE_H

template<typename T>
class Node {
private:
    T value;
    int height;
    Node *left;
    Node *right;
public:
    Node() {
        value = 0;
        left = 0;
        right = 0;
        height = 0;
    };

    Node(T val) {
        this->value = val;
        left = 0;
        right = 0;
    }

    void setHeight(int newHeight) {
        height = newHeight;
    }

    T getValue() {
        return value;
    }

    int getHeight() {
        return height;
    }

    Node *getLeft() {
        return left;
    }

    Node *getRight() {
        return right;
    }

    void setLeft(Node *lft) {
        left = lft;
    }

    void setRight(Node *rght) {
        right = rght;
    }

};

template<typename T>
class BST {
private:
    Node<T>* insertPrvt(Node<T> *node, T value) {
        if (!node) {
            node = new Node<T>(value);
            return node;
        } else {
            if (value < node->getValue()) {
                node->setLeft(insertPrvt(node->getLeft(), value));
            } else if(value > node->getValue()){
                node->setRight(insertPrvt(node->getRight(), value));
            }
        }
        return balance(node);
    }


    Node<T> *removePrvt(Node<T> *node, T key) {
        if (!node)
            return NULL;
        if (key < node->getValue()) {
            node->setLeft(removePrvt(node->getLeft(), key));
        } else if (key > node->getValue()) {
            node->setRight(removePrvt(node->getRight(), key));
        } else if ((node->getLeft()) && (node->getRight())) {
            node = findMinimumNode(node->getRight());
            node->setRight(removePrvt(node->getRight(), node->getValue()));
        } else {
            if (node->getLeft()) {
                node = node->getLeft();
            } else {
                node = node->getRight();
            }
        }
        return node;
    }


    int height(Node<T> *node) {
        return (!node) ? 0 : node->getHeight();
    }


    int balanceFactor(Node<T> *node) {
        return height(node->getRight()) - height(node->getLeft());
    }

/* Корректировка высоты дерева */
    void fixHeight(Node<T> *node) {
        int hl = height(node->getLeft());
        int hr = height(node->getRight());
        node->setHeight(((hl > hr) ? hl : hr) + 1);
    }


    Node<T> *findMinimum(Node<T> *node) {
        if(!node->getLeft()){
            return node;
        } else{
            return  findMinimum(node->getLeft());
        }
    }


    Node<T> *removeMinimum(Node<T> *node) {
        if (!node->getLeft())
            return node->getRight();
        node->setLeft(removeMinimum(node->getLeft()));
        return balance(node);
    }


    Node<T> *rotateRight(Node<T> *node) {
        Node<T> *l = node->getLeft();
        node->setLeft(l->getRight());
        l->setRight(node);
        fixHeight(node);
        fixHeight(l);
        return l;
    }


    Node<T> *rotateLeft(Node<T> *n) {
        Node<T> *r = n->getRight();
        n->setRight(r->getLeft());
        r->setLeft(n);
        fixHeight(n);
        fixHeight(r);
        return r;
    }

    Node<T> *balance(Node<T> *node) {
        fixHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->getRight()) < 0)
                node->setRight(rotateRight(node->getRight()));
            return rotateLeft(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->getLeft()) > 0)
                node->setLeft(rotateLeft(node->getLeft()));
            return rotateRight(node);
        }
        return node;
    }


public:

    Node<T> *root;

    BST() : root(0) {

    }

    void insert(T value) {
        if (!root) {
            root = new Node<T>(value);
        } else {
            insertPrvt(root, value);
        }
    }


    void remove(T value) {
        removePrvt(root, value);
    }

    Node<T> *findMinimumNode(Node<T> *node) {
        if (!node->getLeft())
            return node;
        return findMinimumNode(node->getLeft());
    }


};

#endif //BINARYTREE_BINTREE_H


