#include <vector>
#include <string>
#include "Variable.h"

class Assembly { 
    
    private:
        std::vector<std::string> _assemblyHeaderLines;
        std::vector<std::string> _assemblyBodyLines;

    public:
        Assembly();
        void assignment(LexType, std::string, std::string);

        template< typename... Arguments >
        void lines(std::string, Arguments...);

}; 