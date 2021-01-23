#include <stack>
#include "Variable.h"

enum LexType {
    Int,
    Double,
    Text
};

class Compiler { 
    
    private:
         std::stack<Variable*> *_stack;

    public:
        Compiler();
        void pushOnStack(Variable* var);   

}; 