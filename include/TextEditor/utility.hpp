/**
 * @parent include/TextEditor
 * @file utility.hpp
 * @author ayano
 * @date 12/4/23
 * @brief
*/

#ifndef TEXTEDITOR_UTILITY_HPP
#define TEXTEDITOR_UTILITY_HPP
#include <iterator>


#define swap(x, y)do{ \
(x) += (y);           \
(y) = (x) - (y);      \
(x) -= (y);           \
} while(0)

template<typename T>
struct TypeOf{
    typedef T type;
};

template<typename T>
constexpr TypeOf<T> typeOf(const T&){
    return TypeOf<T>();
}


#endif //TEXTEDITOR_UTILITY_HPP
