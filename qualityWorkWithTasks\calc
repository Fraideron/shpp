#include <iostream>
#include "stack.h"
#include <vector>
#include <cstdlib>
#include <sstream>
#include <math.h>

using namespace std;

/**
 * @brief The Calculator class  using an 
 *        algorithm sorting station has introduced expression
 */
class Calculator
{
private:
    string inputString ;
    Stack<string> * tempStack ;
    vector<string> * polishNotation;
public:
    Calculator(string function = "2+2") {
        inputString = function;
        tempStack = new Stack<string>;
        polishNotation = new vector<string>;
    }

    ~Calculator() {
        delete tempStack;
        delete polishNotation;
    }



    /**
     * @brief getTokenType - function returns the value of int to separate tokens
     * @param token
     * @return type of token
     */
    int getTokenType(char token){
        if(isdigit(token)){
            return 0;
        } else if(token == '+' || token == '-' || token == '*' || token == '/' || token == '^'){
            return 1;
        } else if(isalpha(token)){
            return 2;
        } else if(token == '(' || token == ')'){
            return 3;
        }
    }

    /**
     * @brief getOneTokenFromInputString - function returns a token starting with position 'i'
     * @param position - position of token start
     * @param functionString - string  for calculation
     * @return string value(token)
     */
    string getOneTokenFromInputString(int& position, string & functionString){
        string outputString;

        char current = functionString[position];
        char next = functionString[position+1];

        while ((getTokenType(current) == getTokenType(next)) && position < functionString.size()) {
            outputString += current;
            position++;
            current = next;
            next = functionString[position+1];
        }

        outputString += current;
        ++position;
        return outputString;
    }

    /**
     * @brief getTokenPriority - priority function returns each input token
     * @param token - token to check
     * @return int value - priority
     */
    int getTokenPriority (char token){
        if(token == '+' || token == '-' ){
            return 1;
        }else if(token == '*' || token == '/'){
            return 3;
        }else if(token == '^'){
            return 4;
        }else if(token == '(' || token == ')'){
            return 0;
        } else {
            return 3;
        }
    }



    /**
     * @brief getPolishNotationFromString - using a standard algorithm, 
     *                                      we obtain the inverse Polish notation 
     *                                      from the input line
     */
    getPolishNotationFromString(){
        for (int i = 0; i < inputString.size(); ) {
            string token = getOneTokenFromInputString(i, inputString);
            int tokenType = getTokenPriority(token[0]);

            if(isdigit(token[0]))  {
                polishNotation->push_back(token);
            } else if (token == "(") {
                tempStack->push(token);
            } else if(token == ")"){
                while((tempStack->top() != "(") && (!tempStack->empty())) {
                    polishNotation->push_back(tempStack->top());
                    tempStack->pop();
                }
                tempStack->pop();
            } else if((tokenType == 4) || (tokenType == 3) || (tokenType == 1) || (tokenType == 2) ){
                if(tempStack->empty()){
                    tempStack->push(token);
                    continue;
                }

                while((!tempStack->empty()) && tokenType < getTokenPriority(tempStack->top()[0]) ){
                    polishNotation->push_back(tempStack->top());
                    tempStack->pop();
                }
                tempStack->push(token);
            }
        }

        while (!tempStack->empty()) {
            polishNotation->push_back(tempStack->top());
            tempStack->pop();
        }

    }
    /**
     * @brief stringToDouble convert  string to double
     * @param str - input data
     * @return 
     */
    double stringToDouble(string str){
        stringstream ss(str);
        double convertedValue = 0;
        ss >> convertedValue;
        return convertedValue;
    }

    /**
     * @brief doubleToString convert double to string
     * @param doub
     * @return
     */
    string doubleToString(double doub){
        ostringstream strs;
        strs << doub;
        string str = strs.str();
        return str;

    }
    /**
     * @brief getFunctionParamNumber - function returns the number of operands 
     *                                 required for the operation
     * @param token - operation
     * @return int value
     */
    int getFunctionParamNumber(string token){
        if ((token == "cos") || (token == "sin")) {
            return 1;
        } else if(token == "*" ||
                  token == "/" ||
                  token == "+" ||
                  token == "-" ||
                  token == "^" ){
            return 2;
        } else{
            return 0;
        }
    }

    /**
     * @brief calculateInputFunction - using inverse Polish notation, 
     *                                 this function is operation calculates 
     *                                 the required number of operands, 
     *                                 perform actions on the data obtained, 
     *                                 deletes them and adds the result in the removal of seat
     */
    void calculateInputFunction(){


        for (int i = 0; i < polishNotation->size(); i++) {
            string token = polishNotation->at(i);


            if (getFunctionParamNumber(token) == 2) {
                int firstArg = stringToDouble(polishNotation->at(i-1));
                int secondArg = stringToDouble(polishNotation->at(i-2));
                double rezult;
                if (token == "+") {
                    rezult = firstArg + secondArg;
                } else if(token == "-") {
                    rezult = firstArg - secondArg;
                } else if(token == "/"){
                    rezult = firstArg / secondArg;
                } else if(token == "*"){
                    rezult = firstArg * secondArg;
                } else if (token == "^"){
                    rezult = pow(firstArg, secondArg);
                }

                polishNotation->erase(polishNotation->begin()+i);
                polishNotation->erase(polishNotation->begin()+i-2);
                polishNotation->erase(polishNotation->begin()+i-2);
                polishNotation->insert(polishNotation->begin()+i-2, doubleToString(rezult));
            } else if(getFunctionParamNumber(token) == 1){
                int firstArg = stringToDouble(polishNotation->at(i-1));
                double rezult;
                if(token == "cos"){
                    rezult = cos(firstArg);
                } else if(token == "sin"){
                    rezult = sin(firstArg);
                }
                polishNotation->erase(polishNotation->begin()+i);
                polishNotation->erase(polishNotation->begin()+i-1);
                polishNotation->insert(polishNotation->begin()+i-1, doubleToString(rezult));
                i--;
            }

        }
        cout << (*polishNotation)[0];

    }
};





int main()
{
    


    Calculator calc;
    calc.getPolishNotationFromString();


    calc.calculateInputFunction();

    return 0;
}

