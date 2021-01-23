#include <string>
#include <vector>

enum LexType {
    None,
    Int,
    Double,
    Text
};

class Variable { 
    LexType _type;
    std::string _value;

    public:   

      Variable(LexType, std::string);
      std::string getValue();
      LexType getLexType();

      static std::vector<std::string> unavailableNames;
      static std::string generateUniqueName();
}; 