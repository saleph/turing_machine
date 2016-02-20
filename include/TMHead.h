#ifndef TMHEAD_H
#define TMHEAD_H

#include "TMExceptions.h"
#include "TMHeadMoveType.h"

class TMHead
{ // this class has to be derivided by TMTape
    public:
        TMHead() = default;
        TMHead(const size_t pos) : headPosition(pos) {};
        TMHead(const TMHead&) = default;
        TMHead(TMHead&&) = default;
        virtual ~TMHead() = default;
        TMHead& operator= (const TMHead&) = default;
        TMHead& operator= (TMHead&&) = default;
        size_t getHeadPosition() const { return headPosition; }
        void setHeadPosition(const size_t val) { headPosition = val; }
        char getCharUnderHead() const { return *charUnderHead; }
        void setValueUnderHead(const char val) { *charUnderHead = val; }
        void setPointerToCharUnderHead(char *val) { charUnderHead = val; }

        void moveHeadRight() { headPosition++; }
        void moveHeadLeft() { headPosition--; }
        // this method will use a tape with data and modify its content
        virtual void doCmd (const char before, const char after, TMHeadMoveType headMove)
                throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape) = 0;
    private:
        size_t headPosition;
        char *charUnderHead;
};

#endif // TMHEAD_H
