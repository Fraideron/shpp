#ifndef STACK
#define STACK
#include <iostream>



template <typename T>
class Stack
{
private:
    T* storage;  // first element in the stack
    int count;
    int capac = 20;

public:

    Stack(){
        count = 0;
        storage = new T[capac];
    }

    ~Stack(){
        delete storage;
        count = 0;
    }

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
      storage[count++] = value;
    }

    //return top element of the stack
    T top(){
        return storage[count-1];
    }

    //pop top element from the stack
    void pop(){
        if(!empty()){
            count--;
        }
    }
};


#endif // STACK

