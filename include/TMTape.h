#ifndef TMTAPE_H
#define TMTAPE_H

#include <vector>
#include <stdexcept>
#include "TMHead.h"
#include "TMAlphabet.h"
#include "TMExceptions.h"


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

        const char& operator[] (std::size_t idx) const { return tape[idx]; }
        virtual void setHeadPosition(unsigned int pos) throw (HeadOutOfTape);
        virtual unsigned int getHeadPosition() const;

        void doCmd (const char before, const char after, MoveType headMove)
            throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape);

        TMAlphabet alphabet;
    protected:
    private:
        unsigned int tapeLength;
        std::vector<char> tape;

        void setTapeLength(unsigned int len) throw (ZeroLongTape);
        void checkTapeLength(unsigned int len) const throw (ZeroLongTape);
        void checkHeadPosition() const throw (HeadOutOfTape);
        void checkHeadPosition(unsigned int pos) const throw (HeadOutOfTape);
        void initTape(unsigned int len);
        void changeCharUnderHeadTo(const char character);
        void moveHeadToThe(MoveType direction);
        void updateHeadPointer();
        void checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet);
        void checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead);
};

#endif // TMTAPE_H
