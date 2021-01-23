#include "../headers/Assembly.h"

Assembly::Assembly() {}

void Assembly::assignment(LexType type, std::string value, std::string reg) {
    _assemblyBodyLines.push_back("test");
}

template< typename... Arguments >
void Assembly::lines(std::string value, Arguments... args) 
{
    
}