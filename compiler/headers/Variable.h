#include <string>
#include <vector>

enum LexType {
    Int,
    Double
};

class Variable { 
    LexType _type;
    std::string _value;

    public:   

      Variable(LexType, std::string);
      std::string getValue();

      void setLexType(LexType);
      LexType getLexType();

      static std::vector<std::string> unavailableNames;
      static std::string generateUniqueName();
}; 