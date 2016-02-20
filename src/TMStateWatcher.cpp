#include "TMStateWatcher.h"

std::shared_ptr<LazyInitializator<std::string>> TMStateWatcher::alphabetAsString =
        std::make_shared<LazyInitializator<std::string>>();
std::shared_ptr<LazyInitializator<size_t>> TMStateWatcher::headPosition =
        std::make_shared<LazyInitializator<size_t>>();
std::shared_ptr<LazyInitializator<size_t>> TMStateWatcher::tapeLength =
        std::make_shared<LazyInitializator<size_t>>();
std::shared_ptr<LazyInitializator<size_t>> TMStateWatcher::tapeContentPosition =
        std::make_shared<LazyInitializator<size_t>>();
std::shared_ptr<LazyInitializator<std::string>> TMStateWatcher::tapeContent =
        std::make_shared<LazyInitializator<std::string>>();
std::shared_ptr<LazyInitializator<std::vector<std::string>>> TMStateWatcher::graphAsText =
        std::make_shared<LazyInitializator<std::vector<std::string>>>();
