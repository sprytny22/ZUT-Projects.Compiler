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

void Assembly::pushHeader(std::string lines) {
    _assemblyHeaderLines->push_back(lines);
}

void Assembly::pushBody(std::string lines) {
    _assemblyBodyLines->push_back(lines);
}

void Assembly::createAssigment(std::string variableName, Variable* variable) {

    std::stringstream ss;
    std::string type = variable->getLexType() == LexType::Double ? ".float " : ".word ";

    ss << variableName << ":" << " " << type << "0" << "\n";
    
    pushHeader(ss.str());

    ss.str("");

    ss << "li" << " $t0 " << ", " << variable->getValue() << "\n";
    ss << "sw" << " $t0 " << ", " << variableName << "\n";

    pushBody(ss.str());
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