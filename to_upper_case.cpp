#include "bless.hh"
#include "bcstring.hh"

#include <stdlib.h>


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


#include <iostream>


int main() {

    const char* str = "Hello World!";

    const char* upper = to_upper_case(str);

    std::cout << upper << std::endl;

}

