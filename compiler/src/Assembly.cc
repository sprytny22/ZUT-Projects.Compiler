#include <sstream>
#include <string>
#include <cstdio>
#include "../headers/Assembly.h"
#include "../headers/Debug.h"

Assembly::Assembly() {
    _assemblyHeaderLines = new std::vector<std::string>();
    _assemblyBodyLines = new std::vector<std::string>();

    _assemblyHeaderLines->push_back(".data\n");
    _assemblyBodyLines->push_back(".text\n");
}

void Assembly::pushData(std::string lines) {
    _assemblyHeaderLines->push_back(lines);
}

void Assembly::pushText(std::string lines) {
    _assemblyBodyLines->push_back(lines);
}

void Assembly::lw(std::string reg, std::string value) {
    std::stringstream ss;

    ss << "lw " << reg << ", " << value << "\n";
    pushText(ss.str());
}

void Assembly::sw(std::string reg, std::string value) {
    std::stringstream ss;

    ss << "sw " << reg << ", " << value << "\n";
    pushText(ss.str());
}

void Assembly::li(std::string reg, std::string value) {
    std::stringstream ss;

    ss << "li " << reg << ", " << value << "\n";
    pushText(ss.str());
}

void Assembly::action(std::string op, std::string assignReg, std::string reg0, std::string reg1) {
    std::stringstream ss;

    ss << op << " " << assignReg << ", " << reg0 << " " << reg1 << "\n";
    pushText(ss.str());
}

void Assembly::data(std::string variableName, LexType lextype, std::string value = "0") {
    std::stringstream ss;

    std::string type = lextype == LexType::Double ? ".float" : ".word";

    ss << variableName << ":" << " " << type << " " << value << "\n";
    pushText(ss.str());
}

void Assembly::createAssigment(std::string variableName, Variable* variable) {

    data(variableName, variable->getLexType());
    li("$t0", variable->getValue());
    sw("$t0", variableName);

    generateOutputFile();
}

void Assembly::generateOutputFile() {

    FILE * asmFile;
    remove("output.asm");

    asmFile = fopen ("output.asm","a");

    for ( auto i = _assemblyHeaderLines->begin(); i != _assemblyHeaderLines->end(); i++ ) {
        fprintf(asmFile, i->c_str());
    }
    for ( auto i = _assemblyBodyLines->begin(); i != _assemblyBodyLines->end(); i++ ) {
        fprintf(asmFile, i->c_str());
    }

    fclose (asmFile);
}