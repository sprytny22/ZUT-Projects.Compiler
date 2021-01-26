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
        Variable* findSymbol(std::string); 
        Variable* topAndPop();

        bool correctSymbol(Variable*);
        void simpleAssigmentInt(std::string);
        void simpleAssigmentDouble(std::string);
        void simpleAssigmentText(std::string);

}; 