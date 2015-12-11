#ifndef LNKL
#define LNKL

#include <iostream>




template <typename NODE_T>
class LinkList
{
private:

    struct Node{
        Node* next;
        Node* prev;
        NODE_T value;

        Node(){}

        Node(NODE_T val){
            next = NULL;
            prev = NULL;

            value = val;
        }

    };

    Node* top = new Node();
    Node* last = new Node();

    int count;

public:

    LinkList<NODE_T>() {
        top = NULL;
        last = NULL;

        count = 0;


    }





    ~LinkList(){
        std::cout << "Destr";
        count = 0;


        Node* temp = last;
        while(last->next != NULL)
        {
            last = last->next;
            delete last;
        }

        delete temp;
    }


    int size(){
        return count;
    }


    void clear(){
         count = 0;
         delete top;
         delete last;
    }

    void push_back(NODE_T value){
        Node* newElement = new Node(value);
        if(size() == 0){
            top = newElement;
            last = top;
        }
        else{
            newElement->next= last;
            last->prev= newElement;
            last = newElement;
        }
        count++;

    }

    void push_front(NODE_T value){
        Node* newElement = new Node(value);
        if(size() == 0){
            top = newElement;
            last = top;
        }
        else{
            newElement->prev = top;
            top->next= newElement;
            top = newElement;
            std::cout << newElement->prev->value << std::endl;
        }
        count++;
    }

    NODE_T front(){
        return top->value;
    }

    bool empty(){
        return (count == 0);
    }

    NODE_T back(){
        return last->value;
    }

    void pop_front(){
        if(size() == 0){
            std::cout << "Eeeerrooorr!";
        }
        else{
            Node* temp = top;
            top = top->prev;
            delete temp;
            count--;
        }
    }

    void pop_back(){
        if(size() == 0){
            std::cout << "Eeeerrooorr!";
        }
        else{
            Node* temp = last;
            last = last->next;
            delete temp;
            count--;
        }
    }



};
#endif // LNKL

