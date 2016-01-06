#ifndef TMALPHABET_H
#define TMALPHABET_H

#include <string>
#include <unordered_set>
#include <algorithm>
#include "TMExceptions.h"
using std::string;
using std::unordered_set;

class TMAlphabet
{
    public:
        TMAlphabet() = default;
        TMAlphabet(const string&);
        TMAlphabet(const unordered_set<char>&);
        TMAlphabet(TMAlphabet&) = default;
        TMAlphabet(TMAlphabet&&) = default;
        TMAlphabet& operator= (TMAlphabet&) = default;
        TMAlphabet& operator= (TMAlphabet&&) = default;
        TMAlphabet&& operator= (const string& val) { return TMAlphabet(val); }
        virtual ~TMAlphabet() = default;

        string getAlphabet();
        string getSortedAlphabet();
        void setAlphabet(const string&);

        bool has(const char) const;
    private:
        unordered_set<char> alphabet;
};

#endif // TMALPHABET_H
