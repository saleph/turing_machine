#ifndef TMALPHABET_H
#define TMALPHABET_H

#include <string>
#include <unordered_set>
#include <algorithm>
#include "TMExceptions.h"

class TMAlphabet
{
    public:
        TMAlphabet() = default;
        TMAlphabet(const std::string&);
        TMAlphabet(const std::unordered_set<char>&);
        TMAlphabet(TMAlphabet&) = default;
        TMAlphabet(TMAlphabet&&) = default;
        TMAlphabet& operator= (TMAlphabet&) = default;
        TMAlphabet& operator= (TMAlphabet&&) = default;
        TMAlphabet&& operator= (const std::string& val) { return TMAlphabet(val); }
        virtual ~TMAlphabet() = default;

        std::string getAlphabet();
        std::string getSortedAlphabet();
        void setAlphabet(const std::string&);

        bool has(const char) const;
    private:
        std::unordered_set<char> alphabet;
};

#endif // TMALPHABET_H
