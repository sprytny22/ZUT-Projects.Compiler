#include <stack>
#include <map>
#include "Variable.h"

class Compiler { 
    
    private:
         std::stack<Variable*> *_stack;
         std::map<std::string, Variable*> *_symbols;

    public:
        Compiler();
        void pushOnStack(Variable*);   
        void createThree(std::string);
        void createSymbol(std::string, Variable*);
        Variable* topAndPop();

}; 