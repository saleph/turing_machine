#include "TMCommandParser.h"

pair<string, TMCommand> TMCommandParser::parseToCommandWithItsName(const string& line) throw (InvalidCommandSyntax) {
    checkIfMatchToCmdPattern(line);
    splitToTokens(line);
    checkNumberOfTokens();
    //TODO: IF CMD ALREADY EXIST
    return {getCommandName(), constructNewCommand()};
}

void TMCommandParser::checkIfMatchToCmdPattern(const string& str) const throw (InvalidCommandSyntax) {
    if (!std::regex_match(str, CMD_PATTERN)) throw InvalidCommandSyntax();
}

static char* makeCopyOf(const string& str);

void TMCommandParser::splitToTokens(const string& line) {
    const char *delimeters = " /;";
    char *lineCopy = makeCopyOf(line);
    char *token = strtok(lineCopy, delimeters);
    while (token) {
        tokens.emplace_back(token);
        token = strtok(NULL, delimeters);
    }
}

char* makeCopyOf(const string& str) {
    char *strCopy = new char[str.length()];
    strcpy(strCopy, str.c_str());
    return strCopy;
}

void TMCommandParser::checkNumberOfTokens() const throw (InvalidCommandSyntax) {
    if (tokens.size() != TOKENS_NUMBER) throw InvalidCommandSyntax();
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
    return tokens[FROM_STATE_POS][0];
}

char TMCommandParser::getToState() const {
    return tokens[TO_STATE_POS][0];
}

TMHeadMoveType TMCommandParser::TMCommandParser::getMoveType() const {
    return getHeadMoveTypeFromChar();
}

TMHeadMoveType TMCommandParser::getHeadMoveTypeFromChar() const {
    char moveTypeAsChar = getMoveTypeToken();
    if (moveTypeAsChar == 'R') return TMHeadMoveType::RIGHT; // validated in parse func
    return TMHeadMoveType::LEFT;
}

char TMCommandParser::getMoveTypeToken() const {
    return tokens[MOVE_TYPE_POS][0];
}

string TMCommandParser::getNextCommandName() const {
    return tokens[NEXT_CMD_NAME_POS];
}
