#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <fstream>
#include "gbufferedimage.h"
using namespace std;

/*This func change pixels array to vector<vector<pair<bool, bool>>>
* pair: first param = color (0 = white, 1 = black)
*       second para = check (0 = not yet check, 1 = already check)
*
*@param img - a picture
*@pixels - main storage, for search
*
*/
void getColorMass(GBufferedImage & img, vector<vector<pair<bool, bool>>> & pixels){
    for (int y = 0; y < img.getHeight(); ++y) {
        vector<pair<bool,bool>> pixelsForWidth;
        for (int x = 0; x < img.getWidth(); ++x) {
           int tempColor = img.getRGB(x,y);
           if(img.getRed(tempColor) > 120 || img.getGreen(tempColor) > 120 || img.getBlue(tempColor) > 120 ){
               pixelsForWidth.push_back(make_pair(false, false)); //  pixel is white
           }
           else{
               pixelsForWidth.push_back(make_pair(true, false)); //  pixel is black
           }
        }
        pixels.push_back(pixelsForWidth);
    }
}



/*
This function simulates wide search
*if the pixel's color is blak, simulate search in depth and search all black pixels in this spot.
*Find all black spots.
*
* @param table - main storage of picture
*
* @return countSiluets - count of siluets
*
*/
int searchSiluets(vector<vector<pair<bool,bool>>> & table){
    int countSiluets = 0;
    int X_Lim = table.size();

    for (int x = 0; x < X_Lim; ++x) {
        int Y_Lim = table.at(x).size();
        for (int y = 0; y < Y_Lim; ++y) {
            if(!((table.at(x)).at(y)).second && ((table.at(x)).at(y)).first){
                countSiluets++;
                deque<pair<int,int>> tempPoints;
                tempPoints.push_back(make_pair(x,y));

                while(!tempPoints.empty()) {
                    pair<int,int> tempPoint;
                    tempPoint = tempPoints.front();
                    //for debuging
                    //cout << "Watching " << tempPoint.first << ":" << tempPoint.second << endl;
                    tempPoints.pop_front();

                    if (((table.at(tempPoint.first)).at(tempPoint.second)).second) continue;
                    ((table.at(tempPoint.first)).at(tempPoint.second)).second = true;

                    int x = tempPoint.first;
                    int y = tempPoint.second;
                    //out of range
                    if (x+1 < X_Lim) {
                        //the pixel is black
                        if (!((table.at(x+1)).at(y)).second)
                            //and the pixel is not checked
                            if (((table.at(x+1)).at(y)).first)
                                tempPoints.push_back(make_pair(x+1,y));
                    }
                    if (x-1 >= 0) {
                        if (!((table.at(x-1)).at(y)).second)
                            if (((table.at(x-1)).at(y)).first)
                                tempPoints.push_back(make_pair(x-1,y));
                    }
                    if (y+1 < Y_Lim) {
                        if (!((table.at(x)).at(y+1)).second)
                            if (((table.at(x)).at(y+1)).first)
                                tempPoints.push_back(make_pair(x,y+1));
                    }
                    if (y-1 >= 0) {
                        if (!((table.at(x)).at(y-1)).second)
                            if (((table.at(x)).at(y-1)).first)
                                tempPoints.push_back(make_pair(x,y-1));
                    }


                    //for debuging too
                    /*for (int k=0; k<X_Lim; k++) {
                        for (int r=0; r<Y_Lim; r++) {
                            cout << table[k][r].second;
                        }
                        cout << endl;
                    }
                    cout << endl;*/
                }
           }
        }
    }

    return countSiluets;
}


int main() {


    GBufferedImage* img = new GBufferedImage(80, 60);
    img->load("siluets.jpg");

    vector<vector<pair<bool, bool>>> * pixels = new vector<vector<pair<bool, bool>>>; // pair(color, check)

    getColorMass( *img, *pixels);

    cout << searchSiluets(*pixels) << endl;

    return 0;
}
