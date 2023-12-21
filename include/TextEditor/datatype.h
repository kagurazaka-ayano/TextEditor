/**
 * @file definition.h
 * @author ayano
 * @date 12/3/23
 * @brief
*/

#ifndef TEXTEDITOR_DEFINITION_H
#define TEXTEDITOR_DEFINITION_H

#include <utility>
#include <cstring>
#include "ncursesw/ncurses.h"

// making life easier
typedef NCURSES_SIZE_T NCSIZE;
typedef unsigned long long ull;

/**
 * general purpose color structure
 */
struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	unsigned char data[8]{0x00, 0x00, 0x00, 0x00};

	Color();

	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	Color &operator=(const Color &other);

	Color(const Color &other) = default;
};

#endif //TEXTEDITOR_DEFINITION_H
