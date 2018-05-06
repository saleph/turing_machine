#ifndef TMTAPE_H
#define TMTAPE_H

#include <vector>
#include <memory>
#include <functional>
#include "TMHead.h"
#include "TMAlphabet.h"
#include "TMExceptions.h"


class TMTape : public TMHead
{
    public:
        TMTape(size_t len, std::shared_ptr<TMAlphabet>&) throw (ZeroLongTape);
        virtual ~TMTape();

        TMTape& operator= (const std::vector<char>&);
        char& operator[] (const size_t idx) { return tape.at(idx);
                                              tapeEditNotifier(idx, idx);}
        char& at(const size_t idx) { return tape.at(idx);
                                     tapeEditNotifier(idx, idx);}

        using TapeIterator = std::vector<char>::iterator;
        TapeIterator begin() { return tape.begin(); }
        TapeIterator end() { return tape.end(); }
        using ConstTapeIterator = std::vector<char>::const_iterator;
        ConstTapeIterator cbegin() const { return tape.cbegin(); }
        ConstTapeIterator cend() const { return tape.cend(); }
        size_t size() { return tape.size(); }

        virtual void setHeadPosition(const size_t pos) throw (HeadOutOfTape);
        virtual size_t getHeadPosition() const;

        void doCmd (const char before, const char after, TMHeadMoveType headMove)
                throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape);
        void reset();
        void setNewTapeLength(const size_t len);
        void insertContentAt(const size_t pos, std::string& content);
        void installTapeEditNotifier(std::function<void(size_t, size_t)> n) { tapeEditNotifier = n; }
        void installHeadEditNotifier(std::function<void()> n) { headEditNotifier = n; }
    private:
        size_t tapeLength;
        std::vector<char> tape;
        std::weak_ptr<TMAlphabet> alphabet;
public:
        std::function<void(size_t, size_t)> tapeEditNotifier = [](size_t, size_t){};
        std::function<void()> headEditNotifier = []{};
private:

        void setTapeLength(const size_t len) throw (ZeroLongTape);
        void checkTapeLength(const size_t len) const throw (ZeroLongTape);
        void checkHeadPosition() const throw (HeadOutOfTape);
        void checkHeadPosition(const size_t pos) const throw (HeadOutOfTape);
        void initTape(const size_t len);
        void setAlphabetPtr(std::shared_ptr<TMAlphabet>);
        void setTapePtr(std::shared_ptr<std::vector<char>> tapePtr);
        void changeCharUnderHeadTo(const char character);
        void moveHeadToThe(TMHeadMoveType direction);
        void updateHeadPointer();
        void checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet);
        void checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead);
        void fillTheTapeWithHashes();
        void updateTapeSize();
};

#endif // TMTAPE_H
