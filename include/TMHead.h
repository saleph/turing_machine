#ifndef TMHEAD_H
#define TMHEAD_H
#include <stdexcept>
using std::invalid_argument;

class MismatchCommandAndElementUnderHead : public invalid_argument
{
    public:
        MismatchCommandAndElementUnderHead() : invalid_argument ( "Mismatch of command and the element under head!" );
}


class TMHead
{
    public:
        TMHead() = default;
        TMHead(unsigned int pos) { setPosition(pos); };
        virtual ~TMHead() = default;
        unsigned int getPosition() { return position; }
        void setPosition(unsigned int val) { position = val; }

        enum MoveType { LEFT, RIGHT };
        void proceed (const char before, const char after, MoveType headMove) throw (MismatchCommandAndElementUnderHead);
    private:
        unsigned int position;
        char *signUnderHead;
};

#endif // TMHEAD_H
