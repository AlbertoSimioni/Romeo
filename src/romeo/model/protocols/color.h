/**
* \file color.h
* \author Matteo Pozza
* \date 2014-02-17
**
* \brief Header della classe Color del package romeo::model::protocols
*/

#ifndef COLOR_H
#define COLOR_H

namespace romeo {
namespace model {
namespace protocols{

class Color
{
public:
    Color();
    static int* getColor(int);
private:
    static int red[3];
    static int blue[3];
    static int green[3];
    static int yellow[3];
    static int magenta[3];
    static int lightblue[3];
    static int gray[3];
    static int orange[3];
    static int aquagreen[3];
    static int pink[3];
    static int extracolor[3];
};


}
}
}

#endif // COLOR_H

