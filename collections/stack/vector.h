/*
 * This is a library for simple work with diferent types of mass.
 */



#ifndef VECTOR
#define VECTOR
#include <c++/iostream>

#define START_SIZE 4

namespace VEC{

    template <typename V>
    class vector{
    private:
        int sizeVectr;
        int capacityVectr;
        V * mainStorage;

        void newSize(){
            capacityVectr *=2;
            V * newStorage = new V[capacityVectr];
            for (int i = 0; i < sizeVectr; ++i) {
                newStorage[i] = mainStorage[i];
            }
            delete[] mainStorage;
            mainStorage = newStorage;
        }

        void newSize(int size){
            if(capacityVectr > size){
                std::cout << "Errror!  Low new size!";
                return;
            }
            V * newStorage = new V[size];
            for (int i = 0; i < size; ++i) {
                newStorage[i] = mainStorage[i];
            }
            capacityVectr = size;
            delete[] mainStorage;
            mainStorage = newStorage;
            std::cout << "New size is: " << size;
        }

    public:

        vector<V>(){
            sizeVectr = 0;
            capacityVectr = START_SIZE;
            mainStorage = new V[START_SIZE];
        }

/*
*   push value to the vector
* ------------------------------
*   @param value - value for add
*   @return void
*/
        void push_back(V value){
            if(sizeVectr == capacityVectr){
                newSize();
            }
            mainStorage[sizeVectr] = value;
            sizeVectr++;
        }


/*
 * remove last element in the vector
 * ------------------------------
 *   @param value - value for add
 *   @return void
 */
        void pop_back(){
            if(empty()){
                std::cout << "The vector is empty";
                exit(-1);
            }
            sizeVectr--;
        }


/*
* Return vector's size
* ------------------------------
*   @return int
*/
        int size(){
            return sizeVectr;
        }
/*
* Return vector's capacity
* ------------------------------
*   @return int
*/
        int capacity(){
            return capacityVectr;
        }

/*
* Return true if the vector is empty
* ------------------------------
*   @return bool
*/

        bool empty(){
            return (!size());
        }

/*
* Set a new size of vector. If a new size is smaller then capasity, the program will be exit.
*
* @return int cpcity - a new size of the vector
*/
        void resize(int cpcity){
            newSize(cpcity);
        }

/*
*Return the string with vector's value
*
* @return string - vector's value
*/

        std::string toString();

/*
* Return the i's element
*
* @param i - element's position
*/
        V & operator[] (int i){
            return mainStorage[i];
        }

/*
*Return top value of the vector
*/
        V front(){
            return mainStorage[0];
        }


/*
*Return last value of the vector
*/
        V back(){
            return mainStorage[sizeVectr-1];
        }

/*
*Return value of the vector, at the "i" position
*
* @param int i - element's position
* @return V - value of the vector
*/
        V & at(int i){
            if((!empty()) && (i<sizeVectr)){
                if(i < 0){
                    return mainStorage[sizeVectr+i-1];
                }
                else{
                    return mainStorage[i];
                }
            }
            else{
                std::cout << "Out of range";
                exit(5);
            }
        }

//overloading operation
        vector<V> operator+( vector<V>& rhs);

        bool operator==(vector<V> & rhs);

        bool operator!=(vector<V> & rhs);

        vector<V>& operator=(vector<V>& rhs);
    };

    template <typename V>
    std::string vector<V>::toString() {
        std::string rezult;
        rezult = "Vector: {";
        rezult += mainStorage[0];
        for (int i = 1; i < sizeVectr; ++i) {
            rezult += ", ";
            rezult += mainStorage[i];
            std::cout << mainStorage[i];
        }
        rezult += "}";
        return rezult;
    }


    template <typename V>
    vector<V>& vector<V>::operator=(vector<V>& rhs) {
        delete[] mainStorage;
        sizeVectr= rhs.sizeVectr;
        for (int i = 0; i < rhs.sizeVectr; ++i) {
           mainStorage[i] = rhs.mainStorage[i];
        }
        return *this;
    }

    template <typename V>
    bool vector<V>::operator!=(vector<V> & rhs) {
        if (rhs.size() != vector<V>::sizeVectr)
            return true;
        for (int i = 0; i < vector<V>::sizeVectr; ++i) {
            if (rhs[i] != vector<V>::mainStorage[i])
                return true;
        }
        return false;
    }


    template <typename V>
    bool vector<V>::operator==(vector<V> & rhs) {
        if (rhs.size() != vector<V>::sizeVectr)
            return false;
        for (int i = 0; i < vector<V>::sizeVectr; ++i) {
            if (rhs[i] != vector<V>::mainStorage[i])
                return false;
        }
        return true;
    }

    template <typename V>
    vector<V> vector<V>::operator+(vector<V>& rhs) {
        vector<V>* temp = new vector<V>();

        for (int i = 0; i < vector<V>::sizeVectr; ++i) {
            temp->push_back(vector<V>::mainStorage[i]);
        }

        int size = rhs.size();

        for (int j = 0; j < size; ++j) {
            temp->push_back(rhs[j]);
        }

        return *temp;
    }

}


#endif // VECTOR

