#ifndef MYDEQUE
#define MYDEQUE

#define DATA_PART_SIZE 16
#include <vector>
#include <utility>


using namespace std;

template <typename T>

class MyDeque {
private:
    typedef pair<pair<int,int>,T*> valueOfVector;
    vector<valueOfVector> dequeConnector;
    int lastPiece,                // the last number of storage
    topPiece,                     // the top number of storage
    positionOfLastPart,           // position to add an element to the end
    positionOfTopPart;            // position to add an element to the head

public:
    MyDeque() {
        T* tmp = new T[DATA_PART_SIZE];
        dequeConnector.push_back(valueOfVector(pair<int,int>(-1,-1), tmp));
        lastPiece = topPiece = 0;
        positionOfTopPart = DATA_PART_SIZE / 2;
        positionOfLastPart = positionOfTopPart - 1;
    }


    bool ifHeadOverflow() {
        return positionOfTopPart >= DATA_PART_SIZE - 1;
    }


    bool ifBottomPartOverflow() {
        return positionOfLastPart <= 0;
    }

    /**
    * @brief allocateHead - add a new storage part to the head of mass
    */
    void allocateHead() {
        T* tmp = new T[DATA_PART_SIZE];
        int newPart = dequeConnector.size();
        dequeConnector[topPiece].first.second = newPart;
        dequeConnector.push_back(
                    valueOfVector(pair<int,int>(topPiece,-1), tmp)
                    );
        topPiece = newPart;
        positionOfTopPart = 0;
    }
    /*
    * @brief allocateBottom -  add a new storage part to the bottom of mass
    */
    void allocateBottom() {
        T* tmp = new T[DATA_PART_SIZE];
        int newPart = dequeConnector.size();
        dequeConnector[lastPiece].first.first = newPart;
        dequeConnector.push_back(
                    valueOfVector(pair<int,int>(-1, lastPiece), tmp)
                    );
        lastPiece = newPart;
        positionOfLastPart = DATA_PART_SIZE - 1;
    }

    /**
    * @brief push_front - add element to the frontof data mass
    * @param data
    */
    void push_front(T data) {
        if (ifHeadOverflow()) allocateHead();
        (dequeConnector[topPiece].second)[positionOfTopPart++] = data;
    }

    /**
    * @brief push_back - add element to the end of data mass
    * @param data
    */
    void push_back(T data) {
        if (ifBottomPartOverflow()) allocateBottom();
        (dequeConnector[lastPiece].second)[positionOfLastPart--] = data;
    }



    ~MyDeque() {
        int limit = dequeConnector.size();
        for (int i=0; i<limit; ++i)
            delete dequeConnector[i].second;
    }
};


#endif // MYDEQUE

