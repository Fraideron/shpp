#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <sstream>



//095-129-29-69 - Max
using namespace std;

string findTokens(int & tempPosition, string resString){
    string token = "";

    if(tempPosition < resString.size() && isdigit(resString.at(tempPosition))  )
    {
        while(tempPosition < resString.size() &&
              resString.at(tempPosition) != '(' &&
              resString.at(tempPosition) != ')' &&
              !isalpha(resString.at(tempPosition)) &&
              resString.at(tempPosition) != '+' &&
              resString.at(tempPosition) != '-' &&
              resString.at(tempPosition) != '=' &&
              resString.at(tempPosition) != '/' &&
              resString.at(tempPosition) != '*')
            {
                token += resString.at(tempPosition++);
            }
        tempPosition--;
        return  token;
    }


    switch (resString.at(tempPosition)) {
    case ')':
        return ")";
    case '(':
        return "(";
    case '+':
        return "+";
    case '-':
        return "-";
    case '/':
        return "/";
    case '*':
        return "*";
    case '=':
        return "=";
    }


}

double stringToDouble(string str){
    stringstream ss(str);
    double convertedValue = 0;
    ss >> convertedValue;
    return convertedValue;
}

string doubleToString(double doub){
    ostringstream strs;
    strs << doub;
    string str = strs.str();
    return str;

}

double countInputFunc(vector<string> & out){
    for (int i = 0; i < out.size(); i++) {
        cout << "one more " << endl;
        cout << out.at(i);
        if(!isdigit(out.at(i)[0])){
            int tempPos = i;
            double firstArgument = stringToDouble(out.at(tempPos-2));
            double secondArgument = stringToDouble(out.at(tempPos-1));
            double rez = 0;
            cout << endl;
            switch (out.at(i)[0]) {
            case '+':
                cout << firstArgument <<  "+" << secondArgument;
                rez = firstArgument + secondArgument;
                cout <<"rez" << rez<< endl;
                break;
            case '-':
                cout << firstArgument <<  "-" << secondArgument;
                rez = firstArgument - secondArgument;
                cout <<"rez" << rez<< endl;
                break;
            case '*':
                cout << firstArgument <<  "*" << secondArgument;
                rez = firstArgument * secondArgument;
                cout <<"rez" << rez<< endl;
                break;
            case '/':
                cout << firstArgument <<  "/" << secondArgument;
                rez = firstArgument / secondArgument;
                cout <<"rez" << rez<< endl;
                break;
            }

            string tempRez = doubleToString(rez);
            cout << "tempRez" << rez << endl;


             out.erase(out.begin()+i);
             out.erase(out.begin()+i-2);
             out.erase(out.begin()+i-2);



            out.insert(out.begin()+i-2, tempRez);
            cout << "Polish notation: ";
            for (int i = 0; i < out.size(); ++i) {
                cout <<  out.at(i);
            }
            i -= 2;
            cout << endl << "i:" <<i;
         }
         cout << endl;


    }
}


int main()
{
    string resString = "81*3*(9-5)/2";
    vector<string> out;
    stack<char> operations;
    //check two operation mult or div one each other
    bool checkPossToken = false;
    for (int i = 0; i < resString.size(); i++) {

        string tempToken = findTokens(i, resString);

        //if token is digit
        if(isdigit(tempToken.at(0)))
            out.push_back(tempToken);

        if(!isdigit(tempToken.at(0))){

            char tmpOpr = tempToken.at(0);
            //if token is operation * or / and last operation-token was operation * or /
            if(tmpOpr == '*' && checkPossToken ||
               tmpOpr == '/' && checkPossToken){
                string temp = "";
                temp = operations.top();
                out.push_back(temp);
                operations.pop();
                operations.push(tmpOpr);
                continue;
            }


            if( tmpOpr == '*' || tmpOpr == '/' ){
                operations.push(tmpOpr);
                checkPossToken = true;
            }

            if( tmpOpr == '+' || tmpOpr == '-' ){
                operations.push(tmpOpr);
                checkPossToken = false;
            }

            if(tmpOpr == '('){
                operations.push(tmpOpr);
            }

            if(tmpOpr == ')'){
                while(operations.top() != '('){
                    string temp = "";
                    temp = operations.top();
                    out.push_back(temp);
                    operations.pop();
                }
                operations.pop();
                string temp = "";
                temp = operations.top();
                out.push_back(temp);
                operations.pop();
            }

        }

    }
    while (!operations.empty())
     {
        string temp = "";
        temp = operations.top();
        out.push_back(temp);
        operations.pop();
     }

    cout << "Polish notation: ";
    for (int i = 0; i < out.size(); ++i) {
        cout <<  out.at(i);
    }


    countInputFunc(out);
    cout << endl << "Rezult: " << out.at(0);

    return 0;
}

