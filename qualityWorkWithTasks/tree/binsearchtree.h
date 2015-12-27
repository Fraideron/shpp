#ifndef BINSEARCHTREE
#define BINSEARCHTREE


template <typename T>
class BinSearchTree {
private:

    struct Node {
        Node * left;
        Node * right;
        Node * parent;
        T data;

        Node (T key) {
            data = key;
            left = 0;
            right = 0;
            parent = 0;
        }

        ~Node(){
            left = 0;
            right = 0;
        }

        void insert(T key) {
            if (key > data) {
                if (right) {
                    right->insert(key);
                } else {
                    right = new Node(key);
                    right->parent = this;
                }
            } else {
                if (left) {
                    left->insert(key);
                } else {
                    left = new Node(key);
                    left->parent = this;
                }
            }
        }


        bool contains(T key){
            if(key < data){
                if (left) {
                    left->contains(key);
                } else {
                    return false;
                }
            } else if(key > data){
                if (right) {
                    right->contains(key);
                } else {
                    return false;
                }
            } else if(key == data)
                return true;
            else
                return false;
        }

        bool remove(T key){
            if(key < data){
                if (left) {
                    return left->remove(key);
                } else {
                    return false;
                }
            } else if(key > data){
                if (right) {
                    return right->remove(key);
                } else {
                    return false;
                }
            }
            else if((left) && (right)){
                if(right->left != 0){
                    Node * mostRightLeftChild = (right->findMostLeft());
                    mostRightLeftChild->parent->left = 0;

                    mostRightLeftChild->left = left;
                    mostRightLeftChild->right = right;
                    mostRightLeftChild->parent = parent;
                    if(mostRightLeftChild->data > parent->data){
                        parent->left = mostRightLeftChild;
                    } else{
                        parent->right = mostRightLeftChild;
                    }
                } else{
                    Node * rightChildFromRoot = right;
                    rightChildFromRoot->parent = 0;
                    rightChildFromRoot->left = left;
                    left->parent = rightChildFromRoot;
                   }
            } else {
                if (left) {
                    Node * tempNodeForLeftTree = left;
                    tempNodeForLeftTree->parent = parent;
                    parent->left = tempNodeForLeftTree;
                    if(tempNodeForLeftTree->data > parent->data){
                        parent->right = tempNodeForLeftTree;
                    }
                    else{
                        parent->left = tempNodeForLeftTree;
                    }
                } else if (right) {
                    Node * tempNodeForRightTree = right;
                    tempNodeForRightTree->parent = parent;
                    if(tempNodeForRightTree->data > parent->data){
                        parent->right = tempNodeForRightTree;
                    }
                    else{
                        parent->left= tempNodeForRightTree;
                    }
                }
            }

            return true;
        }



        Node *findMostLeft() {
            if (!left) return this;
            return left->findMostLeft();
        }

    };



public:
     Node *root;
    BinSearchTree() {
        root = 0;
    }

    void insert(T key) {
        if (root) root->insert(key);
        else {
            root = new Node(key);
            root->parent = 0;
        }
    }

    void showTree(){
        root->showTree(root);
    }


    bool contains(T key){
        if(root){
            return root->contains(key);
        }
        else{
            return false;
        }
    }

    bool remove(T key){
        if(root->contains(key)){
            return root->remove(key);
        } else {
            return false;
        }
    }

    Node *findMostLeft(){
        root->findMostLeft();
    }

    ~BinSearchTree() {}

};





#endif // BINSEARCHTREE

