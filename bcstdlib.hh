#pragma once


#include "utils.hh"
#include "bcstring.hh"

#include <cctype>


namespace bcstdlib {

    using namespace utils;
    using namespace bcstring;


    Option<int> char_to_digit(char c) {
        bif(c >= '0' && c <= '9', {
            return Option(c - '0');
        });
        return Option<int>::None();
    }


    Option<int> atoi(const char* str) {

        // Find first non-whitespace character
        Option<usize> op = find_first(str, isspace);

        bif(op.is_none(), {
            return Option<int>::None();
        });

        usize i = op.unwrap();

        bool is_negative = str[i] == '-';
        i += is_negative;

        int number = 0;

        bfor(;, str[i] != '\0', i++, {
            Option<int> op = char_to_digit(str[i]);
            bif(op.is_none(), {
                return (number * !is_negative) + (-number * is_negative);
            });
            number += op.unwrap();
        });

        return (number * !is_negative) + (-number * is_negative);
    }

}

