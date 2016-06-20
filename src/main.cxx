#include "main.hpp"
#include "Zephyr.cxx"
#include "stdlib.cxx"

int main(int argc, const char * argv[]) {
    auto terp = Zephyr();
    auto stdlib = Module();
    stdlib.setFunction("print", print);
    stdlib.setFunction("pstack", print_stack);
    terp.addModule(stdlib);
    while(true) {
        string inp;
        cin >> inp;
        terp.run(inp);
    }
}
