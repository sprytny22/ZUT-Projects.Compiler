#include <sstream>
#include "../headers/Assembly.h"

Assembly::Assembly() {}

void Assembly::assignmentHeader(LexType type, std::string value, std::string reg, std::string op) {

}

void Assembly::assignmentBody(LexType type, std::string value, std::string reg, std::string op) {
    auto line1 = createLine("li ", reg, ", ", value);
    auto line2 = createLine("lw ", reg, ", ", value);
    auto line3 = createLine("add ",reg, ", ", value);
    auto line4 = createLine("sw ", reg, ", ", value);

    _assemblyBodyLines.push_back(line1);
    _assemblyBodyLines.push_back(line2);
    _assemblyBodyLines.push_back(line3);
    _assemblyBodyLines.push_back(line4);
}

std::string Assembly::createLine(std::string command, std::string value, std::string reg, std::string op)
{
   std::stringstream ss;
   ss << command << reg << ", " << value << "\n";

   return ss.str();
}

void Assembly::textAssign(std::string variableName, std::string value, std::string reg = "$t0") {

    //li $t0, 10
    //sw $t0, a
    _assemblyBodyLines.push_back(createLine("li", reg, ",", value));
    _assemblyBodyLines.push_back(createLine("sw", reg, ",", variableName));
    _assemblyBodyLines.push_back(emptyLine);

}

void Assembly::intAssign(std::string variableName, std::string value, std::string reg = "$t0") {

    //li $t0, 10
    //sw $t0, a
    _assemblyBodyLines.push_back(createLine("li", reg, ",", value));
    _assemblyBodyLines.push_back(createLine("sw", reg, ",", variableName));
    _assemblyBodyLines.push_back(emptyLine);

}

void Assembly::doubleAssign(std::string variableName, std::string value, std::string reg = "$t0") {

    //li $t0, 10
    //sw $t0, a
    _assemblyBodyLines.push_back(createLine("li", reg, ",", value));
    _assemblyBodyLines.push_back(createLine("sw", reg, ",", variableName));
    _assemblyBodyLines.push_back(emptyLine);

}