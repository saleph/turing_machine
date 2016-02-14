#include "TMStateWatcher.h"

std::shared_ptr<std::string> TMStateWatcher::alphabetAsString;
std::shared_ptr<size_t> TMStateWatcher::headPosition;
std::shared_ptr<size_t> TMStateWatcher::tapeLength;
std::shared_ptr<size_t> TMStateWatcher::tapeContentPosition;
std::shared_ptr<std::string> TMStateWatcher::tapeContent;
std::shared_ptr<std::vector<std::string>> TMStateWatcher::graphAsText;
