/**
 * @file TerminalContext.cpp
 * @author ayano
 * @date 12/4/23
 * @brief context of current terminal
*/

#include "TerminalContext.h"

TerminalContext::TerminalContext() noexcept: width(getmaxx(stdscr)), height(getmaxy(stdscr)) {

}

void TerminalContext::updateDim() noexcept {
    width = getmaxx(stdscr);
    height = getmaxy(stdscr);
}

NCSIZE TerminalContext::getTerminalWidth() const noexcept {
    return width;
}

NCSIZE TerminalContext::getTerminalHeight() const noexcept {
    return height;
}
