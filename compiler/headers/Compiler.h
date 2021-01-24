#include <stack>
#include <map>
#include "Assembly.h"

class Compiler { 
    
    private:
        std::stack<Variable*> *_stack;
        std::map<std::string, Variable*> *_symbols;
        Assembly *_assembly;

    public:
        Compiler();
        void pushOnStack(Variable*);   
        void createThree(std::string);
        void createSymbol(std::string, Variable*);
        LexType findSymbolType(std::string);
        Variable* topAndPop();

        void textAssign(std::string);
        void intAssign(std::string);
        void doubleAssign(std::string);

}; 