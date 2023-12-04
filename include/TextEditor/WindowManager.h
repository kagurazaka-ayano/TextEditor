/**
 * @parent include/TextEditor
 * @file TerminalUtil.h
 * @author ayano
 * @date 12/1/23
 * @brief
*/

#ifndef TEXTEDITOR_WINDOWMANAGER_H
#define TEXTEDITOR_WINDOWMANAGER_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "SingletonAbstract.hpp"
#include "ncurses/ncurses.h"
#include "datatype.h"

enum class WindowState{
    INSERT,
    COMMAND,
    VIEW
};

enum class WindowType{

};

typedef NCURSES_SIZE_T NCSIZE;

typedef struct windowBorder{
    windowBorder(unsigned char ls, unsigned char rs, unsigned char ts, unsigned char bs, unsigned char tl,
                 unsigned char tr, unsigned char bl, unsigned char br);

    unsigned char ls, rs, ts, bs, tl, tr, bl, br;
}windowBorder;

class WindowWrapper{
public:
    WindowWrapper(WINDOW *data, std::string name, const windowBorder &border, WindowState state, bool focus);

private:
    WINDOW* data;
    std::string window_name;
    windowBorder windowBorder;
    WindowState state;
    bool focus;
};

class WindowManager : public SingletonAbstract<WindowManager> {
    friend SingletonAbstract<WindowManager>;

public:
    WindowManager() = delete;
    WindowManager& operator=(WindowManager& other) = delete;
    WindowManager(WindowManager& other) = delete;

    ~WindowManager() override = default;

    WindowWrapper createWindow(NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const std::string& name, WindowType type);

    void destroyWindow(WINDOW* window);

private:
    std::unordered_map<std::string, WindowWrapper> windowList = std::unordered_map<std::string, WindowWrapper>();

};


#endif //TEXTEDITOR_WINDOWMANAGER_H
