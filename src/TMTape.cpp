#include "TMTape.h"
#include <iostream>
// without setting headPosition the head go to the middle of tape
TMTape::TMTape(size_t len, std::shared_ptr<TMAlphabet>& alphaSPtr) throw (ZeroLongTape) : TMHead (len/2u) {
    setTapeLength(len);
    initTape(len);
    setAlphabetPtr(alphaSPtr);
}

void TMTape::setTapeLength(const size_t len) throw (ZeroLongTape) {
    checkTapeLength(len);
    tapeLength = len;
}

void TMTape::checkTapeLength(const size_t len) const throw (ZeroLongTape) {
    if (len == 0u) throw ZeroLongTape();
}

void TMTape::checkHeadPosition() const throw (HeadOutOfTape) {
    if (getHeadPosition() > tapeLength - 1) throw HeadOutOfTape();
}

TMTape::~TMTape() noexcept {}


TMTape& TMTape::operator= (const std::vector<char>& otherVec) {
    tape = otherVec;
    return *this;
}

void TMTape::setHeadPosition(const size_t pos) throw (HeadOutOfTape) {
    checkHeadPosition(pos);
    TMHead::setHeadPosition(pos);
    updateHeadPointer();
}

void TMTape::checkHeadPosition(const size_t pos) const throw (HeadOutOfTape) {
    if (pos > tapeLength - 1) throw HeadOutOfTape();
}

size_t TMTape::getHeadPosition() const {
    return TMHead::getHeadPosition();
}

void TMTape::initTape(const size_t len) {
    tape.insert(tape.begin(), len, '#');
    updateHeadPointer();
}

void TMTape::updateHeadPointer() {
    setPointerToCharUnderHead(&tape[getHeadPosition()]);
}

void TMTape::setAlphabetPtr(std::shared_ptr<TMAlphabet> alphaSPtr) {
    alphabet = alphaSPtr;
}

void TMTape::doCmd(const char before, const char after, TMHeadMoveType headMove)
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
    tapeEditNotifier(getHeadPosition(), getHeadPosition());
}

void TMTape::moveHeadToThe(TMHeadMoveType direction) {
    if (direction == TMHeadMoveType::LEFT) moveHeadLeft();
    if (direction == TMHeadMoveType::RIGHT) moveHeadRight();
    updateHeadPointer();
    headEditNotifier();
}

void TMTape::checkIfBelongsToAlphabet(const char character) const throw (CharacterOutOfAlphabet) {
    std::shared_ptr<TMAlphabet> alpha (alphabet);
    if (!alpha->has(character)) throw CharacterOutOfAlphabet(character);
}

void TMTape::checkIfMatchWithCharOnTape(const char character) const throw (MismatchCommandAndElementUnderHead) {
    if(getCharUnderHead() != character) throw MismatchCommandAndElementUnderHead();
}

void TMTape::reset() {
    fillTheTapeWithHashes();
    setHeadPosition(tapeLength/2);
}

void TMTape::fillTheTapeWithHashes() {
    std::fill(tape.begin(), tape.end(), '#');
}

void TMTape::setNewTapeLength(const size_t len) {
    setTapeLength(len);
    updateTapeSize();
    fillTheTapeWithHashes();
    setHeadPosition(tapeLength/2);
}

void TMTape::updateTapeSize() {
    tape.resize(tapeLength, '#');
}

void TMTape::insertContentAt(const size_t pos, std::string& content) {
    auto from = tape.begin() + pos;
    auto numberOfElements = content.length();

    tape.erase(from, from + numberOfElements);
    tape.insert(from, content.begin(), content.end());

    tapeEditNotifier(pos, pos + numberOfElements);
}
