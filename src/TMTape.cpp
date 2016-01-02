#include "TMTape.h"

TMTape::TMTape(unsigned int len) throw (ZeroLongTape) : TMHead (len/2u) {
    setTapeLength(len);
    initTape(len);
}

TMTape::TMTape(unsigned int len, unsigned int headPos) throw (ZeroLongTape) : TMHead(headPos) {
    setTapeLength(len);
    initTape(len);
}

TMTape::~TMTape() {
    // dtor def
}

void TMTape::setTapeLength(unsigned int len) {
    if (len == 0u) throw ZeroLongTape();
    tapeLength = len;
}

void TMTape::initTape(unsigned int len) {
    /*tape.insert(tape.begin(), len, '#');*/
}

void TMTape::doCmd (const char before, const char after, MoveType headMove)
    throw (MismatchCommandAndElementUnderHead) {
    ;
}
