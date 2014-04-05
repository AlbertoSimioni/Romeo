/**
* \file color.cpp
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Color del package romeo::model::protocols
*/

#include "color.h"
#include <stdlib.h>

using namespace romeo::model::protocols;

int Color::red[3] = {238,0,0};
int Color::blue[3] = {0,0,128};
int Color::green[3] = {0,205,0};
int Color::yellow[3] = {255,255,0};
int Color::magenta[3] = {255,0,255};
int Color::lightblue[3] = {135,206,250};
int Color::gray[3] = {115,115,115};
int Color::orange[3] = {238,118,0};
int Color::aquagreen[3] = {0,255,255};
int Color::pink[3] = {255,130,171};
int Color::extracolor[3] = {255,255,255};

Color::Color() {}

int* Color::getColor(int index) {
    switch(index) {
    case 0:
        return red;
        break;
    case 1:
        return blue;
        break;
    case 2:
        return green;
        break;
    case 3:
        return yellow;
        break;
    case 4:
        return magenta;
        break;
    case 5:
        return lightblue;
        break;
    case 6:
        return gray;
        break;
    case 7:
        return orange;
        break;
    case 8:
        return aquagreen;
        break;
    case 9:
        return pink;
        break;
    default:
        int redValue = rand()%256;
        int greenValue = rand()%256;
        int blueValue = rand()%256;
        while(redValue==0 && greenValue==0 && blueValue==0) {
            redValue = rand()%256;
            greenValue = rand()%256;
            blueValue = rand()%256;
        }
        extracolor[0] = redValue;
        extracolor[1] = greenValue;
        extracolor[2] = blueValue;
        return extracolor;
    }
}

double Color::getSingleValueColor(int index) {
    switch(index) {
    case 0:
        return getSingleValue(red[0],red[1],red[2]);
        break;
    case 1:
        return getSingleValue(blue[0],blue[1],blue[2]);
        break;
    case 2:
        return getSingleValue(green[0],green[1],green[2]);
        break;
    case 3:
        return getSingleValue(yellow[0],yellow[1],yellow[2]);
        break;
    case 4:
        return getSingleValue(magenta[0],magenta[1],magenta[2]);
        break;
    case 5:
        return getSingleValue(lightblue[0],lightblue[1],lightblue[2]);
        break;
    case 6:
        return getSingleValue(gray[0],gray[1],gray[2]);
        break;
    case 7:
        return getSingleValue(orange[0],orange[1],orange[2]);
        break;
    case 8:
        return getSingleValue(aquagreen[0],aquagreen[1],aquagreen[2]);
        break;
    case 9:
        return getSingleValue(pink[0],pink[1],pink[2]);
        break;
    default:
        return getSingleValue(0,0,0);
    }
}

double Color::getSingleValue(int red,int green,int blue) {
    return (0.2125 * red + 0.7154 * green + 0.0721 * blue);
}
