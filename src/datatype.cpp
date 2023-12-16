/**
 * @file datatype.cpp
 * @author ayano
 * @date 12/3/23
 * @brief
*/

#include "datatype.h"


Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {
    memset(data, COLOR_PAIR((r << 6) | (g << 4) | (b << 2) | (a)), 4);
}


Color& Color::operator=(const Color &other) {
    if (this != &other){
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        memcpy(data, other.data, 4);
        return *this;
    }
}

Color::Color() : Color(0, 0, 0, 255){}





