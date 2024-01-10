/**
 * @file BaseWindow.h
 * @author ayano
 * @date 12/4/23
 * @brief some window wrapper classes
*/

// TODO: implement more windows

#ifndef TEXTEDITOR_BASEWINDOW_H
#define TEXTEDITOR_BASEWINDOW_H

#include "ncursesw/ncurses.h"
#include "datatype.h"
#include "fmt/core.h"
#include "fmt/xchar.h"
#include <string>
#include <vector>
#include <sstream>
#include <initializer_list>
#include <unordered_map>

struct WindowBorder{
    WindowBorder(wchar_t ls, wchar_t rs, wchar_t ts, wchar_t bs, wchar_t tl,
                 wchar_t tr, wchar_t bl, wchar_t br);
    wchar_t ls, rs, ts, bs, tl, tr, bl, br;

};



/**
 * @brief basic window class, all other window should inherit this class
 */
class BaseWindow{
public:

    BaseWindow(WINDOW *data, std::wstring name, const WindowBorder& border, bool focus, NCSIZE startx, NCSIZE starty);

    virtual ~BaseWindow();

    /**
     * @brief get x coord
     * @return x coord
     */
    NCSIZE getX() const noexcept;

    /**
     * @brief get y coord
     * @return y coord
     */
    NCSIZE getY() const noexcept;

    /**
     * @brief get window width
     * @return window width
     */
    NCSIZE getWidth() const noexcept;

    /**
     * @brief get window height
     * @return window height
     */
    NCSIZE getHeight() const noexcept;

    /**
     * @brief get window name
     * @return window name
     */
    std::wstring getName() const noexcept;

    /**
     * @brief get the raw window ptr
     * @return raw window ptr
     */
    WINDOW* getWindowPtr() const noexcept;

    /**
     * @brief get the border the window is using
     * @return border the window is using
     */
    WindowBorder getBorder() const noexcept;

    /**
     * @brief make this window invalid by make the raw window object nullptr
     */
    void invalidateWindow() noexcept;

    /**
     * @brief refresh window
     */
    void refreshWindow();

    /**
     * @brief check this window is valid or not
     * @return true if this window is valid, false otherwise
     */
    [[nodiscard]] bool isValidWindow() const noexcept;

    /**
     * @brief set x coord
     * @param x new x coord
     * @return window ptr for method chaining
     */
    virtual BaseWindow* setX(NCSIZE x);
    /**
     * @brief set y coord
     * @param y new y coord
     * @return window ptr for method chaining
     */
    virtual BaseWindow* setY(NCSIZE y);

    /**
     * @brief set window width
     * @param width new width
     * @return window ptr for method chaining
     */
    virtual BaseWindow* setWidth(NCSIZE width);

    /**
     * @brief set window height
     * @param height new height
     * @return window ptr for method chaining
     */
    virtual BaseWindow* setHeight(NCSIZE height);

    /**
     * @brief set window name
     * @param name new name
     * @return window ptr for method chaining
     */
    virtual BaseWindow* setName(const std::wstring& name);

    /**
     * @brief set raw window ptr
     * @param name new raw window ptr
     * @return window ptr for method chaining
     */
    virtual BaseWindow* setPtr(WINDOW* updatedPtr);

    /**
     * @brief set window border
     * @param name new border
     * @return window ptr for method chaining
     */
    virtual BaseWindow* setBorder(const WindowBorder& border);

    void attrBegin(const std::initializer_list<attributes> &attr, NCSIZE pos) noexcept;

    void attrEnd(const std::initializer_list<attributes> &attr, NCSIZE pos) noexcept;

    NCSIZE getCursorX() const noexcept;

    NCSIZE getCursorY() const noexcept;

    static WindowBorder simpleBorder;

    static WindowBorder nullBorder;

    static WindowBorder starBorder;

    static WindowBorder disabledBorder;

    static WindowBorder roundBorder;

protected:

    // which line in the buffer should being displayed
    ull display_begin_line;
    ull display_end_line;
    // vertical displacement relative to initial position, used for displaying wrapped line
    ull vert_displacement;
    std::wstring display_buffer;
    std::vector<std::wstring> line_buffer;
    std::wstring name;
    WINDOW* data;
    // window width, height, x pos, y pos
    NCSIZE width, height, pos_x, pos_y;
    NCSIZE cursor_pos_x, cursor_pos_y;
    WindowBorder window_border;
    std::vector<std::vector<AttrIndicator>> attr_list;
    ull attr_depth = 0;

    /**
     * @brief clear the border
     */
    void clearBorder();

    /**
     * @brief construct the buffer of this window, typically including add the displaying line to the buffer and add line wrap
     */
    virtual void constructBuffer() = 0;

    /**
     * @brief clear the buffer
     */
    virtual void clearBuffer() = 0;

    /**
     * @brief display buffer to the window, typically putting the display buffer onto the screen
     */
    virtual void displayBuffer() = 0;

    /**
     * @brief update the buffer content each time buffer is modified, typically add line break and update highlighting
     */
    virtual void updateBuffer() = 0;

    /**
     * @brief apply attribute to the buffer
     */
    virtual void updateAttribute() = 0;

    /**
     * @brief make current window get focus
     */
    virtual void enterFocus();

    /**
     * @brief make current window lose focus
     */
    virtual void exitFocus();

    /**
     * @brief dump line into buffer
     */
    virtual void dumpBuffer() = 0;

    // whether this window has focus or not
    bool focus;
};





#endif //TEXTEDITOR_BASEWINDOW_H
