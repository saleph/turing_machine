#ifndef TMCOMMANDPARSER_H
#define TMCOMMANDPARSER_H

#include "TMCommand.h"
#include "TMExceptions.h"
#include <string>
#include <regex>


class TMCommandParser
{
    const size_t CMD_NAME_POS = 1; // because at 0 is the whole, matched line
    const size_t FROM_STATE_POS = 2;
    const size_t TO_STATE_POS = 3;
    const size_t MOVE_TYPE_POS = 4;
    const size_t NEXT_CMD_NAME_POS = 5;
    const std::regex CMD_PATTERN = std::regex(
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
        std::pair<std::string, TMCommand> parseToCommandWithItsName(const std::string& line, const int& location=-1)
                throw (InvalidCommandSyntax);
    private:
        std::smatch tokens;

        void getTokensFrom(const std::string&);
        void checkIfRegexMatched(const std::string& line) const throw (InvalidCommandSyntax);
        std::string getCommandName() const;
        TMCommand constructNewCommand(const int &location) const;
        char getFromState() const;
        char getFirstCharOf(const std::string&) const;
        char getToState() const;
        TMHeadMoveType getMoveType() const;
        TMHeadMoveType getHeadMoveTypeFromChar() const;
        char getMoveTypeFromToken() const;
        std::string getNextCommandName() const;
};

#endif // TMCOMMANDPARSER_H
