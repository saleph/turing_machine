#include "TMTape.h"

TMTape::TMTape(unsigned int len) : tapeLength(len), TMHead (len/2u) {
    initTape(len);
}

TMTape::TMTape(unsigned int len, unsigned int headPos) throw (ZeroLongTape) : tapeLength(len), TMHead(headPos) {
    if (len == 0)
        throw ZeroLongTape();
    initTape(len);
}

TMTape::~TMTape() {
    // dtor def
}

void TMTape::initTape(unsigned int len) {
    /*tape.insert(tape.begin(), len, '#');*/
}

void TMTape::doCmd (const char before, const char after, MoveType headMove)
    throw (MismatchCommandAndElementUnderHead) {
    ;
}
