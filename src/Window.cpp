/**
 * @parent src
 * @file Window.cpp
 * @author ayano
 * @date 12/4/23
 * @brief
*/

#include "Window.h"
#include "utility.hpp"

BaseWindow::BaseWindow(WINDOW *data, std::wstring name, const WindowBorder &border, bool focus, NCSIZE startx, NCSIZE starty)
        : data(data), name(std::move(name)), window_border(border), focus(focus), width(getmaxx(data)), height(getmaxy(data)),
        pos_y(starty), pos_x(startx), vert_displacement(0){
    display_end_line = 0;
    display_begin_line = 0;
    line_buffer.emplace_back(L"");
    setBorder(window_border);
    std::wstringstream ss;
    ss << L"Name: " << this->name;
    mvwaddwstr(data, height, 1, ss.str().c_str());
}

void BaseWindow::setBorder(const WindowBorder &border) {
    wborder(data, border.ls, border.rs, border.ts, border.bs, border.tl, border.tr, border.bl, border.br);
}

WINDOW *BaseWindow::getWindowPtr() const {
    return data;
}

void BaseWindow::invalidateWindow() {
    data = nullptr;
}

bool BaseWindow::isValidWindow() {
    return data != nullptr;
}

BaseWindow::~BaseWindow() {
    if (data == nullptr) return;
    setBorder(nullBorder);
    wrefresh(data);
    delwin(data);
    data = nullptr;
    invalidateWindow();
}

WindowBorder::WindowBorder(wchar_t ls, wchar_t rs, wchar_t ts, wchar_t bs,
                           wchar_t tl, wchar_t tr, wchar_t bl, wchar_t br)
        : ls(ls), rs(rs), ts(ts), bs(bs), tl(tl), tr(tr), bl(bl), br(br) {
}
/*
 *      +-+
 *      | |
 *      +-+
 */

WindowBorder BaseWindow::simpleBorder = WindowBorder('|', '|', '-', '-', '+', '+', '+', '+');

/*
 *
 *
 *
 *
 */
