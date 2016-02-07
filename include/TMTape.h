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
        TMTape(size_t len, shared_ptr<TMAlphabet>) throw (ZeroLongTape);
        TMTape(size_t len, size_t headPos, shared_ptr<TMAlphabet>) throw (ZeroLongTape, HeadOutOfTape);
        virtual ~TMTape();

        const char& operator[] (std::size_t idx) const { return tape[idx]; }
        virtual void setHeadPosition(size_t pos) throw (HeadOutOfTape);
        virtual size_t getHeadPosition() const;

        void doCmd (const char before, const char after, TMHeadMoveType headMove)
                throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape);
    protected:
    private:
        size_t tapeLength;
        vector<char> tape;
        weak_ptr<TMAlphabet> alphabet;

        void setTapeLength(size_t len) throw (ZeroLongTape);
        void checkTapeLength(size_t len) const throw (ZeroLongTape);
        void checkHeadPosition() const throw (HeadOutOfTape);
        void checkHeadPosition(size_t pos) const throw (HeadOutOfTape);
        void initTape(size_t len);
        void setAlphabetPtr(shared_ptr<TMAlphabet>);
        void changeCharUnderHeadTo(const char character);
        void moveHeadToThe(TMHeadMoveType direction);
        void updateHeadPointer();
        void checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet);
        void checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead);
};

#endif // TMTAPE_H
