#include <stack>
#include <map>
#include "Assembly.h"

class Compiler { 
    
    private:
        std::stack<Variable*> *_stack;
        std::stack<std::string> *_conditionStack;
        std::stack<std::string> *_labelStack;
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

        bool isTextValue(std::string);

        void assigmentAssembly(std::string, Variable*);

        bool correctSymbol(Variable*);
        void simpleAssigmentInt(std::string);
        void simpleAssigmentDouble(std::string);
        void simpleAssigmentText(std::string);

        void pushConditionOnStack(std::string);

        void ifStart();
        void ifEnd();

        std::string topAndPopCondition();

        void PushLabelOnStack(std::string);
        void pushOnStackText(Variable*);

        std::string topAndPopLabel();

        void print();
        void printext(std::string);

        void declareInt(std::string);
        void declareDouble(std::string);

        void read();

}; 