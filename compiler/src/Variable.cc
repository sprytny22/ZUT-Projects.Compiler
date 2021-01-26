#include <algorithm>
#include "../headers/Variable.h"

Variable::Variable(LexType type, std::string value) {
    _type = type;
    _value = value;
}

std::string Variable::getValue() {
    return _value;
}

void Variable::setLexType(LexType type) {
    _type = type;
}

LexType Variable::getLexType() {
    return _type;
}

std::vector<std::string> Variable::unavailableNames;

std::string Variable::generateUniqueName() {
    int unique = 0;
    while(std::find(unavailableNames.begin(), unavailableNames.end(), std::to_string(++unique)) != unavailableNames.end()) 
    {}

    unavailableNames.push_back(std::to_string(unique));
    return std::to_string(unique);
}