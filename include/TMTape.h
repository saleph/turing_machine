#ifndef TMTAPE_H
#define TMTAPE_H

#include <vector>
#include <stdexcept>
#include <memory>
#include "TMHead.h"
#include "TMAlphabet.h"
#include "TMExceptions.h"
using std::weak_ptr;
using std::shared_ptr;
using std::vector;


class TMTape : public TMHead
{
    public:
        TMTape(unsigned int len, shared_ptr<TMAlphabet>) throw (ZeroLongTape);
        TMTape(unsigned int len, unsigned int headPos, shared_ptr<TMAlphabet>) throw (ZeroLongTape, HeadOutOfTape);
        virtual ~TMTape();

        const char& operator[] (std::size_t idx) const { return tape[idx]; }
        virtual void setHeadPosition(unsigned int pos) throw (HeadOutOfTape);
        virtual unsigned int getHeadPosition() const;

        void doCmd (const char before, const char after, MoveType headMove)
                throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape);
    protected:
    private:
        unsigned int tapeLength;
        vector<char> tape;
        weak_ptr<TMAlphabet> alphabet;

        void setTapeLength(unsigned int len) throw (ZeroLongTape);
        void checkTapeLength(unsigned int len) const throw (ZeroLongTape);
        void checkHeadPosition() const throw (HeadOutOfTape);
        void checkHeadPosition(unsigned int pos) const throw (HeadOutOfTape);
        void initTape(unsigned int len);
        void setAlphabetPtr(shared_ptr<TMAlphabet>);
        void changeCharUnderHeadTo(const char character);
        void moveHeadToThe(MoveType direction);
        void updateHeadPointer();
        void checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet);
        void checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead);
};

#endif // TMTAPE_H
