#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

bool isFloat(string test);
class Zephyr;
typedef map<string, void(*)(Zephyr* const)> function_map;

class Module {
private:
    function_map defs;
public:
    Module();
    void setFunction(string s, void(*f)(Zephyr* const));
    function_map getDefs();
};

class Lexer {
private:
    int next;
    vector<string> words;
public:
    Lexer(string text);
    string nextWord();
    bool nextWordExists();
};

struct StackObj {
    union {
        float f_;
    };
    enum {F_ACTIVE = 1} tag;
    StackObj(float f); 
    float getFloat();
    int type();
};

class Zephyr {
public:
    function_map dictionary;
    stack<StackObj> stack_;
public:
    Lexer lex = Lexer("");
public:
    Zephyr();
    void define(string word, void(*f)(Zephyr* const));
    Zephyr* addModule(Module m);
    void run(string source_code);
    stack<StackObj> getStack();
    int size();
    StackObj pop();
};
