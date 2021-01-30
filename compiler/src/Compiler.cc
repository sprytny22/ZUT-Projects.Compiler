#include <iostream>
#include <sstream>
#include <string>
#include "../headers/Compiler.h"
#include "../headers/Debug.h"

Compiler::Compiler() {
    _stack = new std::stack<Variable*>();
    _conditionStack = new std::stack<std::string>();
    _labelStack = new std::stack<std::string>();
    _symbols = new std::map<std::string, Variable*>();
    _assembly = new Assembly();
}

void Compiler::pushOnStack(Variable* variable) {
    _stack->push(variable);
}

void Compiler::pushOnStackText(Variable* variable) {
    auto var = findSymbol(variable->getValue());

    if (var == nullptr) {
        Debug::info("ERROR PUSH");
        return;
    }

    variable->setLexType(var->getLexType());

    _stack->push(variable);
}

void Compiler::createThree(std::string op) {

    if (_stack->size() < 1) {
        return;
    }

    LexType resultType = LexType::Int;

    Variable* right = topAndPop();
    Variable* left = topAndPop();

    std::string rightValue = right->getValue();
    std::string leftValue = left->getValue();

    if (isTextValue(rightValue)) {
        auto symbol = findSymbol(right->getValue());
        if (symbol == nullptr) {
            Debug::info("Symbol not exists right! (createThree)");
            return;
        }

        _assembly->lw("$t0", right->getValue());
    }
    else {
        _assembly->li("$t0", right->getValue());
    }

    if (isTextValue(leftValue)) {
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

    if (right->getLexType() == LexType::Double || left->getLexType() == LexType::Double) {
        resultType = LexType::Double;
    }

    std::string unique = Variable::generateUniqueName();
    Variable* result = new Variable(resultType, unique);

    pushOnStack(result);
    createSymbol(unique, result);

    if (result->getLexType() == LexType::Double){
        _assembly->actiondots(op, "$f0", "$f0", "$f1");
        _assembly->sdots("$t0", result->getValue());
        _assembly->data(result->getValue(),result->getLexType());
        return;
    }

    _assembly->action(op, "$t0", "$t0", "$t1");
    _assembly->sw("$t0", result->getValue());
    _assembly->data(result->getValue(),result->getLexType());
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
    std::string value = top->getValue();

    if (type == LexType::Double) {
        Debug::info("Cant assigne double to int!");
        return;
    }

    if (isTextValue(value)) {
        if (!correctSymbol(top)) {
            Debug::info("symbol not exists! (simpleAssigmentInt)");
            return;
        }
    }

    createSymbol(variableName, top);
    assigmentAssembly(variableName, top);
}

void Compiler::simpleAssigmentDouble(std::string variableName) {
    Variable* top = topAndPop();
    LexType type = top->getLexType();
    std::string value = top->getValue();

    if (isTextValue(value)) {
        top->setLexType(LexType::Double);

        if (!correctSymbol(top)) {
            Debug::info("symbol not exists! (simpleAssigmentDouble)");
            return;
        }
    }

    top->setLexType(LexType::Double);

    createSymbol(variableName, top);
    assigmentAssembly(variableName, top);
}

void Compiler::simpleAssigmentText(std::string variableName) {
    Variable* top = topAndPop();

    if (!correctSymbol(top)) {
        Debug::info("symbol not declarated!");
        return;
    }

    assigmentAssembly(variableName, top);
}

bool Compiler::correctSymbol(Variable* variable) {
    LexType type;
    std::string value = variable->getValue();
    Variable* symbol = nullptr;

    if ((symbol = findSymbol(value)) == nullptr) {
        Debug::info("symbol not exists!");
        return false;
    }

    // type = symbol->getLexType();// TODO: type int -> double, double -> int is CORRECT!
    // if (type != variable->getLexType()) {
    //     Debug::info("symbol not match!");
    //     return false;
    // }

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

bool Compiler::isTextValue(std::string value) {
  std::stringstream ss(value); 
  int number;
  float fnumber;

  if((ss >> number).fail() && (ss >> fnumber).fail()) { 
      return true;
  }

  return false;
}

void Compiler::assigmentAssembly(std::string variableName, Variable* top) {

    if (top->getLexType() == LexType::Double) {
        std::string unique = Variable::generateUniqueName();
        !isTextValue(top->getValue()) ? _assembly->data(unique, top->getLexType(), top->getValue()) : _assembly->data(unique, top->getLexType());
        _assembly->data(variableName, top->getLexType());
        
        _assembly->ldots("$f0", unique);
        _assembly->sdots("$f0", variableName);
        _assembly->generateOutputFile();
        return;
    }

    isTextValue(top->getValue()) ? _assembly->lw("$t0", top->getValue()) : _assembly->li("$t0", top->getValue());

    // // if (!findSymbol(top->getValue())){
    //      _assembly->data(variableName, top->getLexType());    
     
    //      _assembly->data(variableName, top->getLexType());    
    // // }
    _assembly->data(variableName, top->getLexType());    
    _assembly->sw("$t0", variableName);
    _assembly->generateOutputFile();
}

void Compiler::pushConditionOnStack(std::string condition) {
    _conditionStack->push(condition);
}

std::string Compiler::topAndPopCondition() {
    std::string top = _conditionStack->top();
    _conditionStack->pop();

    return top;
}

void Compiler::ifStart() {
    Variable* right = topAndPop();
    Variable* left = topAndPop();
    std::string rightValue = right->getValue();
    std::string leftValue = left->getValue();

    std::string condition = topAndPopCondition();

    std::string label = Variable::generateUniqueLabel();
    PushLabelOnStack(label);

    if (isTextValue(rightValue)) {
        auto symbol = findSymbol(right->getValue());
        if (symbol == nullptr) {
            Debug::info("Symbol not exists right! (createThree)");
            return;
        }
        _assembly->lw("$t2", left->getValue());
    }
    else {
        _assembly->li("$t2", left->getValue());
    }
    
    if (isTextValue(rightValue)) {
        auto symbol = findSymbol(right->getValue());
        if (symbol == nullptr) {
            Debug::info("Symbol not exists right! (createThree)");
            return;
        }
        _assembly->lw("$t3", left->getValue());
    }
    else {
        _assembly->li("$t3", left->getValue());
    }

    _assembly->condition(condition, "$t2", "$t3", label);
}

void Compiler::ifEnd() {
    std::string label = topAndPopLabel();

    _assembly->label(label);
    _assembly->generateOutputFile();
}

void Compiler::PushLabelOnStack(std::string label) {
    _labelStack->push(label);
}

std::string Compiler::topAndPopLabel() {
    std::string top = _labelStack->top();
    _labelStack->pop();

    return top;
}

void Compiler::print() {
    Variable* top = topAndPop();
    std::string value = top->getValue();

    if (!correctSymbol(top)) {
        Debug::info("print error");
        return;
    }

    LexType type = findSymbolType(top->getValue());

    if (type == LexType::Int) {
        _assembly->li("$v0", "1");
        _assembly->lw("$a0", value);
    }
    else {
        _assembly->li("$v0", "2");
        _assembly->ldots("$f12", value);
    }

    _assembly->syscall();
    _assembly->generateOutputFile();
}

void Compiler::printext(std::string text) {
    std::string unique = Variable::generateUniqueName();

    _assembly->data(unique, text);
    _assembly->li("$v0", "4");
    _assembly->la("$a0", unique);
    _assembly->syscall();

    _assembly->generateOutputFile();
}

void Compiler::read() {
    Variable* top = topAndPop();
    LexType type = top->getLexType();
    std::string value = top->getValue();

    if (!correctSymbol(top)) {
        Debug::info("read error");
        return;
    }

    if (type == LexType::Int) {
        _assembly->li("$v0", "5");
        _assembly->syscall();
        _assembly->sw("$v0", value);
    }
    else {
        _assembly->li("$v0", "6");
        _assembly->syscall();
        _assembly->sdots("$f0", value);
    }

    _assembly->generateOutputFile();
}

void Compiler::declareInt(std::string value) {
    Variable* var = new Variable(LexType::Int, value);

    if(findSymbol(value)) {
        Debug::info("ERROR: Taki symbol juz instenieje");
        return;
    }

    createSymbol(value, var);
    _assembly->data(value, var->getLexType());
}

void Compiler::declareDouble(std::string value) {
    Variable* var = new Variable(LexType::Double, value);

    if(findSymbol(value)) {
        Debug::info("ERROR: Taki symbol juz instenieje");
        return;
    }

    createSymbol(value, var);
    _assembly->data(value, var->getLexType());
}