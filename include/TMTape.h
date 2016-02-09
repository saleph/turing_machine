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
using std::fill;


class TMTape : public TMHead
{
    public:
        TMTape(size_t len, shared_ptr<TMAlphabet>) throw (ZeroLongTape);
        TMTape(size_t len, size_t headPos, shared_ptr<TMAlphabet>) throw (ZeroLongTape, HeadOutOfTape);
        virtual ~TMTape();

        char& operator[] (size_t idx) { return tape[idx]; }
        using TapeIterator = std::vector<char>::iterator;
        TapeIterator begin() { return tape.begin(); }
        TapeIterator end() { return tape.end(); }
        using ConstTapeIterator = std::vector<char>::const_iterator;
        const ConstTapeIterator cbegin() const { return tape.cbegin(); }
        const ConstTapeIterator cend() const { return tape.cend(); }
        virtual void setHeadPosition(size_t pos) throw (HeadOutOfTape);
        virtual size_t getHeadPosition() const;

        void doCmd (const char before, const char after, TMHeadMoveType headMove)
                throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape);
        void reset();
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
        void setTapePtr(shared_ptr<vector<char>> tapePtr);
        void changeCharUnderHeadTo(const char character);
        void moveHeadToThe(TMHeadMoveType direction);
        void updateHeadPointer();
        void checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet);
        void checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead);
        void fillTheTapeWithHashes();
};

#endif // TMTAPE_H
