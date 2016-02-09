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
        void operator= (const std::string& val) { setAlphabet(val); }
        virtual ~TMAlphabet() = default;

        std::string getAlphabet();
        std::string getSortedAlphabet();
        void setAlphabet(const std::string&);

        bool has(const char) const;
    private:
        std::unordered_set<char> alphabet;
};

#endif // TMALPHABET_H
