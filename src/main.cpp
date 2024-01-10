#include <string>
#include <sstream>
#include <future>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ranges>
#include "fmt/core.h"
#include "ncursesw/ncurses.h"
#include "WindowManager.h"
#include "BaseWindow.h"
#include "InputHandler.h"
#include "TextEditWindow.h"
int main() {


    setenv("TERMINFO", TERMINFO_PATH, 1);
    setlocale(LC_ALL, "en_US.UTF-8");
    keypad(stdscr, true);
    initscr();
    raw();
    noecho();
    auto promise = std::promise<wint_t>();
    auto future = promise.get_future();
    auto manager = WindowManager::Instance();
    auto input = InputHandler::Instance();


    NCSIZE startx = 1, starty = 1, width = manager->getContext()->getTerminalWidth() / 4, height = manager->getContext()->getTerminalHeight() / 4;
    auto* window = manager->createWindow<TextEditWindow>(startx, starty,
                                        width, height,
                                        L"name", BaseWindow::roundBorder);


    std::string buffer;
    refresh();
    wint_t ch = 'l';
    do {

        switch(ch){
            case 'l':
                manager->translateWindow(window, 1, 0);
                break;
            case 'h':
                manager->translateWindow(window, -1, 0);
                break;
            case 'k':
                manager->translateWindow(window, 0, -1);
                break;
            case 'j':
                manager->translateWindow(window, 0, 1);
                break;
//            case '9':
//                window->attrBegin({attributes::UNDERLINE}, window->getCursorX());
//                break;
//            case '0':
//                window->attrEnd({attributes::UNDERLINE}, window->getCursorX());
//                break;
            default:
                window->addCh(ch);
                break;
        }
        ch = getch();
    }while(ch != 'Q');
    manager->killWindow(window);
    endwin();
    return 0;
}
