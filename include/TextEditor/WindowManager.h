/**
 * @file WindowManager.h
 * @author ayano
 * @date 12/1/23
 * @brief Manager of all window
 * @remark ALWAYS use this to create a window, DO NOT USE NEW!
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
#include "BaseWindow.h"

// defined to include all ptr inherent BaseWindow
template<class T>
concept WINDOWS = (std::is_convertible<T*, BaseWindow*>::value);


class WindowManager : public SingletonAbstract<WindowManager> {
    friend SingletonAbstract<WindowManager>;

public:
    WindowManager& operator=(WindowManager& other) = delete;
    WindowManager(WindowManager& other) = delete;
    WindowManager(WindowManager&& other) = delete;

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
    template<WINDOWS T>
    T* createWindow(NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const std::wstring& name, const WindowBorder& border, bool focus = true);

    /**
     * get a window from window pool with its name
     * @tparam T type of the window is fetching
     * @param name window name give in the assignment
     * @return window pointer corresponding to the name, nullptr if the window doesn't exist
     */
    template<WINDOWS T>
    T* getWindow(const std::wstring& name) const;

    /**
     * get current terminal context
     * @return current terminal context
     */
    TerminalContext* getContext() const noexcept;

    /**
     * free the window
     * @param window window pointer
     * @remark you still have to assign the window to nullptr to avoid dangling ptr
     */
    void killWindow(BaseWindow* window);

    /**
     * free the window with given name
     * @param name name of the window
     * @remark you still have to assign the window to nullptr to avoid dangling ptr
     */
    void killWindow(const std::wstring& name);

    /**
     * @brief move the window from its original pos to a new pos
     * @param window window ptr
     * @param deltaX change in x (left is positive and right is negative)
     * @param deltaY change in y (down is positive and up is negative)
     * @remark this method will do nothing if the translation is invalid(window out of range of current terminal)
     */
    void translateWindow(BaseWindow *window, NCSIZE deltaX, NCSIZE deltaY);

    /**
     * @brief move the window to another position
     * @param window window ptr
     * @param destX target x-coord
     * @param destY target y-coord
     * @remark this method will do nothing if the translation is invalid(window out of range of current terminal)
     */
    void moveWindow(BaseWindow *window, NCSIZE destX, NCSIZE destY);

    /**
     * @brief move the window with given name from its original pos to a new pos
     * @param name window name
     * @param deltaX change in x (left is positive and right is negative)
     * @param deltaY change in y (down is positive and up is negative)
     * @remark this method will do nothing if the translation is invalid(window out of range of current terminal)
     */
    void translateWindow(const std::wstring& name, NCSIZE deltaX, NCSIZE deltaY);

    /**
     * @brief move the window with given name to another position
     * @param name window name
     * @param destX target x-coord
     * @param destY target y-coord
     * @remark this method will do nothing if the translation is invalid(window out of range of current terminal)
     */
    void moveWindow(const std::wstring& name, NCSIZE destX, NCSIZE destY);

private:

    /**
     * @brief check a translation is valid or not
     * @param window window ptr
     * @param newposX new x pos
     * @param newposY new y pos
     * @return true of translation is valid
     */
    bool isTranslateValid(BaseWindow* window, NCSIZE newposX, NCSIZE newposY) const noexcept;

    /**
     * @brief set the parameter of the window to the given parameter
     * @param window window object
     * @param startx upper left x-coord
     * @param starty upper left y-coord
     * @param width window width
     * @param height window height
     * @param border border of this window
     */
    void remakeWindow(BaseWindow* window, NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const WindowBorder& border);


    TerminalContext* context = TerminalContext::Instance();
    WindowManager() = default;

    // map storing all windows
    std::unordered_map<std::wstring, BaseWindow*> window_map = std::unordered_map<std::wstring, BaseWindow*>();


};

template<WINDOWS T>
T* WindowManager::createWindow(NCSIZE startx, NCSIZE starty, NCSIZE width, NCSIZE height, const std::wstring& name, const WindowBorder &border, bool focus){
    WINDOW* window = newwin(height, width, starty, startx);
    box(window, 0, 0);
    wrefresh(window);
    auto* wrapper = new T(window, name, border, focus, startx, starty);
    window_map.try_emplace(name, wrapper);
    return wrapper;
}

template<WINDOWS T>
T* WindowManager::getWindow(const std::wstring &name) const {
    if (window_map.find(name) != window_map.end()){
        return window_map.at(name);
    }
    return nullptr;
}




#endif //TEXTEDITOR_WINDOWMANAGER_H
