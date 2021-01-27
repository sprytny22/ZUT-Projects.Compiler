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

/*
result= c 9 ∗
result= b result +
result= a result =
*/

void Compiler::createThree(std::string op) {

    if (_stack->size() < 1) {
        return;
    }

    Variable* right = topAndPop();
    Variable* left = topAndPop();

    LexType rightType = right->getLexType();
    LexType leftType = left->getLexType();

    if (rightType == LexType::Text) {
        auto symbol = findSymbol(right->getValue());
        if (symbol == nullptr) {
            Debug::info("Symbol not exists right! (createThree)");
            return;
        }
        else {
            right->setLexType(symbol->getLexType());
        }

    if (isTextValue(rightValue)) {
        auto symbol = findSymbol(left->getValue());
        if (symbol == nullptr) {
            Debug::info("Symbol not exists left! (createThree)");
            return;
        }

        _assembly->lw("$t1", left->getValue());
    }
    else {
        _assembly->li("$t1", left->getValue());
    }



    std::string unique = Variable::generateUniqueName();
    Variable* result = new Variable(LexType::Text, unique);

    _assembly->action(op, "$t0", "$t0", "$t1");
    _assembly->sw("$t0", result->getValue());

    createSymbol(unique, result);
    _assembly->data(result->getValue(),);
}

void Compiler::createSymbol(std::string name, Variable* variable) {
    if (findSymbol(name) != nullptr) {
        Debug::info("Variable is already defined!");
        return;
    }

    _symbols->insert(std::make_pair(name, variable));
}

void Compiler::simpleAssigmentInt(std::string variableName) {
    Variable* top = topAndPop();
    LexType type = top->getLexType();

    if (type == LexType::Double) {
        Debug::info("Cant assigne double to int!");
    }

    if (type == LexType::Text) {
        top->setLexType(LexType::Int);

        if (!correctSymbol(top)) {
            Debug::info("symbol not exists! (simpleAssigmentInt)");
            return;
        }
    }

    createSymbol(variableName, top);
    _assembly->createAssigment(variableName, top);
}

void Compiler::simpleAssigmentDouble(std::string variableName) {
    Variable* top = topAndPop();
    LexType type = top->getLexType();

    if (type == LexType::Int) {
        top->setLexType(LexType::Double); //convert int to double
    }

    if (type == LexType::Text) {
        top->setLexType(LexType::Double);

        if (!correctSymbol(top)) {
            Debug::info("symbol not exists! (simpleAssigmentDouble)");
            return;
        }
    }

    createSymbol(variableName, top);
    _assembly->createAssigment(variableName, top);
}

void Compiler::simpleAssigmentText(std::string variableName) {
    Variable* top = topAndPop();

    if (!correctSymbol(top)) {
        Debug::info("symbol not declarated!");
        return;
    }

    _assembly->createAssigment(variableName, top);
}

bool Compiler::correctSymbol(Variable* variable) {
    LexType type;
    std::string value = variable->getValue();
    Variable* symbol = nullptr;

    if ((symbol = findSymbol(value)) == nullptr) {
        Debug::info("symbol not exists!");
        return false;
    }

    type = symbol->getLexType();// TODO: type int -> double, double -> int is CORRECT!
    if (type != variable->getLexType()) {
        Debug::info("symbol not match!");
        return false;
    }

    return true;
} 

Variable* Compiler::findSymbol(std::string value) {
    Variable* type = nullptr;
    auto found = _symbols->find(value);
    
    if (found != _symbols->end()) {
        type = found->second;
    }

    return type;
}

LexType Compiler::findSymbolType(std::string value) {
    return findSymbol(value)->getLexType();
}

Variable* Compiler::topAndPop(){
    Variable* top = _stack->top();
    _stack->pop();

    return top;
}