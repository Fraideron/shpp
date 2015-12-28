#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <fstream>
#include "simpio.h"
#include "filelib.h"
#include "gbufferedimage.h"
using namespace std;


class ShilhouetteRecognizer {
private:
    GBufferedImage *img;
    vector<vector<pair<bool, bool>>> pixels;

public:
    ShilhouetteRecognizer(string file): img(new GBufferedImage()) {
        img->load(file);
    }

    bool getColorRatio(int color) {
        if(img->getRed(color) > 120 || img->getGreen(color) > 120 || img->getBlue(color) > 120 )
            return false;
        return true;
    }

    void generageBinPixels() {
        for (int y = 0; y < img->getHeight(); ++y) {
            vector<pair<bool,bool>> pixelsForWidth;
            for (int x = 0; x < img->getWidth(); ++x) {
                pixelsForWidth.push_back(make_pair(
                    getColorRatio(img->getRGB(x,y)),
                    false
                ));
            }
            pixels.push_back(pixelsForWidth);
        }
    }

    int searchSilhouettes(){

        if (pixels.size() == 0) return 0;

        int nunberOfSilhouettes = 0;
        int X_Lim = pixels.size();

        for (int x = 0; x < X_Lim; ++x) {
            int Y_Lim = pixels[x].size();

            for (int y = 0; y < Y_Lim; ++y) {
                if(!((pixels[x])[y]).second && ((pixels[x])[y]).first){
                    nunberOfSilhouettes++;
                    deque<pair<int,int>> tempPoints;
                    tempPoints.push_back(make_pair(x,y));

                    while(!tempPoints.empty()) {
                        pair<int,int> tempPoint;
                        tempPoint = tempPoints.front();
                        tempPoints.pop_front();

                        int x = tempPoint.first;
                        int y = tempPoint.second;

                        if (((pixels[x])[y]).second) continue;
                        ((pixels[x])[y]).second = true;


                        checkPixel(x+1, y,  tempPoints);
                        checkPixel(x-1, y,  tempPoints);
                        checkPixel(x, y+1,  tempPoints);
                        checkPixel(x, y-1,  tempPoints);
                    }
                }
            }
        }

        return nunberOfSilhouettes;
    }

    void checkPixel(int x, int y,  deque<pair<int,int>> & tempPoints){
        if (x < pixels.size()) {
            if (!((pixels.at(x)).at(y)).second)
                if (((pixels.at(x)).at(y)).first)
                    tempPoints.push_back(make_pair(x,y));
        }

    }

    ~ShilhouetteRecognizer() {
        delete img;
    }


};


int main() {

    string file = getLine("Input the file name:");
    while (!fileExists(file)) {
        cout <<"Sorrry, but there is no file with the specified name!" << endl << endl;
        file = getLine("Input the file name:");
    }

    cout <<  "Opening..." << endl;


    ShilhouetteRecognizer *worker = new ShilhouetteRecognizer(file);
    worker->generageBinPixels();
    cout<< "Hello! I am ShilhouetteRecognizer! And i found "
        << worker->searchSilhouettes()
        << " silhouettes in file "
        << file
        << endl;

    delete worker;
    return 0;
}

