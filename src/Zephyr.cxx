bool isFloat(string test) {
    istringstream iss(test);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}

Module::Module() {
    defs = function_map();
}

void Module::setFunction(string s, void(*f)(Zephyr* const)) {
    defs[s] = f;
}

function_map Module::getDefs() {
    return defs;
}

Lexer::Lexer(string text) {
    next = 0;
    words = vector<string>();
    istringstream iss(text);
    while(iss) {
        string word;
        iss >> word;
        words.push_back(word);
    }
}

string Lexer::nextWord() {
    return words[next++];
}

bool Lexer::nextWordExists() {
    return next < words.size();
}

StackObj::StackObj(float f) {
    tag = F_ACTIVE;
    f_ = f;
}

float StackObj::getFloat() {
    return f_;
}

int StackObj::type() {
    return tag;
}

Zephyr::Zephyr() {
    dictionary = function_map();
}

void Zephyr::define(string word, void(*f)(Zephyr* const)) {
    dictionary[word] = f;
}

Zephyr* Zephyr::addModule(Module m) {
    for (auto const& x: m.getDefs()) {
        define(x.first, x.second);
    }
    return this;
}

void Zephyr::run(string source_code) {
    lex = Lexer(source_code);
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

stack<StackObj> Zephyr::getStack() {
    return stack_;
}

int Zephyr::size() {
    return stack_.size();
}

StackObj Zephyr::pop() {
    auto t = stack_.top();
    stack_.pop();
    return t;
}
