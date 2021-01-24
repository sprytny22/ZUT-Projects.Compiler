#include <vector>
#include <string>
#include "Variable.h"

class Assembly { 
    
    private:
        std::vector<std::string> _assemblyHeaderLines;
        std::vector<std::string> _assemblyBodyLines;

    public:
        std::string emptyLine = " ";

        Assembly();
        void assignmentHeader(LexType, std::string, std::string, std::string);
        void assignmentBody(LexType, std::string, std::string, std::string);
        void generateAssemblyOutput();

        std::string createLine(std::string, std::string, std::string, std::string);

        void textAssign(std::string, std::string, std::string);
        void intAssign(std::string, std::string, std::string);
        void doubleAssign(std::string, std::string, std::string);


}; 