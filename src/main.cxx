#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

bool isFloat(string test) {
    istringstream iss(test);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

class Zephyr;

class Function {
public:
    void run(Zephyr* const z) {

    }
};

class Module {
private:
    map<string, Function> defs;
public:
    Module() {
        defs = map<string, Function>();
    }
};

class IO : public Module {

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

union StackObj {
    float f;
    double d;
};



class Zephyr {
private:
    map<string, Function> dictionary;
    vector<StackObj> stack;
public:
    Zephyr() {
        dictionary = map<string, Function>();
    }

    void addModule(Module m) {

    }

    void run(string source_code) {
        Lexer lex = Lexer(source_code);
        string word;
        float num_val;

        while(lex.nextWordExists()) {
            word = lex.nextWord();
            if(dictionary.find(word) != dictionary.end()) {
                dictionary[word].run(this);
            } else if (isFloat(word)) {
                StackObj x;
                x.d = stod(word);
                stack.push_back(x);
            } else if (word != "") {
                cerr << "Unknown word" << endl;
            }
        }
    }

    vector<StackObj> getStack() {
        return stack;
    }
};

int main(int argc, const char * argv[]) {
    auto terp = Zephyr();
    terp.run("1 2 3 45 678");
    auto stack = terp.getStack();
}
