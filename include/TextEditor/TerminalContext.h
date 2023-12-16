/**
 * @file TerminalContext.h
 * @author ayano
 * @date 12/4/23
 * @brief
*/

#ifndef TEXTEDITOR_TERMINALCONTEXT_H
#define TEXTEDITOR_TERMINALCONTEXT_H

#include "SingletonAbstract.hpp"
#include "ncursesw/ncurses.h"
#include "datatype.h"

class TerminalContext : public SingletonAbstract<TerminalContext> {
    friend SingletonAbstract<TerminalContext>;
public:

    TerminalContext& operator=(TerminalContext& other) = delete;
    TerminalContext(TerminalContext& other) = delete;

    NCSIZE getTerminalWidth() const;
    NCSIZE getTerminalHeight() const;

private:
    NCSIZE width;
    NCSIZE height;
    TerminalContext();

    void updateDim();
};


#endif //TEXTEDITOR_TERMINALCONTEXT_H
