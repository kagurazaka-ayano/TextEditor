/**
 * @parent src
 * @file TerminalUtil.cpp
 * @author ayano
 * @date 12/1/23
 * @brief
*/

#include "TerminalUtil.h"


void putBuffer(const std::string& buffer){
    putchar('\f');
    for(auto i : buffer){
        putchar(i);
    }
}