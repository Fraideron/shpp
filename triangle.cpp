#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;

//This function get two points
//Search the middle between the two points
GPoint searchMiddle(GPoint first, GPoint second){
    GPoint res(int((first.getX() + second.getX()) / 2), int ((first.getY() + second.getY()) / 2) );
    return res;
}

//Get point and draw her
void drawPoint( GPoint point, GWindow & window){
    window.drawRect(point.getX(), point.getY(), 0.1, 0.1);
}

//main function for draw triangle
void makeFract(Vector<GPoint> & vertex, GPoint oldPoints, GWindow & wind){
    GPoint temp = searchMiddle(oldPoints, vertex.get(randomInteger(0, 2)));
    drawPoint(temp, wind);
    makeFract(vertex, temp, wind);
}

int main() {

    GWindow window(700, 500);
    window.setColor("White");
    window.clear();
    window.setWindowTitle("Sample Project");
    window.setColor("Black");

    window.setVisible(true);

    window.requestFocus();

    // start points for rectangle
    Vector<GPoint> vertex;
    vertex.add(GPoint(350, 10));
    vertex.add(GPoint(10, 490));
    vertex.add(GPoint(690, 490));

    //fuction for draw points 
    makeFract(vertex, vertex.get(2), window);

    window.close();
    exitGraphics();
    return 0;
}
