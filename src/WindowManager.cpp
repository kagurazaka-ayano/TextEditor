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

TerminalContext *WindowManager::getContext() const noexcept {
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

bool WindowManager::isTranslateValid(BaseWindow *window, NCSIZE newposX, NCSIZE newposY) const noexcept {
    return (0 <= newposX && newposX + window->getWidth() <= context->getTerminalWidth()) && (0 <= newposY && newposY + window->getHeight() <= context->getTerminalHeight());
}

void WindowManager::remakeWindow(BaseWindow *window, NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height,
                                 const WindowBorder &border) {
    window->setBorder(BaseWindow::nullBorder)->setX(startx)->setY(starty)->setBorder(border)->refreshWindow();
}

void WindowManager::translateWindow(BaseWindow *window, NCSIZE deltaX, NCSIZE deltaY) {
    moveWindow(window, window->getX() + deltaX, window->getY() + deltaY);
}


void WindowManager::moveWindow(BaseWindow *window, NCSIZE destX, NCSIZE destY) {
    if (!isTranslateValid(window, destX, destY)) return;
    remakeWindow(window, destX, destY, window->getWidth(), window->getHeight(), window->getBorder());

}


void WindowManager::translateWindow(const std::wstring &name, NCSIZE deltaX, NCSIZE deltaY) {
    translateWindow(window_map[name], deltaX, deltaY);
}


void WindowManager::moveWindow(const std::wstring &name, NCSIZE destX, NCSIZE destY) {
    moveWindow(window_map[name], destX, destY);
}

