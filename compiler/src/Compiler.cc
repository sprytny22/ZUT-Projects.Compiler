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

    Debug::info("Pushed Stack!");
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

    
    LexType leftType = LexType::None;
    LexType rightType = LexType::None;


    if (left->getLexType() == LexType::Text && _symbols->find(left->getValue()) != _symbols->end()) {
        leftType = _symbols->find(left->getValue())->second->getLexType();
    }
    else if (left->getLexType() == LexType::Text) {
        std::string errorMessage = "Undefined symbol found.";   //TODO: error mesaages
    }

    if (right->getLexType() == LexType::Text && _symbols->find(right->getValue()) != _symbols->end()) {
        rightType = _symbols->find(right->getValue())->second->getLexType();
    }
    else if (right->getLexType() == LexType::Text) {
        std::string errorMessage = "Undefined symbol found.";
    }

    if (leftType != rightType) {
        std::string errorMessage = "Type mismatch!";
    }

    _assembly->assignment(leftType, left->getValue(), "$t0");
    _assembly->assignment(rightType, right->getValue(), "$t1");
    

    //std::cout << std::string(result->getValue()) + std::string(" = ") + std::string(tmp->getValue()) + std::string(" ") + std::string(tmp2->getValue()) + std::string(" ") + std::string(op) << std::endl;
}

void Compiler::createSymbol(std::string name, Variable * variable) {
    _symbols->insert(std::make_pair(name, variable));
}

Variable* Compiler::topAndPop(){
    Variable* top = _stack->top();
    _stack->pop();

    return top;
}

