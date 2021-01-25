#include <iostream>
#include <string>
#include "../headers/Compiler.h"
#include "../headers/Debug.h"

Compiler::Compiler() {
    _stack = new std::stack<Variable*>();
    _symbols = new std::map<std::string, Variable*>();
    _assembly = new Assembly();
}

void Compiler::pushOnStack(Variable* variable) {
    _stack->push(variable);
}

void Compiler::createThree(std::string op) {

    if (_stack->size() < 1) {
        return;
    }

    Variable* left = topAndPop();
    Variable* right = topAndPop();

    std::string unique = Variable::generateUniqueName();
    Variable* result = new Variable(LexType::Text, unique);

    pushOnStack(result);
    createSymbol(unique, result);

    
    LexType leftType = left->getLexType();
    LexType rightType = right->getLexType();


    if (leftType == LexType::Text) {
        leftType = findSymbolType(left->getValue());
    }

    if (leftType == LexType::Text) { 
        leftType = findSymbolType(right->getValue());
    }

    if (leftType == LexType::None || rightType == LexType::None || rightType != leftType) {
        Debug::info("Type != type");
        return;
    }

    Debug::lexToString("left: " ,leftType);
    Debug::lexToString("right: " ,rightType);

    LexType currentType = leftType;

    //Debug::info(_assembly->lines("jeden")); 

    // _assembly->assignmentBody(currentType, left->getValue(), "$t0", op);
    // _assembly->assignmentBody(currentType, right->getValue(), "$t1", op);

    // _assembly->generateAssemblyOutput();
    

    //std::cout << std::string(result->getValue()) + std::string(" = ") + std::string(tmp->getValue()) + std::string(" ") + std::string(tmp2->getValue()) + std::string(" ") + std::string(op) << std::endl;
}

void Compiler::createSymbol(std::string name, Variable * variable) {
    _symbols->insert(std::make_pair(name, variable));
}

void Compiler::simpleAssigment(std::string variableName) {
    Variable* top = topAndPop();

    Debug::info("ok!");

    createSymbol(variableName, top);

    _assembly->createAssigment(variableName, top);

}

LexType Compiler::findSymbolType(std::string value) {

    LexType type = LexType::Text;
    auto found = _symbols->find(value);
    
    if (found != _symbols->end()) {
        type = found->second->getLexType();
    }

    return type;
}

Variable* Compiler::topAndPop(){
    Variable* top = _stack->top();
    _stack->pop();

    return top;
}

void Compiler::createOutput() {
    _assembly->generateOutputFile();
}