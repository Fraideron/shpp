#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "gwindow.h" // for GWindow
using namespace std;


/*
* Drawing the tree
*
* @param points - start point for the tree
* @param l - length of the lines
* @param window - handler of the window
* @param a - angle for trigonometrics func
*
* @return void
*/
void drawTree(GPoint points, int l, GWindow & window, double a){
    if (l>1) {
        l *= 0.71;

        // point for end line
        int posX = (int)(points.getX()+l*cos(a));
        int posY = (int)(points.getY()-l*sin(a));

        //draw line
        window.drawLine(points.getX(), points.getY(), posX, posY);

        //begin recursion
        drawTree(GPoint(posX, posY), l, window, a+(M_PI/6));
        drawTree(GPoint(posX, posY), l, window, a-(M_PI/6));

    }

}

int main() {

    GWindow window(700, 500);
    window.setColor("White");
    window.clear();
    window.setWindowTitle("Sample Project");
    window.setColor("Black");

    window.setVisible(true);

    window.requestFocus();

    drawTree( GPoint(350, 480), 200, window, M_PI/2);

//    window.close();
//    exitGraphics();
    return 0;
}
