#ifndef STACK
#define STACK
#include <iostream>



template <typename T>
class Stack
{
private:
    //the struct for a element in the stack
    struct Node{
        Node * prevElement;
        T value;
        Node(){
        }
        Node(T val){
            value = val;
            prevElement = NULL;
        }
    };

    Node * topElement = new Node();
    int count;
public:

    Stack() {
        count = 0;
    }
    ~Stack(){}

    //if the stack is empty
    bool empty(){
        return (count == 0);
    }

    //size of the stack
    int size(){
        return count;
    }

    //push element to the stack
    void push(T value){
        Node * newElement = new Node(value);
        if(count == 0){
            topElement = newElement;
        }
        else{
            newElement->prevElement = topElement;
            topElement = newElement;
        }
        count++;
    }

    //return top element of the stack
    T top(){
        return topElement->value;
    }

    //pop top element from the stack
    void pop(){
           if(!empty()){
               Node* temp = topElement;
               topElement = topElement->prevElement;
               delete temp;
               count--;
           }else{
               std::cout << "Errroorr! The stack is empty!" << std::endl;
           }
    }
};


#endif // STACK

