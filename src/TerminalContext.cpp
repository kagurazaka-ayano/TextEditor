/**
 * @parent src
 * @file TerminalContext.cpp
 * @author ayano
 * @date 12/4/23
 * @brief
*/

#include "TerminalContext.h"

TerminalContext::TerminalContext(): width(getmaxx(stdscr)), height(getmaxy(stdscr)) {

}

void TerminalContext::updateDim() {
    width = getmaxx(stdscr);
    height = getmaxy(stdscr);
}

NCSIZE TerminalContext::getTerminalWidth() const {
    return width;
}

NCSIZE TerminalContext::getTerminalHeight() const {
    return height;
}
