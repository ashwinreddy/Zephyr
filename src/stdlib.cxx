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
