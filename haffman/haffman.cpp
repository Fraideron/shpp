#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <iterator>

using namespace std;

vector<bool> code;
map<char,vector<bool> > table;

/*
*   Main class with node struct for tree.
*/
class Node{
public:
    int a;
    char c;
    Node *left, *right;

    Node(){
        left=right=NULL;
    }

    Node(Node *L, Node *R){
        c = ' ';
        left =  L;
        right = R;
        a = L->a + R->a;
    }
};

//For sorting list
struct MyCompare
{
    bool operator()(Node* l, Node* r) const{
        return (l->a) < (r->a);
    }
};


/**
 * @brief buildTreeForHuffman - Calculate the frequency of each character
                                Make list with nodes for the tree.
                                Build tree( to addition two weight of nodes, make a new node, and to add new node in the tree)
 *
 * @param inputData - all input chars
 * @return Node* root of tree
 */
Node* buildTreeForHuffman(vector<char> *inputData){
    map<char, int> chastotu;
     for (int i = 0; i < inputData->size(); ++i) {
         char c = inputData->at(i);
         chastotu[c]++;
     }


     map<char, int>::iterator itr;

     list<Node*> tempListForTree;
     for ( itr = chastotu.begin(); itr != chastotu.end(); itr++) {
         Node *p = new Node();
         p->c = itr->first;
         p->a = itr->second;
         tempListForTree.push_back(p);

     }


    while (tempListForTree.size()!=1){
        tempListForTree.sort(MyCompare());

        Node *SonL = tempListForTree.front();
        tempListForTree.pop_front();

        Node *SonR = tempListForTree.front();
        tempListForTree.pop_front();

        Node *parent = new Node(SonL,SonR);
        tempListForTree.push_back(parent);
    }
    
    Node *root = tempListForTree.front();
     
    return root;
}

/*
* This function make code for symbol.
* And write this code in the map.
* if go left way +0
* if go right way +1
* if can't go - write way to the map
*
* @param root - root of the tree
*/
void BuildTable(Node *root){
  if (root->left!=NULL){
      code.push_back(0);
      BuildTable(root->left);
  }

  if (root->right!=NULL){
      code.push_back(1);
      BuildTable(root->right);
    }

  if (root->c){
    table[root->c]=code;
  }

  code.pop_back();
}





/**
 * @brief readFile - this function read file, binary
 * @param nameOfsourceFile
 * @return vector<char> - it contains all the characters read from the file
 */
vector<char>* readFile(){
    ifstream input("debug/test.txt", ios::binary);
    // copies all data into buffer
    char symb;
    vector<char> *rezult = new vector<char>();
    while(input.get(symb)){
        rezult->push_back(symb);
    }
    input.close();
    return rezult;
}


/**
 * @brief codeFile - write to the file size of map,
 *                   and next structure:
 *                   1) - character
 *                   2) - code size
 *                   3) - code for character
 *                   This is for decodding file.
 *                   After this to make the vector of boolean values and to add their codes all characters
 *
 * @param table - map with character and him code
 * @param codeForFile - vector of boolean values for codding file
 */

void codeFile(map<char, vector<bool> > table,  vector<bool> & codeForFile ){

    ofstream output;
    output.open ("debug/codeFile", ios::binary );

    int sizeOfMap = table.size();
    output.write((char*) &sizeOfMap, sizeof(int));
    cout << sizeOfMap << endl;

    for(map<char, vector<bool> >::iterator itrt = table.begin(); itrt!= table.end(); itrt++){
        output.put(itrt->first);

        vector<bool> codeOfChar = itrt->second;

        int sizeOfCodeChar = codeOfChar.size();
        output.write((char*) &sizeOfCodeChar, sizeof(int));

        cout << itrt->first <<" "<< sizeOfCodeChar << endl;

        int codeSymbol;
        for (int i = 0; i < sizeOfCodeChar; ++i) {
             codeSymbol = (codeSymbol << 1) | codeOfChar[i];
        }

        output.write((char*) &codeSymbol, sizeof(int));
    }

    int codedSize = codeForFile.size();
    output << codedSize;

    while(codedSize%8 != 0){
        codeForFile.push_back(0);
        codedSize++;
    }
    int sizeOfCode = 0;
    char code;
    for (int i = 0; i < codedSize; ++i) {

        code = (code << 1) | (codeForFile.at(i));
        sizeOfCode++;
        if(sizeOfCode == 8){
            output << code;
            sizeOfCode = 0;
            code = 0;
        }
    }

    output.close();
}

/**
 * @brief decodeFile - for decodding use inverse codding algorithm
 * @param mainMapForDecode - map which will be entered values with code and him character
 * @return vector with boolean values, this is the source code of coded file
 */

vector<bool>* decodeFile( map<vector<bool>, char>* mainMapForDecode);


/**
 * @brief makeDecodedFile - create a new file, and to write there decoded data
 * @param codeForFile - vector with boolean values, this is the source code of coded file
 * @param mainMapForDecode - map with equals codes and characters
 */
void makeDecodedFile( vector<bool> * codeForFile, map<vector<bool>, char>* mainMapForDecode);


int main()
{


   vector<char> *inputData = new vector<char>;
   inputData = readFile();


   BuildTable(buildTreeForHuffman(inputData));


    vector<bool> codeForFile;
    for (int i = 0; i < inputData->size(); ++i) {
        vector<bool> temp = table[inputData->at(i)];
        for (int i = 0; i < temp.size(); ++i) {
            codeForFile.push_back(temp.at(i));
        }
    }

    codeFile(table, codeForFile);

    map<vector<bool>, char>* mainMapForDecode = new map<vector<bool>, char>();
    decodeFile(mainMapForDecode);

    return 0;
}

vector<bool>* decodeFile( map<vector<bool>, char>* mainMapForDecode){
    ifstream readFile("debug/codeFile", ios::binary);

    int sizeOfMainMap;
    readFile.read((char*) &sizeOfMainMap, sizeof(int));

    for (int i = 0; i < sizeOfMainMap; ++i) {
        char key;
        readFile.get(key);

        int sizeOfCodeChar;
        readFile.read((char*) &sizeOfCodeChar, sizeof(int));

        int dataOfCode = 0;
        readFile.read((char*) &dataOfCode, sizeof(int));

        vector<bool> codeOfChar;
        dataOfCode = dataOfCode << (sizeof(dataOfCode) * 8 - sizeOfCodeChar);
        for(char u = 0; u < sizeOfCodeChar; u++){
            codeOfChar.push_back(dataOfCode < 0);
            dataOfCode = dataOfCode << 1;
        }
        (*mainMapForDecode)[codeOfChar] = key;
    }

    int codedSize = 0;
    vector<bool> *codeForFile = new vector<bool>();
    readFile >> codedSize;
    for (int i = 0; i < codedSize;) {
        char tmp;
        readFile.get(tmp);
        for (int j = 0; (j < 8)&&(i < codedSize); j++,i++) {
            codeForFile->push_back(tmp & 0b10000000);
            tmp <<= 1;
        }
    }
    readFile.close();

    return codeForFile;
}

void makeDecodedFile( vector<bool> * codeForFile, map<vector<bool>, char>* mainMapForDecode){

    ofstream writeFile("debug/magic.txt", ios::binary);
    vector<bool> key;
    vector<bool>::iterator iter = codeForFile->begin();
    while(iter != codeForFile->end()) {
        key.push_back(*iter);
        if(mainMapForDecode->count(key)) {
            writeFile.put((*mainMapForDecode)[key]);
            key.clear();
        }
        iter++;
    }

    writeFile.close();

}
