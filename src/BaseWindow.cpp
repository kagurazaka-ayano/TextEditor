/**
 * @file BaseWindow.cpp
 * @author ayano
 * @date 12/4/23
 * @brief
*/

#include "BaseWindow.h"

BaseWindow::BaseWindow(WINDOW *data, std::wstring name, const WindowBorder &border, bool focus, NCSIZE startx, NCSIZE starty)
        : data(data), name(std::move(name)), window_border(border), focus(focus), width(getmaxx(data)), height(getmaxy(data)),
        pos_y(starty), pos_x(startx), vert_displacement(0){
    display_end_line = 0;
    display_begin_line = 0;
    line_buffer.emplace_back(L"");
    setBorder(window_border);
    mvwaddwstr(data, height, 1, fmt::format(L"Name: {}", this->name).c_str());
}

BaseWindow* BaseWindow::setBorder(const WindowBorder &border) {
    wborder(data, border.ls, border.rs, border.ts, border.bs, border.tl, border.tr, border.bl, border.br);
    window_border = border;
    refreshWindow();
    return this;
}

WINDOW *BaseWindow::getWindowPtr() const noexcept {
    return data;
}

void BaseWindow::invalidateWindow() noexcept {
    data = nullptr;
}

void BaseWindow::refreshWindow() {
    wrefresh(data);
}

bool BaseWindow::isValidWindow() const noexcept {
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
WindowBorder BaseWindow::disabledBorder = WindowBorder(L'·', L'·', L'·', L'·', '*', '*', '*', '*');

/*
 *      ╭─╮
 *      │ │
 *      ╰─╯
 */
WindowBorder BaseWindow::roundBorder = WindowBorder(L'│', L'│', L'─', L'─', L'╭', L'╮', L'╰', L'╯');



void BaseWindow::enterFocus() {
    focus = true;

}

void BaseWindow::exitFocus() {
    focus = false;
}

NCSIZE BaseWindow::getX() const noexcept {
    return pos_x;
}

NCSIZE BaseWindow::getY() const noexcept {
    return pos_y;
}

std::wstring BaseWindow::getName() const noexcept {
    return name;
}

NCSIZE BaseWindow::getWidth() const noexcept {
    return width;
}

NCSIZE BaseWindow::getHeight() const noexcept {
    return height;
}

WindowBorder BaseWindow::getBorder() const noexcept {
    return window_border;
}

BaseWindow* BaseWindow::setPtr(WINDOW* updatedPtr) {
    clearBorder();
    delwin(data);
    this->data = updatedPtr;
    refreshWindow();
    return this;
}

BaseWindow *BaseWindow::setName(const std::wstring &name) {
    this->name = name;
    return this;
}

BaseWindow *BaseWindow::setHeight(NCSIZE height) {
    this->height = height;
    data->_maxy = height;
    return this;
}

BaseWindow *BaseWindow::setWidth(NCSIZE width) {
    this->width = width;
    data->_maxx = height;
    return this;
}

BaseWindow *BaseWindow::setY(NCSIZE y) {
    this->pos_y = y;
    data->_begy = y;
    return this;
}

BaseWindow *BaseWindow::setX(NCSIZE x) {
    this->pos_x = x;
    data->_begx = x;
    return this;
}

void BaseWindow::clearBorder() {
    wborder(data, nullBorder.ls, nullBorder.rs, nullBorder.ts, nullBorder.bs, nullBorder.tl, nullBorder.tr, nullBorder.bl, nullBorder.br);
    window_border = nullBorder;
}

void BaseWindow::attrBegin(const std::initializer_list<attributes> &attr, NCSIZE pos) noexcept {
    unsigned int attrib = 0;
    for(auto i : attr) {
        attrib |= static_cast<unsigned int>(i);
    }
    attr_depth++;
    attr_list[cursor_pos_y].emplace_back(pos, 0, attrib, 0);
    attron(attrib);
}

void BaseWindow::attrEnd(const std::initializer_list<attributes> &attr, NCSIZE pos) noexcept{
    unsigned int attrib = 0;
    for(auto i : attr){
        attrib |= static_cast<unsigned int>(i);
    }
    attr_list[cursor_pos_y][attr_depth].end = pos;
    attr_depth--;
    attroff(attrib);
}

NCSIZE BaseWindow::getCursorX() const noexcept {
    return cursor_pos_x;
}

NCSIZE BaseWindow::getCursorY() const noexcept {
    return cursor_pos_y;
}

