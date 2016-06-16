#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <string>
#include <stack>
#include <sstream>
using namespace std;

bool isFloat(string test) {
    istringstream iss(test);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

class Zephyr;
typedef map<string, void(*)(Zephyr* const)> function_map;

class Module {
private:
    function_map defs;
public:
    Module() {
        defs = function_map();
    }

    void setFunction(string s, void(*f)(Zephyr* const)) {
        defs[s] = f;
    }

    function_map getDefs() {
        return defs;
    }
};

class Lexer {
private:
    int next;
    vector<string> words;
public:
    Lexer(string text) {
        next = 0;
        words = vector<string>();
        istringstream iss(text);
        while(iss) {
            string word;
            iss >> word;
            words.push_back(word);
        }
    }

    string nextWord() {
        return words[next++];
    }

    bool nextWordExists() {
        return next < words.size();
    }
};

struct StackObj {
    union {
        float f_;
    };
    enum {F_ACTIVE = 1} tag;

    StackObj(float f) {
        tag = F_ACTIVE;
        f_ = f;
    }

    float getFloat() {
        return f_;
    }

    int type() {
        return tag;
    }
};



class Zephyr {
private:
    function_map dictionary;
    stack<StackObj> stack_;
public:
    Zephyr() {
        dictionary = function_map();
    }

    void addModule(Module m) {
        for (auto const& x: m.getDefs()) {
            dictionary[x.first] = x.second;
        }
    }

    void run(string source_code) {
        Lexer lex = Lexer(source_code);
        string word;
        float num_val;

        while(lex.nextWordExists()) {
            word = lex.nextWord();
            if(dictionary.find(word) != dictionary.end()) {
                dictionary[word](this);
            } else if (isFloat(word)) {
                StackObj x(stod(word));
                stack_.push(x);
            } else if (word != "") {
                cerr << "Unknown word" << endl;
            }
        }
    }

    stack<StackObj> getStack() {
        return stack_;
    }

    int size() {
        return stack_.size();
    }

    StackObj pop() {
        auto t = stack_.top();
        stack_.pop();
        return t;
    }
};

void print_stack_element(StackObj so) {
    if (so.type() == 1) {
        cout << so.getFloat() << endl;
    }
}


void print(Zephyr* const z) {
    if (z->size() < 1) {
        throw "Not enough items on stack";
    }
    auto t = z->pop();
    if(t.type() == 1) {
        print_stack_element(t);
    }
}

void print_stack(Zephyr* const z) {
    auto st = z->getStack();
    do {
        print_stack_element(st.top());
        st.pop();
    } while (!st.empty());
}



int main(int argc, const char * argv[]) {
    auto terp = Zephyr();
    auto stdio = Module();
    stdio.setFunction("print", print);
    stdio.setFunction("pstack", print_stack);
    terp.addModule(stdio);
    terp.run("1 2 3 print print print");
}
