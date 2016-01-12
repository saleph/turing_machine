#include "TMCommandParser.h"

pair<string, TMCommand> TMCommandParser::parseToCommandWithItsName(const string& line) throw (InvalidCommandSyntax) {
    getTokensFrom(line);
    checkIfRegexMatched();
    return {getCommandName(), constructNewCommand()};
}

void TMCommandParser::getTokensFrom(const string& str) {
    std::regex_match(str, tokens, CMD_PATTERN);
}

void TMCommandParser::checkIfRegexMatched() const throw (InvalidCommandSyntax) {
    if (!tokens.size()) throw InvalidCommandSyntax();
}

string TMCommandParser::getCommandName() const {
    return tokens[CMD_NAME_POS];
}

TMCommand TMCommandParser::constructNewCommand() const {
    char fromState = getFromState();
    char toState = getToState();
    TMHeadMoveType moveType = getMoveType();
    string nextCommandName = getNextCommandName();
    return TMCommand(fromState, toState, moveType, nextCommandName);
}

char TMCommandParser::getFromState() const {
    return getFirstCharOf(tokens[FROM_STATE_POS]);
}

char TMCommandParser::getFirstCharOf(const string& str) const {
    return str[0];
}

char TMCommandParser::getToState() const {
    return getFirstCharOf(tokens[TO_STATE_POS]);
}

TMHeadMoveType TMCommandParser::TMCommandParser::getMoveType() const {
    return getHeadMoveTypeFromChar();
}

TMHeadMoveType TMCommandParser::getHeadMoveTypeFromChar() const {
    char moveTypeAsChar = getMoveTypeFromToken();
    if (moveTypeAsChar == 'R') return TMHeadMoveType::RIGHT; // validated in parse func
    return TMHeadMoveType::LEFT;
}

char TMCommandParser::getMoveTypeFromToken() const {
    return getFirstCharOf(tokens[MOVE_TYPE_POS]);
}

string TMCommandParser::getNextCommandName() const {
    return tokens[NEXT_CMD_NAME_POS];
}
