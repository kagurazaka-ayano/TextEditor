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
#include <typeinfo>
#include "TerminalContext.h"
#include "SingletonAbstract.hpp"
#include "ncursesw/ncurses.h"
#include "datatype.h"
#include "Window.h"
#include "utility.hpp"

template<class T>
concept C = (std::is_convertible<T*, BaseWindow*>::value);

class WindowManager : public SingletonAbstract<WindowManager> {
    friend SingletonAbstract<WindowManager>;

public:
    WindowManager& operator=(WindowManager& other) = delete;
    WindowManager(WindowManager& other) = delete;

    ~WindowManager() override;

    template<C T>
    T* createWindow(NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const std::wstring& name, WindowBorder border, bool focus = true);

    BaseWindow* getWindow(const std::wstring& name);

    TerminalContext* getContext() const;

    void killWindow(BaseWindow* window);

    void killWindow(const std::wstring& name);

    template<C T>
    void translateWindow(T* window, NCSIZE delta_x, NCSIZE delta_y);

    template<C T>
    void moveWindow(T* window, NCSIZE dest_x, NCSIZE dest_y);

    template<C T>
    void translateWindow(const std::wstring& name, NCSIZE delta_x, NCSIZE delta_y);

    template<C T>
    void moveWindow(const std::wstring& name, NCSIZE dest_x, NCSIZE dest_y);

private:


    bool isTranslateValid(BaseWindow* window, NCSIZE newpos_x, NCSIZE newpos_y);

    TerminalContext* context = TerminalContext::Instance();
    WindowManager() = default;
    std::unordered_map<std::wstring, BaseWindow*> window_map = std::unordered_map<std::wstring, BaseWindow*>();


};

template<C T>
T* WindowManager::createWindow(NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const std::wstring& name, WindowBorder border, bool focus){
    WINDOW* window = newwin(height, width, starty, startx);
    box(window, 0, 0);
    wrefresh(window);
    auto* wrapper = new T(window, name, border, focus, startx, starty);
    window_map.try_emplace(name, wrapper);
    return wrapper;
}

template<C T>
void WindowManager::translateWindow(T *window, NCSIZE delta_x, NCSIZE delta_y) {
    if (!isTranslateValid(window, window->getX() + delta_x, window->getY() + delta_y)) return;
    moveWindow<T>(window, window->getX() + delta_x, window->getY() + delta_y);
}

template<C T>
void WindowManager::moveWindow(T *window, NCSIZE dest_x, NCSIZE dest_y) {
    if (!isTranslateValid(window, dest_x, dest_y)) return;
    auto* dummy_window = createWindow<T>(dest_x, dest_y, window->getWidth(), window->getHeight(),
                                        window->getName(), window->getBorder());
    killWindow(window);
    window = dummy_window;
}

template<C T>
void WindowManager::translateWindow(const std::wstring &name, NCSIZE delta_x, NCSIZE delta_y) {
    translateWindow<T>(window_map[name], delta_x, delta_y);
}

template <C T>
void WindowManager::moveWindow(const std::wstring &name, NCSIZE dest_x, NCSIZE dest_y) {
    moveWindow<T>(window_map[name], dest_x, dest_y);
}



#endif //TEXTEDITOR_WINDOWMANAGER_H
