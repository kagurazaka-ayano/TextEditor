/**
 * @file TextEditWindow.cpp
 * @author ayano
 * @date 12/24/23
 * @brief
*/

#include "TextEditWindow.h"

void TextEditWindow::bufferWrapLine() {
    for (auto& i : line_buffer) {
        if (i.length() <= getWidth() - 2) continue;
        // if already processed
        if (i.find(L'\n') != std::string::npos) {
            auto last = i.rfind(L'\n');
            if (i.size() - last <= getWidth() - 2) continue;
            i.insert(last + (i.size() - last) % (getWidth() - 2), L"\n");
        }
        // if not processed
        else {
            auto len = i.size();
            auto pos = 0;
            while (len > getWidth() - 2) {
                pos += getWidth() - 2;
                i.insert(pos, L"\n");
                // inserted a EOL, must increment 1
                pos++;
                len -= (getWidth() - 2);
            }
        }
    }
}

void TextEditWindow::dumpBuffer() {
    display_buffer.clear();
    for (const auto& i : line_buffer){
        display_buffer += i + L'\n';
    }
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

void TextEditWindow::updateAttribute() {

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
    if (line_begin > line_end) std::swap(line_begin, line_end);
    if (col_begin > col_end) std::swap(col_begin, col_end);
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

std::wstring TextEditWindow::getDisplayBuffer() const noexcept {
    return display_buffer;
}

void TextEditWindow::clearBuffer() {
    display_begin_line = 0;
    display_end_line = height - 1;
    display_buffer = L"";
    line_buffer.clear();
}

TextEditWindow::~TextEditWindow() {
    clearBorder();
    wrefresh(data);
    delwin(data);
    invalidateWindow();
}
