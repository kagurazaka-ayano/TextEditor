/**
 * @file TerminalContext.h
 * @author ayano
 * @date 12/4/23
 * @brief context of current terminal, include all the parameters of current terminal
*/

// TODO: will refresh each time when the terminal is resized(unimplemented)

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
    TerminalContext(TerminalContext&& other) = delete;

    /**
     * @brief get terminal width
     * @return width of this terminal
     */
    NCSIZE getTerminalWidth() const noexcept;

    /**
     * @brief get terminal height
     * @return height of this terminal
     */
    NCSIZE getTerminalHeight() const noexcept;

private:
    NCSIZE width;
    NCSIZE height;
    TerminalContext() noexcept;

    /**
     * @brief update dimension variable
     */
    void updateDim() noexcept;
};


#endif //TEXTEDITOR_TERMINALCONTEXT_H
