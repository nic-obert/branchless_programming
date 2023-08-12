#include <iostream>


/// Call the callback function if the condition is met
void if_then(bool condition, void (*callback)()) {

    /// A struct containing handler functions
    struct Local {
        /// Handler function in case the condition is false (do nothing)
        static void c0() {}
    };

    void (*cases[2])() = { Local::c0, callback };

    (*cases[condition])();
}


int main() {

    int a = 0;
    int b = -1;

    struct Local {
        static void c0() {
            std::cout << "a <= b" << std::endl;
        }

        static void c1() {
            std::cout << "a > b" << std::endl;
        }
    };

    void (*cases[2])() = { Local::c0, Local::c1 };

    (*cases[a > b])();

}

