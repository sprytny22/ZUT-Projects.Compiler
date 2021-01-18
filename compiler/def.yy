%{
  #include <iostream>
  #include <stdbool.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string>
  #include <vector>
  #include <stack>
  #include <map>

  extern "C" int yylex();
  extern "C" int yyerror(const char *msg, ...);

	#define INFILE_ERROR 1
	#define OUTFILE_ERROR 2

  extern FILE *yyin;
  extern FILE *yyout;

  enum Type {
    Text,
    Integer,
    Double,
  };

  class Variable {
    Type type;
    String value;
    public:
      Variable(Type type, String value) {
        this->type = type;
        this->value = value;
      }
  }

  class Compiler {

    std::string id = "result";

    std::stack<Variable> *Stack;

    std::map<std::string, Variable> Symbols;
    std::vector<std::string> AssemblyCode;  

    void generate_three() {
      
    }

    Variable * calculateStackTop(std::string operator) {
      switch(operator) {
        case '+':
          break;
        case '-':
          break;
        case '*':
          break;
        case '/':
          break;
      }
    }

    public:

    void stack_push(Variable *variable) {
      Stack->push(variable);
    }

    void throw_stack(std::string operator) {

      static int variableCounter;
      
      Variable top = Stack->top();
      Stack->pop();
      Variable top2 = Stack->top();
      Stack->pop();

      Variable *templaryVariable = this->calculateStackTop(operator);
      variableCounter++;
      std::string vid = this->id + std::to_string(variableCounter);
      this->Symbols->insert( std::pair<vid, templaryVariable> );

      Stack->push(templaryVariable)
      this->generate_three();
    }
  }

%}

%union 
{
  char *textValue;
  int	integerValue;
  double decimalValue;
};


%token INT DOUBLE STRING BOOLEAN;
%token IF ELSE WHILE RETURN;
%token READ PRINT;
%token TRUE FALSE COMMENT;
%token EQ NEQ GEQ LEQ;

%token<textValue> TEXT;
%token<integerValue> VALUE_INTEGER;
%token<decimalValue> VALUE_DECIMAL;

%%

lines:
       line
     | lines line   { }
     ;

line:
       	declaration { }
     | 	assignment  { }
     ;
     
assignment:
		typeName elementCmp '=' elementCmp ';' { compiler->throw_stack(); }
	|	typeName elementCmp '=' expression ';' { compiler->throw_stack(); }
	;

declaration:
     	typeName elementCmp ';' { }
     ;


typeName:
       INT     {  printf("Syntax: typ int\n"); }
     | DOUBLE  {  printf("Syntax: typ double\n"); }
     | STRING  {  printf("Syntax: typ string\n"); }
     | BOOLEAN {  printf("Syntax: typ bool\n"); }
      ;

expression:
	  components '+' expression {  compiler->throw_stack(); }
	| components '-' expression {  compiler->throw_stack(); }
	| components
	;

components:
	  components '*' elementCmp {  compiler->throw_stack(); }
	| components '/' elementCmp {  compiler->throw_stack(); }
	| elementCmp 
	;

elementCmp:
	   VALUE_INTEGER			{  compiler->stack_push(new Variable(Type::Integer, std::to_string($1))); }
	   | VALUE_DECIMAL		{  compiler->stack_push(new Variable(Type::Double, std::to_string($1))); }
     | TEXT             {  compiler->stack_push(new Variable(Type::Text, std::to_string($1))); }
	;

%%


int main(int argc, char *argv[])
{

  Compiler *compiler = new Compiler();

	yyparse();

  delete compiler;
	return 0;
}