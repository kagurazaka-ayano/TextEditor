/**
 * @parent src
 * @file TerminalUtil.cpp
 * @author ayano
 * @date 12/1/23
 * @brief
*/

#include "WindowManager.h"

#include <utility>


WindowWrapper
WindowManager::createWindow(NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const std::string &name,
                            WindowType type) {
    WINDOW* window = newwin(height, width, starty, startx);
    wrefresh(window);
    WindowWrapper wrapper = WindowWrapper(window, name, )
}

WindowWrapper::WindowWrapper(WINDOW *data, std::string name, const windowBorder &border, WindowState state,
                             bool focus) : data(data), window_name(std::move(name)), windowBorder(border), state(state), focus(focus) {}

windowBorder::windowBorder(unsigned char ls, unsigned char rs, unsigned char ts, unsigned char bs, unsigned char tl,
                           unsigned char tr, unsigned char bl, unsigned char br) : ls(ls), rs(rs), ts(ts), bs(bs),
                                                                                   tl(tl), tr(tr), bl(bl), br(br) {

}
