/**
 * @parent include/TextEditor
 * @file SingletonAbstract.hpp
 * @author ayano
 * @date 12/1/23
 * @brief
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
