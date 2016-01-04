#include "TMTape.h"

// without setting headPosition the head go to the middle of tape
TMTape::TMTape(unsigned int len) throw (ZeroLongTape) : TMHead (len/2u) {
    setTapeLength(len);
    initTape(len);
}

TMTape::TMTape(unsigned int len, unsigned int headPos) throw (ZeroLongTape, HeadOutOfTape) : TMHead(headPos) {
    setTapeLength(len);
    checkHeadPosition();
    initTape(len);
}

void TMTape::setTapeLength(unsigned int len) throw (ZeroLongTape) {
    checkTapeLength(len);
    tapeLength = len;
}

void TMTape::checkTapeLength(unsigned int len) const throw (ZeroLongTape) {
    if (len == 0u) throw ZeroLongTape();
}

void TMTape::checkHeadPosition() const throw (HeadOutOfTape) {
    if (TMHead::getHeadPosition() > tapeLength - 1) throw HeadOutOfTape();
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
}

void TMTape::doCmd (const char before, const char after, MoveType headMove)
    throw (MismatchCommandAndElementUnderHead) {
    // TODO
}
