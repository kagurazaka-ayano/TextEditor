/**
 * @file TerminalUtil.cpp
 * @author ayano
 * @date 12/1/23
 * @brief
*/

#include "WindowManager.h"


void WindowManager::killWindow(BaseWindow *window) {
    std::wstring element_name;
    for (const auto& i: window_map) {
        if(i.second == window) {
            element_name = i.first;
            break;
        }
    }
    delete window;
    window_map.erase(element_name);
}

void WindowManager::killWindow(const std::wstring &name) {
    auto* element = window_map[name];
    killWindow(element);
}

TerminalContext *WindowManager::getContext() const {
    return context;
}

WindowManager::~WindowManager() {
    std::vector<BaseWindow*> obj_free = std::vector<BaseWindow*>(window_map.size());
    for (const auto& i: window_map) {
        obj_free.push_back(i.second);
    }
    window_map.clear();
    for(auto i : obj_free){
        delete i;
    }
}

bool WindowManager::isTranslateValid(BaseWindow *window, NCSIZE newpos_x, NCSIZE newpos_y) {
    return (0 <= newpos_x && newpos_x + window->getWidth() <= context->getTerminalWidth()) && (0 <= newpos_y && newpos_y + window->getHeight() <= context->getTerminalHeight());
}

void WindowManager::remakeWindow(BaseWindow *window, NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height,
                                 WindowBorder border) {
    window->setBorder(BaseWindow::nullBorder)->setX(startx)->setY(starty)->setBorder(border)->refreshWindow();
}

