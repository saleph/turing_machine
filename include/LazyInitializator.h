#ifndef LAZYINITIALIZATOR_H_INCLUDED
#define LAZYINITIALIZATOR_H_INCLUDED

#include <memory>


template<typename T>
class LazyInitializator : public std::unique_ptr<T> {
    public:
        LazyInitializator() : std::unique_ptr<T>() {} // this ctor offers lazy initialization
        LazyInitializator(const T& val) : std::unique_ptr<T> (std::make_unique<T>(val)) {} // for normal construction
        LazyInitializator& operator= (const T& val) { // assigning value which will be constructed into unique_ptr
            if (!std::unique_ptr<T>::operator bool()) // if object wasn't constructed
                std::unique_ptr<T>::operator= (std::make_unique<T>(val)); // construct it
            **this = val; // use of assingment provided by T - no unneccessary mem allocation
            return *this;
        }
};

#endif // LAZYINITIALIZATOR_H_INCLUDED
