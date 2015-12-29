#ifndef TMALPHABET_H
#define TMALPHABET_H

#include <string>
#include <unordered_set>


class TMAlphabet
{
    public:
        TMAlphabet() {};
        TMAlphabet(const std::string&);
        TMAlphabet(const std::unordered_set<char>&);
        virtual ~TMAlphabet() {};

        std::string getAlphabet();

        bool has(const char);
    protected:
    private:
        std::unordered_set<char> alphabet;
};

#endif // TMALPHABET_H
