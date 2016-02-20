#ifndef TMSTATEWATCHER_H
#define TMSTATEWATCHER_H

#include "LazyInitializator.h"
#include <memory>
#include <vector>


struct TMStateWatcher
{
    TMStateWatcher() = delete;
    static std::shared_ptr<LazyInitializator<std::string>> alphabetAsString;
    static std::shared_ptr<LazyInitializator<size_t>> headPosition;
    static std::shared_ptr<LazyInitializator<size_t>> tapeLength;
    static std::shared_ptr<LazyInitializator<size_t>> tapeContentPosition;
    static std::shared_ptr<LazyInitializator<std::string>> tapeContent;
    static std::shared_ptr<LazyInitializator<std::vector<std::string>>> graphAsText;

    static bool prepared() { // dereference because shared_ptr contains unique_ptr with content
        return (*alphabetAsString && *headPosition && *tapeLength
            && *tapeContentPosition && *tapeContent && *graphAsText);
    }

    static void reset() { // members of StateWatcher are only pointers to unique_ptr, so -> is neccessary
        alphabetAsString->reset();
        graphAsText->reset();
        headPosition->reset();
        tapeContent->reset();
        tapeContentPosition->reset();
        tapeLength->reset();
    }
};

#endif // TMSTATEWATCHER_H
