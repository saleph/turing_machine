#include "TMAlphabet.h"

TMAlphabet::TMAlphabet(const string& strVal) {
    alphabet.insert (strVal.begin(), strVal.end());
}

TMAlphabet::TMAlphabet(const unordered_set<char>& usetVal) {
    alphabet = usetVal;
}

string TMAlphabet::getAlphabet() {
    return string(alphabet.begin(), alphabet.end());
}

string TMAlphabet::getSortedAlphabet() {
    string strAlpha {getAlphabet()};
    std::sort (strAlpha.begin(), strAlpha.end());
    return strAlpha;
}

void TMAlphabet::setAlphabet(const string& strVal) {
    alphabet.clear();
    alphabet.insert (strVal.begin(), strVal.end());
}

bool TMAlphabet::has(const char sign) const {
    int occurrences = alphabet.count(sign);
    return occurrences > 0 ? true : false;
}
