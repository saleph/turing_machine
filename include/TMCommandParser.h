#ifndef TMCOMMANDPARSER_H
#define TMCOMMANDPARSER_H

#include "TMCommand.h"
#include "TMExceptions.h"
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <regex>
using std::string;
using std::pair;
using std::vector;
using std::array;
using std::size_t;
using std::regex;
using std::regex_match;


class TMCommandParser
{
    const size_t TOKENS_NUMBER = 5;
    const size_t CMD_NAME_POS = 0;
    const size_t FROM_STATE_POS = 1;
    const size_t TO_STATE_POS = 2;
    const size_t MOVE_TYPE_POS = 3;
    const size_t NEXT_CMD_NAME_POS = 4;
    const regex CMD_PATTERN = regex("^[^ ;/]+ [^ ;/]/[^ ;/];[RLrl] [^ ;/]+$");
    public:
        pair<string, TMCommand> parseToCommandWithItsName(const string& line) throw (InvalidCommand);
    private:
        vector<string> tokens;

        void checkIfMatchToCmdPattern(const string&) const throw (InvalidCommand);
        void splitToTokens(const string& line);
        void checkNumberOfTokens() const throw (InvalidCommand);
        string getCommandName() const;
        TMCommand constructNewCommand() const;
        char getFromState() const;
        char getToState() const;
        TMHeadMoveType getMoveType() const;
        TMHeadMoveType getHeadMoveTypeFromChar() const;
        char getMoveTypeToken() const;
        string getNextCommandName() const;
};

#endif // TMCOMMANDPARSER_H
