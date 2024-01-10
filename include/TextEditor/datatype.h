/**
 * @file datatype.h
 * @author ayano
 * @date 12/3/23
 * @brief defined datatype to make life easier
*/

#ifndef TEXTEDITOR_DEFINITION_H
#define TEXTEDITOR_DEFINITION_H

#include <utility>
#include <cstring>

#include "ncursesw/ncurses.h"

// making life easier
typedef NCURSES_SIZE_T NCSIZE;
typedef unsigned long long ull;

enum class attributes {
    NORMAL = A_NORMAL,
    STANDOUT = A_STANDOUT,
    UNDERLINE = A_UNDERLINE,
    REVERSE = A_REVERSE,
    BLINK = A_BLINK,
    DIM = A_DIM,
    BOLD = A_BOLD,
    PROTECT = A_PROTECT,
    INVIS = A_INVIS,
    ALTCHARSET = A_ALTCHARSET,
    CHARTEXT = A_CHARTEXT
};

/**
 * general purpose color structure
 */
struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	unsigned char data = 0x00000000;

	Color();

	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    Color(uint32_t data);

	Color &operator=(const Color &other);

	Color(const Color &other) = default;

};

inline void makeColorPair(short idx, const Color& c1, const Color& c2){
    init_pair(idx, c1.data, c2.data);
}


/**
 * @brief indicator of a attribute
 */
struct AttrIndicator {
    /**
     * @brief constructor
     * @param begin where the attribute begin in this line, start from 0
     * @param end where the attribute end in this line, start from 0
     * @param att what the attribute is
     * @param priority priority of this attribute, max is 0
     */
    AttrIndicator(NCSIZE begin, NCSIZE end, unsigned int att, ull priority);

    NCSIZE begin;
    NCSIZE end;
    unsigned int attr;
    ull priority = 0;
};


#endif //TEXTEDITOR_DEFINITION_H
