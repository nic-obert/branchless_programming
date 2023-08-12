#pragma once


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
unsigned int bstrlen(const char* str) {
    // Start searching for the null char
    return recursive_strlen(str, 0);
}


/// @brief Return a new uppercase version of the string
/// @param str the stirng to uppercase
/// @return the new uppercased string
const char* to_upper_case(const char* str) {

    unsigned int len = bstrlen(str);
    char* new_str = (char*) malloc(len);

    unsigned int i;

    bfor(i = 0, i < len, i++, {
        new_str[i] = str[i] - 32 * (str[i] >= 'a' && str[i] <= 'z');
    });

    new_str[len] = '\0';

    return new_str;
}


/// @brief Return a new lowercase version of the string
/// @param str the stirng to lowercase
/// @return the new lowercased string
const char* to_lower_case(const char* str) {

    unsigned int len = bstrlen(str);
    char* new_str = (char*) malloc(len);

    unsigned int i;

    bfor(i = 0, i < len, i++, {
        new_str[i] = str[i] + 32 * (str[i] >= 'A' && str[i] <= 'Z');
    });

    new_str[len] = '\0';

    return new_str;
}

