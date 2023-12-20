/**
 * @file Window.h
 * @author ayano
 * @date 12/4/23
 * @brief
*/

#ifndef TEXTEDITOR_WINDOW_H
#define TEXTEDITOR_WINDOW_H

#include "ncursesw/ncurses.h"
#include "datatype.h"
#include "fmt/core.h"
#include "fmt/xchar.h"
#include <string>
#include <vector>
#include <sstream>

typedef struct WindowBorder{
    WindowBorder(wchar_t ls, wchar_t rs, wchar_t ts, wchar_t bs, wchar_t tl,
                 wchar_t tr, wchar_t bl, wchar_t br);
    wchar_t ls, rs, ts, bs, tl, tr, bl, br;

}windowBorder;

/**
 * basic window class, the base class of all other window.
 */
class BaseWindow{
public:

    BaseWindow(WINDOW *data, std::wstring name, const WindowBorder& border, bool focus, NCSIZE startx, NCSIZE starty);

    virtual ~BaseWindow();

    NCSIZE getX() const;

    NCSIZE getY() const;

    NCSIZE getWidth() const;

    NCSIZE getHeight() const;

    std::wstring getName() const;

    WINDOW* getWindowPtr() const;

    WindowBorder getBorder() const;

    void invalidateWindow();

    void refreshWindow();

    bool isValidWindow();

    virtual BaseWindow* setX(NCSIZE x);

    virtual BaseWindow* setY(NCSIZE y);

    virtual BaseWindow* setWidth(NCSIZE width);

    virtual BaseWindow* setHeight(NCSIZE height);

    virtual BaseWindow* setName(const std::wstring& name);

    virtual BaseWindow* setPtr(WINDOW* updatedPtr);

    virtual BaseWindow* setBorder(const WindowBorder& border);

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
    NCSIZE width, height, pos_x, pos_y;
    WindowBorder window_border;

    void clearBorder();

    /**
     * construct the buffer of this window, typically including add the displaying line to the buffer and add line wrap
     */
    virtual void constructBuffer() = 0;

    /**
     * clear the buffer
     */
    virtual void clearBuffer() = 0;

    /**
     * display buffer to the window, typically putting the display buffer onto the screen
     */
    virtual void displayBuffer() = 0;

    /**
     * update the buffer content each time buffer is modified, typically add line break and update highlighting
     */
    virtual void updateBuffer() = 0;

    /**
     * make current window get focus
     */
    virtual void enterFocus();

    /**
     * make current window lose focus
     */
    virtual void exitFocus();

    /**
     * dump line into buffer
     */
    virtual void dumpBuffer() = 0;

    // whether this window has focus or not
    bool focus;


};



class TextEditWindow : public BaseWindow {
public:

    enum class WindowState{
        INSERT,
        VIEW
    };

    virtual ~TextEditWindow() override;

    TextEditWindow(WINDOW *data, std::wstring name, const WindowBorder &border, bool focus, NCSIZE startx, NCSIZE starty);

    void addCh(wchar_t ch);

    void addStr(const std::wstring& str);

    void addStrAt(const std::wstring &str, ull line, ull col);

    void popCh();

    void removeChAt(ull linepos, ull colpos);

    void removeChBetween(ull line_begin, ull line_end, ull col_begin, ull col_end);

    [[nodiscard]] std::wstring getDisplayBuffer() const;

protected:
    void constructBuffer() override;

    void displayBuffer() override;

    void updateBuffer() override;

    void clearBuffer() override;

    void dumpBuffer() override;

    /**
    * wrap line of buffer to make it prettier
    */
    virtual void bufferWrapLine();

    // keep track which position the cursor is
    ull line, col;

    WindowState state;
};

#endif //TEXTEDITOR_WINDOW_H
