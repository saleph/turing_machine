#ifndef TMTAPE_H
#define TMTAPE_H

#include <vector>
#include "TMHead.h"


class TMTape : public TMHead
{
    public:
        TMTape(unsigned int len) : tapeLength(len), TMHead (tapeLength/2u) { initTape(len); }
        TMTape(unsigned int len, unsigned int headPos) : tapeLength(len), TMHead(headPos) { initTape(len); }
        TMTape(TMTape&) = default;
        TMTape(TMTape&&) = default;
        TMTape& operator= (TMTape&) = default;
        TMTape& operator= (TMTape&&) = default;
        virtual ~TMTape() = default;

        void doCmd (const char before, const char after, MoveType headMove)
            throw (MismatchCommandAndElementUnderHead);
    protected:
    private:
        unsigned int tapeLength;
        std::vector<char> tape;

        void initTape(unsigned int len);
};

#endif // TMTAPE_H
