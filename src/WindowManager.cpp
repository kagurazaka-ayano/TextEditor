/**
 * @parent src
 * @file TerminalUtil.cpp
 * @author ayano
 * @date 12/1/23
 * @brief
*/

#include "WindowManager.h"

void WindowManager::killWindow(BaseWindow* window) {
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



BaseWindow* WindowManager::getWindow(const std::wstring &name){
    if (window_map.find(name) != window_map.end()){
        return window_map.at(name);
    }
    return nullptr;
}

void WindowManager::killWindow(const std::wstring &name) {
    auto* element = window_map[name];
    delete element;
    window_map.erase(name);
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
    return (newpos_x + window->getWidth() < context->getTerminalWidth()) && (newpos_y + window->getHeight() < context->getTerminalHeight());
}
