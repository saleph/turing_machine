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


class TMCommandParser
{
    const size_t CMD_NAME_POS = 1; // because at 0 is the whole, matched line
    const size_t FROM_STATE_POS = 2;
    const size_t TO_STATE_POS = 3;
    const size_t MOVE_TYPE_POS = 4;
    const size_t NEXT_CMD_NAME_POS = 5;
    const regex CMD_PATTERN = regex(
        "^"           // start of command
        "\\s*"        // preceding spaces
        "([^ ;\\/]+)" // name of the command
        "\\s+"        // space(s) after command
        "([^ ;\\/])"  // one character (current state on tape)
        "/"           // separator between current & after states
        "([^ ;\\/])"  // one character (which will repace current)
        ";"           // separator between current and new chars & head move type
        "([RLrl])"    // move type (R/L or r/l)
        "\\s+"        // space(s) after "to head" commands
        "([^ ;\\/]+)" // name of next command
        "\\s*"        // maybe ending spaces
        "$"           // end of command
        );
    public:
        pair<string, TMCommand> parseToCommandWithItsName(const string& line) throw (InvalidCommandSyntax);
    private:
        std::smatch tokens;

        void getTokensFrom(const string&);
        void checkIfRegexMatched() const throw (InvalidCommandSyntax);
        string getCommandName() const;
        TMCommand constructNewCommand() const;
        char getFromState() const;
        char getFirstCharOf(const string&) const;
        char getToState() const;
        TMHeadMoveType getMoveType() const;
        TMHeadMoveType getHeadMoveTypeFromChar() const;
        char getMoveTypeFromToken() const;
        string getNextCommandName() const;
};

#endif // TMCOMMANDPARSER_H
