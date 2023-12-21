/**
 * @file InputHandler.h
 * @author ayano
 * @date 12/20/23
 * @brief handle all inputs
 * @remark this class is designed to work in multithreading
*/

// TODO: implement this class

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <SingletonAbstract.hpp>
#include <condition_variable>
#include <thread>
#include <future>
#include <Window.h>
#include "ncursesw/ncurses.h"


class InputHandler : public SingletonAbstract<InputHandler> {
    friend SingletonAbstract<InputHandler>;
public:
    void operator()(std::promise<wchar_t>&& promise, const BaseWindow& window);
    InputHandler& operator=(InputHandler& other) = delete;
    InputHandler(InputHandler& other) = delete;
    InputHandler(InputHandler&& other) = delete;
private:
    InputHandler() = default;
};


#endif //INPUTHANDLER_H
