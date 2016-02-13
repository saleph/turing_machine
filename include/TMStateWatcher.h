#ifndef TMSTATEWATCHER_H
#define TMSTATEWATCHER_H

#include <memory>
#include <vector>

struct TMStateWatcher
{
    static std::shared_ptr<std::string> alphabetAsString;
    static std::shared_ptr<size_t> headPosition;
    static std::shared_ptr<size_t> tapeLength;
    static std::shared_ptr<size_t> tapeContentPosition;
    static std::shared_ptr<std::string> tapeContent;
    static std::shared_ptr<std::vector<std::string>> graphAsText;

    static bool prepared() const {
        return (alphabetAsString && headPosition && tapeLength
            && tapeContentPosition && tapeContent && graphAsText);
    }
};

#endif // TMSTATEWATCHER_H
