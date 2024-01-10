/**
 * @file InputHandler.cpp
 * @author ayano
 * @date 12/20/23
 * @brief
*/

#include "InputHandler.h"

wchar_t InputHandler::getWcharInput(const BaseWindow &window) {
    wint_t ret;
    wget_wch(window.getWindowPtr(), &ret);
    return ret;
}
