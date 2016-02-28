#include "TMAPI.h"

void TMAPI::insertGraph(const std::initializer_list<std::string>& graphAsList) {
    graphAsText = graphAsList;
}

void TMAPI::insertGraph(const std::vector<std::__cxx11::string> &graphAsVector) {
    graphAsText = std::move(graphAsVector);
}

const std::vector<std::string>& TMAPI::getGraphAsVector() const {
    return graphAsText;
}

int TMAPI::getLocationOfLastCommand() const {
    return turingMachine.getLocationOfLastCommand();
}

std::pair<size_t, char> TMAPI::getPositionAndCharacterRecentlyChangedByStep() const {
    return { turingMachine.getLastTapeChangePosition(), turingMachine.getLastChangedCharacter() };
}

void TMAPI::insertAlphabet(const std::string& alphabet) {
    *turingMachine.alphabet = alphabet;
}

std::string TMAPI::getAlphabet() const {
    return turingMachine.alphabet->getAlphabet();
}

void TMAPI::setHeadPosition(const size_t& pos) {
    tape->setHeadPosition(pos);
}

void TMAPI::compileInsertedGraph() {
    turingMachine.graph->clear();
    for (size_t i = 0; i < graphAsText.size(); i++)
        turingMachine.addToGraph(graphAsText[i], i);
    turingMachine.backTheGraphToTheBeginning();
}

void TMAPI::doSingleStep() {
    turingMachine.doStep();
}

void TMAPI::executeGraphInstantly() {
    turingMachine.executeGraphInstantly();
}

void TMAPI::turnBackGraphToStartPosition() {
    turingMachine.backTheGraphToTheBeginning();
}

void TMAPI::makeCurrentCmdACommandWithLocation(int loc) {
    turingMachine.makeCurrentCmdACommandWith(loc);
}

void TMAPI::getDataFromFile(const std::string& filename) {
    initializeFileParser(filename);
    fileParser->parseToStateWatcher();
    checkIfDataWasInserted();
    getDataFromStateWatcher();
}

void TMAPI::initializeFileParser(const std::string& filename) {
    fileParser = std::make_unique<TMFileParser>(filename);
}

void TMAPI::checkIfDataWasInserted() const throw (DataFromFileDoesntInserted) {
    if (!TMStateWatcher::prepared())
        throw DataFromFileDoesntInserted();
}

void TMAPI::getDataFromStateWatcher() {
    setAlphabetWithValueFromStateWatcher();
    setTapeLengthWithValueFromStateWatcher();
    setHeadPositionWithValueFromStateWatcher();
    setTapeContentWithValueFromStateWatcher();
    setGraphAsTextWithValueFromStateWatcher();
}

void TMAPI::setAlphabetWithValueFromStateWatcher() {
    insertAlphabet(**TMStateWatcher::alphabetAsString);
}

void TMAPI::setTapeLengthWithValueFromStateWatcher() {
    tape->setNewTapeLength(**TMStateWatcher::tapeLength);
}

void TMAPI::setHeadPositionWithValueFromStateWatcher() {
    setHeadPosition(**TMStateWatcher::headPosition);
}

void TMAPI::setTapeContentWithValueFromStateWatcher() {
    tape->insertContentAt(**TMStateWatcher::tapeContentPosition, **TMStateWatcher::tapeContent);
}

void TMAPI::setGraphAsTextWithValueFromStateWatcher() {
    graphAsText = std::move(**TMStateWatcher::graphAsText);
}
