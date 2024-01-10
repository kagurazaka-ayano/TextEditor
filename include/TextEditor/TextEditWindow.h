/**
 * @file TextEditWindow.h
 * @author ayano
 * @date 12/24/23
 * @brief
*/

#ifndef TEXTEDITOR_TEXTEDITWINDOW_H
#define TEXTEDITOR_TEXTEDITWINDOW_H

#include "BaseWindow.h"

class TextEditWindow : public BaseWindow {
public:

    enum class WindowState{
        INSERT,
        VIEW
    };

    virtual ~TextEditWindow();

    TextEditWindow(WINDOW *data, std::wstring name, const WindowBorder &border, bool focus, NCSIZE startx, NCSIZE starty);

    /**
     * @brief add a character at the end of current line
     * @param ch character to add
     */
    void addCh(wchar_t ch);

    /**
     * @brief add a string at the end of current line
     * @param str string to add
     */
    void addStr(const std::wstring& str);

    /**
     * @brief add a string at given location (line and col)
     * @param str string to add
     * @param line dest line
     * @param col dest col(nth character, start from 0)
     */
    void addStrAt(const std::wstring &str, ull line, ull col);

    /**
     * @brief remove last character from current line
     */
    void popCh();

    /**
     * @brief remove the character at given position
     * @param linepos character line
     * @param colpos character col
     */
    void removeChAt(ull linepos, ull colpos);

    /**
     * @brief remove all character between the given range
     * @param line_begin line range begin
     * @param line_end line range end
     * @param col_begin col range begin(character after this position on first line, inclusive)
     * @param col_end col range end(character before this position on the last line, inclusive)
     */
    void removeChBetween(ull line_begin, ull line_end, ull col_begin, ull col_end);

    /**
     * @brief get current display buffer of this window
     * @return display buffer
     */
    [[nodiscard]] std::wstring getDisplayBuffer() const noexcept;

protected:
    void constructBuffer() override;

    void displayBuffer() override;

    void updateBuffer() override;

    void clearBuffer() override;

    void dumpBuffer() override;

    /**
    * @brief wrap line of buffer to make it prettier
    */
    virtual void bufferWrapLine();

    // keep track which position the cursor is
    ull line, col;

    WindowState state;

    void updateAttribute() override;
};

#endif //TEXTEDITOR_TEXTEDITWINDOW_H
