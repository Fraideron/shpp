#include <iostream>
#include <vector>
#include <utility>
#include <deque>
#include <fstream>
#include "simpio.h"
#include "filelib.h"
#include "gbufferedimage.h"

using namespace std;
/**
 * @brief The Pixel class - to store information
 *                          about each pixel and methods
 *                          of access to this information
 */
class Pixel{
private:
    int x, y;
    bool black, check;
public:
    Pixel(){}
    
    Pixel(int posX, int posY, bool black, bool check) {
        this->x = posX;
        this->y = posY;
        this->black = black;
        this->check = check;
    }
    
    int getX(){
        return this->x;
    }
    
    int getY(){
        return this->y;
    }
    
    bool isBlack(){
        return this->black;
    }
    
    bool isCheck(){
        return this->check;
    }
    
    void setCheck(bool ch){
        this->check = ch;
    }
};


class SilhouetteRecognizer{
private:
    GBufferedImage *img;
    vector<vector<Pixel>> pixels ;
    
public:
    SilhouetteRecognizer(): img(new GBufferedImage()) {
        
    }
    
    /**
     * @brief isBlack - return true if the pixel is black
     * @param color
     * @return
     */
    bool isBlack(int color) {
        return !(img->getRed(color) > 120 ||
                 img->getGreen(color) > 120 ||
                 img->getBlue(color) > 120 );
    }
    
    /**
     * @brief generagePixelsTable - fill a "table" objects of Pixel,
     *                              1) set to check false;
     *                              2) color set to white pixels - 0,
     *                                              black poxels - 1.
     */
    void loadFileAndGeneragePixelsTable(string file) {
        img->load(file);
        for (int y = 0; y < img->getHeight(); ++y) {
            vector<Pixel> pixelsLine;
            for (int x = 0; x < img->getWidth(); ++x) {
                pixelsLine.push_back(Pixel(x, y, isBlack(img->getRGB(x,y)), false));
            }
            pixels.push_back(pixelsLine);
        }
    }
    
    
    /**
     * @brief searchSilhouettes - function find unverified black pixel and
     *                            using the algorithm "Breadth-first search" stopping completely
     *                            black spots
     * @return
     */
    int searchSilhouettes(){
        if (pixels.size() == 0) return 0;
        int numberOfSilhouettes = 0;
        int xLim = pixels.size();
        
        for (int x = 0; x < xLim; ++x) {
            int yLim = pixels[x].size();
            
            for (int y = 0; y < yLim; ++y) {
                if(!((pixels[x])[y]).isCheck() && ((pixels[x])[y]).isBlack()){
                    numberOfSilhouettes++;
                    deque<pair<int,int>> pointsForCheck;
                    pointsForCheck.push_back(make_pair(x,y));
                    
                    while(!pointsForCheck.empty()) {
                        pair<int,int> tempPoint;
                        tempPoint = pointsForCheck.front();
                        pointsForCheck.pop_front();
                        
                        int x = tempPoint.first;
                        int y = tempPoint.second;
                        
                        if (((pixels[x])[y]).isCheck()) continue;
                        ((pixels[x])[y]).setCheck(true);
                        
                        checkPixel(x+1, y,  pointsForCheck);
                        checkPixel(x-1, y,  pointsForCheck);
                        checkPixel(x, y+1,  pointsForCheck);
                        checkPixel(x, y-1,  pointsForCheck);
                    }
                }
            }
        }
        return numberOfSilhouettes;
    }
    
    /**
     * @brief checkPixel  - if not out of range,
     *                      the pixel is black
     *                      and the pixel is not checked
     * @param x   / pixel's position
     * @param y  /
     * @param tempPoints - deque for storage untested pixels
     */
    void checkPixel(int x, int y,  deque<pair<int,int>> & tempPoints){
        if ((x < pixels.size()) &&
                (!((pixels[x])[y]).isCheck()) &&
                ((pixels[x])[y]).isBlack())
            tempPoints.push_back(make_pair(x,y));
        
    }
    
    ~SilhouetteRecognizer() {
        delete img;
    }
    
    
};
/**
 * @brief isImageFile - function checks the file and its extension
 * @param fileName -
 * @return
 */
bool isImageFile(string fileName){
    if(fileExists(fileName)){
        string subStringForCheck = fileName.substr(fileName.size()-3);
        
        return (subStringForCheck == "bmp" ||
                subStringForCheck == "jpg" ||
                subStringForCheck == "png" ||
                subStringForCheck == "peg");
    }
    return false;
}

int main() {
    
    string file;
    do{
        file = getLine("Input the file name:");
    }while (!isImageFile(file));
    
    cout <<  "Searching ..." << endl;
    
    SilhouetteRecognizer worker;
    worker.loadFileAndGeneragePixelsTable(file);
    
    cout<< "Found "
        << worker.searchSilhouettes()
        << " silhouettes in file "
        << file
        << "!"
        << endl;
    
    return 0;
}

