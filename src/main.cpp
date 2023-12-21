#include <string>
#include "ncursesw/ncurses.h"
#include "WindowManager.h"
#include "Window.h"
#include "InputHandler.h"
int main() {
    setenv("TERMINFO", TERMINFO_PATH, 1);
    setlocale(LC_ALL, "en_US.UTF-8");
    keypad(stdscr, true);
    initscr();
    raw();
    noecho();
    auto promise = std::promise<char>();
    auto manager = WindowManager::Instance();
    NCSIZE startx = 1, starty = 1, width = manager->getContext()->getTerminalWidth() / 4, height = manager->getContext()->getTerminalHeight() / 4;
    auto* window = manager->createWindow<TextEditWindow>(startx, starty,
                                        width, height,
                                        L"name", BaseWindow::roundBorder);
    std::string buffer;
    refresh();
    char ch = 0;
    while(ch != 'Q'){
        ch = getch();
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
            default:
                window->addCh(ch);
                break;
        }
    }
    manager->killWindow(window);
    endwin();
    return 0;
}
