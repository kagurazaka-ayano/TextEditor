#include <iostream>
#include <string>
#include "KeyDefinition.h"
#include "TerminalUtil.h"
#include "InputHandler.h"
int main() {
    std::string buffer;
    std::string buffer_displaying;

    char in = 0;
    while(in != EOF){
        in = static_cast<char>(getchar());
        if (in != '0'){
            buffer += in;
        }
        putBuffer(buffer);
    }
    return 0;
}
