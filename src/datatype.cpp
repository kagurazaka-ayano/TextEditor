/**
 * @file datatype.cpp
 * @author ayano
 * @date 12/3/23
 * @brief
*/

#include "datatype.h"


Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : r(r), g(g), b(b), a(a) {
    data = COLOR_PAIR((r << 6) | (g << 4) | (b << 2) | (a));
}


Color& Color::operator=(const Color &other) {
    if (this != &other) {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        data = other.data;
    }
    return *this;
}

Color::Color() : Color(0, 0, 0, 0xff){}

Color::Color(uint32_t data) {
    this->data = data;
    r = data & (0xff000000);
    g = data & (0x00ff0000);
    b = data & (0x0000ff00);
    a = data & (0x000000ff);
}


AttrIndicator::AttrIndicator(NCSIZE begin, NCSIZE end, unsigned int att, ull priority)
        : begin(begin), end(end), attr(att), priority(priority) {

}
