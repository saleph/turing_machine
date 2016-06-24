#ifndef LAZYINITIALIZATOR_H_INCLUDED
#define LAZYINITIALIZATOR_H_INCLUDED

#include <memory>


template<typename T>
class LazyInitializator : public std::unique_ptr<T> {
    public:
        LazyInitializator() // this ctor offers lazy initialization
            : std::unique_ptr<T>()
        {}
        template<class T_t>
        LazyInitializator(T_t&& val) // for normal construction
            : std::unique_ptr<T> (std::make_unique<T>(std::forward<T_t>(val)))
        {}
        template<class T_t>
        LazyInitializator& operator= (T_t&& val) { // for r-value
            if (!std::unique_ptr<T>::operator bool())
                std::unique_ptr<T>::operator= (std::make_unique<T>(std::forward<T_t>(val)));
            **this = val;
            return *this;
        }
        LazyInitializator& operator() (const T& val) {
            LazyInitializator::operator= (val);
            return *this;
        }
};

#endif // LAZYINITIALIZATOR_H_INCLUDED
