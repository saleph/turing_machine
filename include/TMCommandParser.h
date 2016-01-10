#ifndef TMCOMMANDPARSER_H
#define TMCOMMANDPARSER_H

#include "TMCommand.h"
#include "TMExceptions.h"
#include <string>
#include <vector>
#include <array>
#include <cstring>
using std::string;
using std::pair;
using std::vector;
using std::array;
using std::size_t;


class TMCommandParser
{
    const size_t TOKENS_NUMBER = 5;
    const size_t CMD_NAME_POS = 0;
    const size_t FROM_STATE_POS = 1;
    const size_t TO_STATE_POS = 2;
    const size_t MOVE_TYPE_POS = 3;
    const size_t NEXT_CMD_NAME_POS = 4;
    public:
        pair<string, TMCommand> parseToCommandWithItsName(const string& line) throw (InvalidCommand, InvalidHeadMoveType);
    private:
        vector<string> tokens;

        void splitToTokens(const string& line);
        void checkNumberOfTokens() const throw (InvalidCommand);
        void checkIfSingleCharTokensAreSingle() const throw (InvalidCommand);
        void checkIfFromStateIsSingle() const throw (InvalidCommand);
        void checkIfToStateIsSingle() const throw (InvalidCommand);
        void checkIfMoveTypeIsSingle() const throw (InvalidCommand);
        void checkIfMoveTypeIsRorL() const throw (InvalidHeadMoveType);
        string getCommandName() const;
        TMCommand&& constructNewCommand() const;
        char getFromState() const;
        char getToState() const;
        TMHeadMoveType getMoveType() const;
        TMHeadMoveType getHeadMoveTypeFromChar() const;
        char getMoveTypeToken() const;
        string getNextCommandName() const;
};

#endif // TMCOMMANDPARSER_H
