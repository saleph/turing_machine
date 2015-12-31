#ifndef TMALPHABET_H
#define TMALPHABET_H

#include <string>
#include <unordered_set>
#include <algorithm>


class TMAlphabet
{
    public:
        TMAlphabet() {};
        TMAlphabet(const std::string&);
        TMAlphabet(const std::unordered_set<char>&);
        virtual ~TMAlphabet() {};

        std::string getAlphabet();
        std::string getSortedAlphabet();
        void setAlphabet(const std::string&);

        bool has(const char);
    private:
        std::unordered_set<char> alphabet;
};

#endif // TMALPHABET_H
