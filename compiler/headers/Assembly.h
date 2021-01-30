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
        void la(std::string, std::string);
        void ldots(std::string, std::string);
        void sdots(std::string, std::string);

        void data(std::string, LexType, std::string = "0");
        void data(std::string, std::string);
        void action(std::string, std::string, std::string, std::string);
        void actiondots(std::string, std::string, std::string, std::string);
        void condition(std::string, std::string, std::string, std::string);
        void label(std::string);

        void syscall();
        
        void generateOutputFile();

        void pushData(std::string);
        void pushText(std::string);
}; 