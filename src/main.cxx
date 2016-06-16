#include "main.hpp"
#include "Zephyr.cxx"
#include "IO.cxx"

int main(int argc, const char * argv[]) {
    auto terp = Zephyr();
    auto stdio = Module();
    stdio.setFunction("print", print);
    stdio.setFunction("pstack", print_stack);
    terp.addModule(stdio)->run("1 2 3 print print print");
}
