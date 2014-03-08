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
