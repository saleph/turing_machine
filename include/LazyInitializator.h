#ifndef LAZYINITIALIZATOR_H_INCLUDED
#define LAZYINITIALIZATOR_H_INCLUDED

#include <memory>


template<typename T>
class LazyInitializator : public std::unique_ptr<T> {
    public:
        LazyInitializator() // this ctor offers lazy initialization
            : std::unique_ptr<T>()
        {}
        LazyInitializator(const T& val) // for normal construction
            : std::unique_ptr<T> (std::make_unique<T>(val))
        {}
        LazyInitializator& operator= (const T& val) { // assigning value which will be constructed into unique_ptr
            if (!std::unique_ptr<T>::operator bool()) // if object wasn't constructed
                std::unique_ptr<T>::operator= (std::make_unique<T>(val)); // construct it
            **this = val; // use of assingment provided by T - no unneccessary mem allocation
            return *this;
        }
        LazyInitializator& operator= (T&& val) { // for r-value
            if (!std::unique_ptr<T>::operator bool())
                std::unique_ptr<T>::operator= (std::make_unique<T>(val));
            **this = val;
            return *this;
        }
        LazyInitializator& operator() (const T& val) {
            LazyInitializator::operator= (val);
            return *this;
        }
};

#endif // LAZYINITIALIZATOR_H_INCLUDED
