#include "TMAlphabet.h"

TMAlphabet::TMAlphabet(const std::string& strVal) {
    alphabet.insert (strVal.begin(), strVal.end());
}

TMAlphabet::TMAlphabet(const std::unordered_set<char>& usetVal) {
    alphabet = usetVal;
}

std::string TMAlphabet::getAlphabet() {
    return std::string(alphabet.begin(), alphabet.end());
}

std::string TMAlphabet::getSortedAlphabet() {
    std::string strAlpha {getAlphabet()};
    std::sort (strAlpha.begin(), strAlpha.end());
    return strAlpha;
}

void TMAlphabet::setAlphabet(const std::string& strVal) {
    alphabet.clear();
    alphabet.insert (strVal.begin(), strVal.end());
}

bool TMAlphabet::has(const char sign) {
    int occurrences = alphabet.count(sign);
    return occurrences > 0 ? true : false;
}
