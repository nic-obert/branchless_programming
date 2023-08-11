#include <iostream>
#include <cstring>


unsigned int recursive_strlen(const char* c, unsigned int length) {

    /// Hanlder function type
    typedef unsigned int (*F)(const char*, unsigned int);

    /// Convenient struct to hold local handler functions
    struct Local {

        /// Handler function to call when the char is not null
        static unsigned int not_null_char(const char* c, unsigned int length) {
            // Continue searching for the null char
            return recursive_strlen(c + 1, length + 1);
        }

        /// Handler function to call when the char is null
        static unsigned int null_char(const char* c, unsigned int length) {
            // End the search for the null char
            return length;
        }

    };

    // Create a lookup table on the spot
    F cases[2] = { Local::not_null_char, Local::null_char };

    // Check if the char is null and call the appropriate handler function
    return (*cases[*c == '\0'])(c, length);
}


/// @brief Return the length of a null-terminated string.
/// @param str the null-terminated string.
/// @return the length of the null-terminated string.
unsigned int branchless_strlen(const char* str) {
    // Start searching for the null char
    return recursive_strlen(str, 0);
}


int main() {

    const char* tests[] = {
        "Hello World\0",
        "\0",
        "hi",
        " ",
    };

    for (int i = 0; i < 4; i++) {

        unsigned int len = branchless_strlen(tests[i]);

        if (len != strlen(tests[i])) {
            std::cerr << "Failed \"" << tests[i] << "\"" <<  std::endl;
            break;
        }

        std::cout << "Length of \"" << tests[i] << "\" is " << len << " bytes" << std::endl;

    }

}
