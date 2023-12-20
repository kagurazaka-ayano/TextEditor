#include <string>
#include "ncursesw/ncurses.h"
#include "WindowManager.h"
#include "Window.h"
int main() {
    setenv("TERMINFO", TERMINFO_PATH, 1);
    setlocale(LC_ALL, "");
    keypad(stdscr, true);
    initscr();
    raw();
    noecho();
    auto manager = WindowManager::Instance();
    NCSIZE startx = 1, starty = 1, width = manager->getContext()->getTerminalWidth() / 4, height = manager->getContext()->getTerminalHeight() / 4;
    auto* window = manager->createWindow<TextEditWindow>(startx, starty,
                                        width, height,
                                        L"name", BaseWindow::starBorder);
    std::string buffer;
    refresh();
    char ch = 0;
    while(ch != 'Q'){
        ch = getch();
        switch(ch){
            case 'd':
                manager->translateWindow<TextEditWindow>(window, 1, 0);
                break;
            case 'a':
                manager->translateWindow<TextEditWindow>(window, -1, 0);
                break;
            case 'w':
                manager->translateWindow<TextEditWindow>(window, 0, -1);
                break;
            case 's':
                manager->translateWindow<TextEditWindow>(window, 0, 1);
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
