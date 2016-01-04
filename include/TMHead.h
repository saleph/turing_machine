#ifndef TMHEAD_H
#define TMHEAD_H

#include "TMExceptions.h"

class TMHead
{ // this class has to be derivided by TMTape
    public:
        TMHead() = default;
        TMHead(unsigned int pos) : headPosition(pos) {};
        TMHead(TMHead&) = default;
        TMHead(TMHead&&) = default;
        virtual ~TMHead() = default;
        TMHead& operator= (TMHead&) = default;
        TMHead& operator= (TMHead&&) = default;
        unsigned int getHeadPosition() const { return headPosition; }
        void setHeadPosition(unsigned int val) { headPosition = val; }
        char getCharUnderHead() const { return *charUnderHead; }
        void setValueUnderHead(const char val) { *charUnderHead = val; }
        void setPointerForCharUnderHead(char *val) { charUnderHead = val; }

        enum MoveType { LEFT, RIGHT };
        void moveHeadRight() { headPosition++; }
        void moveHeadLeft() { headPosition--; }
        // this method will use a tape with data and modify its content
        virtual void doCmd (const char before, const char after, MoveType headMove)
                throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape) = 0;
    private:
        unsigned int headPosition;
        char *charUnderHead;
};

#endif // TMHEAD_H
