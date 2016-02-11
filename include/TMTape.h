#ifndef TMTAPE_H
#define TMTAPE_H

#include <vector>
#include <memory>
#include "TMHead.h"
#include "TMAlphabet.h"
#include "TMExceptions.h"


class TMTape : public TMHead
{
    public:
        TMTape(size_t len, std::shared_ptr<TMAlphabet>) throw (ZeroLongTape);
        virtual ~TMTape();

        char& operator[] (size_t idx) { return tape[idx]; }

        using TapeIterator = std::vector<char>::iterator;
        TapeIterator begin() { return tape.begin(); }
        TapeIterator end() { return tape.end(); }
        using ConstTapeIterator = std::vector<char>::const_iterator;
        ConstTapeIterator cbegin() const { return tape.cbegin(); }
        ConstTapeIterator cend() const { return tape.cend(); }

        virtual void setHeadPosition(size_t pos) throw (HeadOutOfTape);
        virtual size_t getHeadPosition() const;

        void doCmd (const char before, const char after, TMHeadMoveType headMove)
                throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape);
        void reset();
    private:
        size_t tapeLength;
        std::vector<char> tape;
        std::weak_ptr<TMAlphabet> alphabet;

        void setTapeLength(size_t len) throw (ZeroLongTape);
        void checkTapeLength(size_t len) const throw (ZeroLongTape);
        void checkHeadPosition() const throw (HeadOutOfTape);
        void checkHeadPosition(size_t pos) const throw (HeadOutOfTape);
        void initTape(size_t len);
        void setAlphabetPtr(std::shared_ptr<TMAlphabet>);
        void setTapePtr(std::shared_ptr<std::vector<char>> tapePtr);
        void changeCharUnderHeadTo(const char character);
        void moveHeadToThe(TMHeadMoveType direction);
        void updateHeadPointer();
        void checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet);
        void checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead);
        void fillTheTapeWithHashes();
};

#endif // TMTAPE_H
