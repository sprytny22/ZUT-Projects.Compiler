#include <iostream>
#include "../headers/Variable.h"
#include "../headers/Debug.h"

void Debug::info(std::string message) {
    std::cout << std::string("DEBUG::INFO: ") + std::string(message) + std::string(" \n") << std::endl;
}

void Debug::lexToString(std::string message, int lextype) {

    switch(lextype) {
        case LexType::Int:
            std::cout << message << std::string("LexType::Int") << std::endl;
            break;
        case LexType::Double:
            std::cout << message << std::string("LexType::Double") << std::endl;
            break;
        case LexType::Text:
            std::cout << message << std::string("LexType::Text") << std::endl;
            break;
        case LexType::None:
            std::cout << message << std::string("LexType::None") << std::endl;
            break;
        default:
            std::cout << message << std::string("Type debug Critical Error!") << std::endl;
            break;
    }
}