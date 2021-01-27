#include <vector>
#include <string>
#include "Variable.h"

class Assembly { 
    
    private:
        std::vector<std::string> *_assemblyHeaderLines;
        std::vector<std::string> *_assemblyBodyLines;

    public:
        Assembly();

        void lw(std::string, std::string);
        void sw(std::string, std::string);
        void li(std::string, std::string);

        void data(std::string, LexType, std::string = "0");
        void action(std::string, std::string, std::string, std::string);
        
        void generateOutputFile();

        void pushData(std::string);
        void pushText(std::string);
}; 