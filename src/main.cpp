#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "ncurses/ncurses.h"
#include "WindowManager.h"
int main() {
    setenv("TERMINFO", TERMINFO_PATH, 1);
    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
    int ch = 0;
    int input_cnt = 0;
    std::string buffer;
    int height, width;
    getmaxyx(stdscr, height, width);
    auto buffer_ptr = buffer.begin();
    WINDOW* my_win;

    while(ch != 'Q'){
        ch = getch();

    }
    endwin();
    return 0;
}
