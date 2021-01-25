#include <vector>
#include <string>
#include "Variable.h"

class Assembly { 
    
    private:
        std::vector<std::string> *_assemblyHeaderLines;
        std::vector<std::string> *_assemblyBodyLines;

    public:
        Assembly();
        
        void generateOutputFile();
        void createAssigment(std::string, Variable*);
        void pushHeader(std::string);
        void pushBody(std::string);
}; 