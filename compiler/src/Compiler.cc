#include "../headers/Compiler.h"
#include "../headers/Debug.h"

Compiler::Compiler() {
    _stack = new std::stack<Variable*>();
}

void Compiler::pushOnStack(Variable* variable) {
    _stack->push(variable);
    Debug::info();
}