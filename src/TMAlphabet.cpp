#include "TMAlphabet.h"

TMAlphabet::TMAlphabet(const std::string& strVal) {
    alphabet.insert (strVal.begin(), strVal.end());
}

TMAlphabet::TMAlphabet(const std::unordered_set<char>& usetVal) {
    alphabet = usetVal;
}

std::string TMAlphabet::getAlphabet() {
    std::string strAlphabet;
    for (const char& sign : alphabet)
        strAlphabet += sign;
    return strAlphabet;
}

bool TMAlphabet::has(const char sign) {
    int retVal = alphabet.count(sign);
    return retVal > 0 ? true : false;
}