WindowBorder BaseWindow::nullBorder = WindowBorder(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');

/*
 *      @*@
 *      * *
 *      @*@
 */
WindowBorder BaseWindow::starBorder = WindowBorder('*', '*', '*', '*', '@', '@', '@', '@');

/*
 *      *·*
 *      · ·
 *      *·*
 */
WindowBorder BaseWindow::disabledBorder = WindowBorder(u'·', u'·', u'·', u'·', '*', '*', '*', '*');

/*
 *      ╭─╮
 *      │ │
 *      ╰─╯
 */
WindowBorder BaseWindow::roundBorder = WindowBorder(u'│', u'│', u'─', u'─', u'╭', u'╮', u'╰', u'╯');



void BaseWindow::enterFocus() {
    focus = true;

}

void BaseWindow::exitFocus() {
    focus = false;
}

NCSIZE BaseWindow::getX() const {
    return pos_x;
}

NCSIZE BaseWindow::getY() const {
    return pos_y;
}

std::wstring BaseWindow::getName() const {
    return name;
}

NCSIZE BaseWindow::getWidth() const {
    return width;
}

NCSIZE BaseWindow::getHeight() const {
    return height;
}

WindowBorder BaseWindow::getBorder() const {
    return window_border;
}

void TextEditWindow::bufferWrapLine() {
    for(auto i = display_begin_line; i <= display_end_line; i++){
        if (line_buffer[i].contains('\n')) continue;
        for (int j = width; j < line_buffer[i].size(); j += width) {
            line_buffer[i].insert(j, L"\n");
        }
    }
}

void TextEditWindow::dumpBuffer() {
    ull line_diff = vert_displacement - display_begin_line;
    std::wstring before = line_buffer[display_begin_line];
    ull last_pos = before.find(L'\n', 0);
    for(ull i = 0; i < line_diff; i++){
        if(last_pos == std::wstring::npos) break;
        before = before.substr(last_pos, before.size());
        last_pos = before.find(L'\n', last_pos);
    }
    auto pos = line_buffer[display_end_line].rfind(L'\n');
    std::wstring after;
    if (pos != std::wstring::npos) after = line_buffer[display_end_line].substr(pos);
    else after = line_buffer[display_end_line];
    display_buffer = before;
    if (display_begin_line + 1 < display_end_line - 1) {
        for (ull i = display_begin_line + 1; i < display_end_line - 1; i++) {
            display_buffer += line_buffer[i] + L'\n';
        }
    }
    display_buffer += after;
}

void TextEditWindow::constructBuffer() {
    display_buffer = L"";

}

void TextEditWindow::displayBuffer() {
    bufferWrapLine();
    dumpBuffer();
    mvaddwstr(pos_y + 1, pos_x + 1, display_buffer.c_str());
}

TextEditWindow::TextEditWindow(WINDOW *data, std::wstring name, const WindowBorder &border, bool focus, NCSIZE startx,
                               NCSIZE starty) : BaseWindow(data, std::move(name), border, focus, startx, starty), state(WindowState::VIEW) {
    line = 0;
    col = 0;
    line_buffer.emplace_back(L"");
}

void TextEditWindow::addCh(wchar_t ch) {
    if (line_buffer.size() == line) {
        line_buffer.emplace_back(L"");
        line++;
        display_end_line = std::min(display_end_line + 1, display_begin_line + height);
    }
    line_buffer[line].push_back(ch);
    displayBuffer();
}

void TextEditWindow::addStr(const std::wstring &str) {
    if (line_buffer.size() == line) {
        line_buffer.emplace_back(L"");
        line++;
        display_end_line = std::min(display_end_line + 1, display_begin_line + height);
    }
    line_buffer[line].append(str);
    displayBuffer();
}

void TextEditWindow::addStrAt(const std::wstring &str, ull pos, ull col) {
    if (pos >= line_buffer.size()) return;
    if (line_buffer[pos].size() >= col) return;
    line_buffer[pos].insert(col, str);
    displayBuffer();
}

void TextEditWindow::popCh() {
    line_buffer[line].pop_back();
    if (line_buffer[line].empty()) line_buffer.erase(line_buffer.begin() + line);
    displayBuffer();
}

void TextEditWindow::removeChAt(ull linepos, ull colpos) {
    if (linepos >= line_buffer.size()) return;
    if (line_buffer[colpos].size() <= colpos) return;
    line_buffer[colpos].erase(colpos);

    if (line_buffer[linepos].empty()) line_buffer.erase(line_buffer.begin() + linepos);
    displayBuffer();
}

void TextEditWindow::removeChBetween(ull line_begin, ull line_end, ull col_begin, ull col_end) {
    if (line_begin >= line_buffer.size() || line_end >= line_buffer.size()) return;
    if (line_buffer[line_begin].size() <= col_begin || line_buffer[line_end].size() <= col_end) return;
    if (line_begin > line_end) swap(line_begin, line_end);
    if (col_begin > col_end) swap(col_begin, col_end);
    line_buffer[line_begin].erase(col_begin, line_buffer[line_begin].size() - 1);
    line_buffer[line_end].erase(0, col_end);
    if (line_begin != line_end) line_buffer.erase(line_buffer.begin() + line_begin + 1, line_buffer.begin() + line_end - 1);
    displayBuffer();
}

void TextEditWindow::updateBuffer() {
    bufferWrapLine();
    display_buffer.clear();
    ull line_diff = vert_displacement - display_begin_line;
    std::wstring before = line_buffer[display_begin_line];
    ull last_pos = 0;
    for(ull i = 0; i < line_diff; i++){
        before = before.substr(last_pos);
        last_pos = before.find(L'\n', 0);
    }
    for(auto i = display_begin_line + 1; i < display_end_line - 1; i++){
        display_buffer.append(line_buffer[i] + L'\n');
    }
    auto pos = line_buffer[display_end_line].find('\n', 0);
    if (pos == std::wstring::npos)
        display_buffer.append(line_buffer[display_end_line]);
    else
        display_buffer.append(line_buffer[display_end_line].substr(0, pos));
}

std::wstring TextEditWindow::getDisplayBuffer() const {
    return display_buffer;
}

void TextEditWindow::clearBuffer() {
    display_begin_line = 0;
    display_end_line = height - 1;
    display_buffer = L"";
    line_buffer.clear();
}

TextEditWindow::~TextEditWindow() {
    setBorder(nullBorder);
    wrefresh(data);
    delwin(data);
    invalidateWindow();
}
