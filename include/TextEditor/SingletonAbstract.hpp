/**
 * @file SingletonAbstract.hpp
 * @author ayano
 * @date 12/1/23
 * @brief a singleton class for all singletons to inherit, defined many useful methods and vars
 * @remark when inheriting this class you must set this class a friend of the derived class and explicitly make </br>
 * constructor private, delete equal operator and copy and move constructor. And the constructor cannot have any parameter
*/

#ifndef TEXTEDITOR_SINGLETONABSTRACT_H
#define TEXTEDITOR_SINGLETONABSTRACT_H

#include <mutex>

template<typename T>
class SingletonAbstract {
private:
    static std::unique_ptr<T> instance;
    static std::mutex mutex;
protected:
    SingletonAbstract() = default;
    virtual ~SingletonAbstract() = default;
public:
    static T* Instance();
    T operator=(T other) = delete;
    SingletonAbstract(SingletonAbstract& other) = delete;
    SingletonAbstract(SingletonAbstract&& other) = delete;
};

template<typename T>
T *SingletonAbstract<T>::Instance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr){
        instance.reset(new T);
    }
    return instance.get();
}

template<typename T>
std::mutex SingletonAbstract<T>::mutex;

template<typename T>
std::unique_ptr<T> SingletonAbstract<T>::instance = nullptr;


#endif //TEXTEDITOR_SINGLETONABSTRACT_H
