#include "TMTape.h"

// without setting headPosition the head go to the middle of tape
TMTape::TMTape(unsigned int len, shared_ptr<TMAlphabet> alphaSPtr) throw (ZeroLongTape) : TMHead (len/2u) {
    setTapeLength(len);
    initTape(len);
    setAlphabetPtr(alphaSPtr);
}

TMTape::TMTape(unsigned int len, unsigned int headPos, shared_ptr<TMAlphabet> alphaSPtr)
        throw (ZeroLongTape, HeadOutOfTape) : TMHead(headPos) {
    setTapeLength(len);
    checkHeadPosition();
    initTape(len);
    setAlphabetPtr(alphaSPtr);
}

void TMTape::setTapeLength(unsigned int len) throw (ZeroLongTape) {
    checkTapeLength(len);
    tapeLength = len;
}

void TMTape::checkTapeLength(unsigned int len) const throw (ZeroLongTape) {
    if (len == 0u) throw ZeroLongTape();
}

void TMTape::checkHeadPosition() const throw (HeadOutOfTape) {
    if (getHeadPosition() > tapeLength - 1) throw HeadOutOfTape();
}

TMTape::~TMTape() {}

void TMTape::setHeadPosition(unsigned int pos) throw (HeadOutOfTape) {
    checkHeadPosition(pos);
    TMHead::setHeadPosition(pos);
}

void TMTape::checkHeadPosition(unsigned int pos) const throw (HeadOutOfTape) {
    if (pos > tapeLength - 1) throw HeadOutOfTape();
}

unsigned int TMTape::getHeadPosition() const {
    return TMHead::getHeadPosition();
}

void TMTape::initTape(unsigned int len) {
    tape.insert(tape.begin(), len, '#');
    updateHeadPointer();
}

void TMTape::updateHeadPointer() {
    setPointerForCharUnderHead(&tape[getHeadPosition()]);
}

void TMTape::setAlphabetPtr(shared_ptr<TMAlphabet> alphaSPtr) {
    alphabet = alphaSPtr;
}

void TMTape::doCmd(const char before, const char after, MoveType headMove)
        throw (MismatchCommandAndElementUnderHead, CharacterOutOfAlphabet, HeadOutOfTape) {
    checkIfBelongsToAlphabet(before);
    checkIfBelongsToAlphabet(after);
    checkIfMatchWithCharOnTape(before);
    changeCharUnderHeadTo(after);
    moveHeadToThe(headMove);
    checkHeadPosition();
}

void TMTape::changeCharUnderHeadTo(const char character) {
    setValueUnderHead(character);
}

void TMTape::moveHeadToThe(MoveType direction) {
    if (direction == LEFT) moveHeadLeft();
    if (direction == RIGHT) moveHeadRight();
    updateHeadPointer();
}

void TMTape::checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet) {
    if (!alphabet.lock()->has(character)) throw CharacterOutOfAlphabet();
}

void TMTape::checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead) {
    if(getCharUnderHead() != character) throw MismatchCommandAndElementUnderHead();
}
