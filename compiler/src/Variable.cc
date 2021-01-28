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
std::vector<std::string> Variable::unavailableLabels;

std::string Variable::generateUniqueName() {
    int unique = 0;
    std::string defaultVariableName = "result";
    
    while(std::find(unavailableNames.begin(), unavailableNames.end(), std::to_string(++unique)) != unavailableNames.end()) 
    {}

    unavailableNames.push_back(std::to_string(unique));
    return std::string(defaultVariableName) + std::to_string(unique);
}

std::string Variable::generateUniqueLabel() {
    int unique = 0;
    std::string defaultLabelName = "LABEL";
    
    while(std::find(unavailableLabels.begin(), unavailableLabels.end(), std::to_string(++unique)) != unavailableLabels.end()) 
    {}

    unavailableLabels.push_back(std::to_string(unique));
    return std::string(defaultLabelName) + std::to_string(unique);
}