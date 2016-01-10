#ifndef TMCOMMANDPARSER_H
#define TMCOMMANDPARSER_H

#include "TMCommand.h"
#include <string>
using std::string;


class TMCommandParser
{
    public:
        TMCommandParser();
        virtual ~TMCommandParser();

        TMCommand parseToCommand(string line);
    protected:
    private:
};

#endif // TMCOMMANDPARSER_H
