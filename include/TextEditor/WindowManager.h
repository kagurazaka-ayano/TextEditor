/**
 * @file TerminalUtil.h
 * @author ayano
 * @date 12/1/23
 * @brief
*/

#ifndef TEXTEDITOR_WINDOWMANAGER_H
#define TEXTEDITOR_WINDOWMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "TerminalContext.h"
#include "SingletonAbstract.hpp"
#include "ncursesw/ncurses.h"
#include "datatype.h"
#include "Window.h"


template<class T>
concept C = (std::is_convertible<T*, BaseWindow*>::value);


class WindowManager : public SingletonAbstract<WindowManager> {
    friend SingletonAbstract<WindowManager>;

public:
    WindowManager& operator=(WindowManager& other) = delete;
    WindowManager(WindowManager& other) = delete;

    ~WindowManager() override;

    /**
     * create a window
     * @tparam T type of window to be created
     * @param startx x coord of upper left pos
     * @param starty y coord of upper left pos
     * @param width window width
     * @param height window height
     * @param name window name
     * @param border window border
     * @param focus whether this window should get focus or not, default true
     * @return pointer to this window
     */
    template<C T>
    T* createWindow(NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const std::wstring& name, WindowBorder border, bool focus = true);

    /**
     * get a window from window pool with its name
     * @param name window name give in the assignment
     * @return window pointer corresponding to the name
     */
    template<C T>
    T* getWindow(const std::wstring& name);

    /**
     * get current terminal context
     * @return current terminal context
     */
    TerminalContext* getContext() const;

    /**
     * free a window
     * @param window window pointer
     * @remark you still have to assign the window to nullptr to avoid dangling ptr
     */
    void killWindow(BaseWindow* window);

    /**
     * free the window with given name
     * @param name name of the window
     */
    void killWindow(const std::wstring& name);

    void remakeWindow(BaseWindow* window, NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, WindowBorder border);

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
    moveWindow<T>(window, window->getX() + delta_x, window->getY() + delta_y);
}

template<C T>
void WindowManager::moveWindow(T *window, NCSIZE dest_x, NCSIZE dest_y) {
    if (!isTranslateValid(window, dest_x, dest_y)) return;
    remakeWindow(window, dest_x, dest_y, window->getWidth(), window->getHeight(), window->getBorder());

}

template<C T>
void WindowManager::translateWindow(const std::wstring &name, NCSIZE delta_x, NCSIZE delta_y) {
    translateWindow<T>(window_map[name], delta_x, delta_y);
}

template <C T>
void WindowManager::moveWindow(const std::wstring &name, NCSIZE dest_x, NCSIZE dest_y) {
    moveWindow<T>(window_map[name], dest_x, dest_y);
}

template<C T>
T* WindowManager::getWindow(const std::wstring &name){
    if (window_map.find(name) != window_map.end()){
        return window_map.at(name);
    }
    return nullptr;
}




#endif //TEXTEDITOR_WINDOWMANAGER_H
