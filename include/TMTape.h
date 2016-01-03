#ifndef TMTAPE_H
#define TMTAPE_H

#include <vector>
#include <stdexcept>
#include "TMHead.h"
using std::invalid_argument;

class ZeroLongTape : public invalid_argument
{
    public:
        ZeroLongTape() : invalid_argument ( "The tape cannot be zero-element-long!" ) {}
};

class HeadOutOfTape : public invalid_argument
{
    public:
        HeadOutOfTape() : invalid_argument ( "The head position has cannot be larger than tapeSize - 1!" ) {}
};


class TMTape : public TMHead
{
    public:
        TMTape(unsigned int len) throw (ZeroLongTape);
        TMTape(unsigned int len, unsigned int headPos) throw (ZeroLongTape, HeadOutOfTape);
        // additional ctors and = to improve unit tests execution
        TMTape(TMTape&) = default;
        TMTape(TMTape&&) = default;
        TMTape& operator= (TMTape&) = default;
        TMTape& operator= (TMTape&&) = default;
        virtual ~TMTape();

        void doCmd (const char before, const char after, MoveType headMove)
            throw (MismatchCommandAndElementUnderHead);
    protected:
    private:
        unsigned int tapeLength;
        std::vector<char> tape;

        void setTapeLength(unsigned int len) throw (ZeroLongTape);
        void checkTapeLength(unsigned int len) const throw (ZeroLongTape);
        void checkHeadPosition() const throw (HeadOutOfTape);
        void initTape(unsigned int len);
};

#endif // TMTAPE_H
