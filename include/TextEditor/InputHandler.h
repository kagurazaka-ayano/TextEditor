/**
 * @file InputHandler.h
 * @author ayano
 * @date 12/20/23
 * @brief handle all inputs
 * @remark this class is designed to work in multithreading
*/

// TODO: implement this class
// TODO: add callback functionality

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <SingletonAbstract.hpp>
#include <condition_variable>
#include <thread>
#include <future>
#include <BaseWindow.h>
#include "ncursesw/ncurses.h"


class InputHandler : public SingletonAbstract<InputHandler> {
    friend SingletonAbstract<InputHandler>;
public:
    InputHandler& operator=(InputHandler& other) = delete;
    InputHandler(InputHandler& other) = delete;
    InputHandler(InputHandler&& other) = delete;
    wchar_t getWcharInput(const BaseWindow& window);
private:
    InputHandler() = default;
};


#endif //INPUTHANDLER_H
