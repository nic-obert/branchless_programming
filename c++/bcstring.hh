#pragma once


#include "bless.hh"
#include "utils.hh"


namespace bcstring {

    using namespace utils;
    using namespace bless;


    usize recursive_strlen(const char* c, usize cur_length) {

        /// Hanlder function type
        typedef usize (*F)(const char*, usize);

        /// Convenient struct to hold local handler functions
        struct Local {

            /// Handler function to call when the char is not null
            static usize not_null_char(const char* c, usize cur_length) {
                // Continue searching for the null char
                return recursive_strlen(c + 1, cur_length + 1);
            }

            /// Handler function to call when the char is null
            static usize null_char(const char* c, usize cur_length) {
                // End the search for the null char
                return cur_length;
            }

        };

        // Create a lookup table on the spot
        F cases[2] = { Local::not_null_char, Local::null_char };

        // Check if the char is null and call the appropriate handler function
        return (*cases[*c == '\0'])(c, cur_length);
    }


    /// @brief Return the length of a null-terminated string.
    /// @param str the null-terminated string.
    /// @return the length of the null-terminated string.
    usize strlen(const char* str) {
        // Start searching for the null char
        return recursive_strlen(str, 0);
    }


    /// @brief Return a new uppercase version of the string
    /// @param str the stirng to uppercase
    /// @return the new uppercased string
    char* to_upper_case(const char* str) {

        usize len = strlen(str);
        char* new_str = (char*) malloc(len);

        usize i;

        bfor(i = 0, i < len, i++, {
            new_str[i] = str[i] - 32 * (str[i] >= 'a' && str[i] <= 'z');
        });

        new_str[len] = '\0';

        return new_str;
    }


    /// @brief Return a new lowercase version of the string
    /// @param str the stirng to lowercase
    /// @return the new lowercased string
    char* to_lower_case(const char* str) {

        usize len = strlen(str);
        char* new_str = (char*) malloc(len);

        usize i;

        bfor(i = 0, i < len, i++, {
            new_str[i] = str[i] + 32 * (str[i] >= 'A' && str[i] <= 'Z');
        });

        new_str[len] = '\0';

        return new_str;
    }


    /// @brief Copy `num` bytes from `src` to `dest`. Note: the memory regions shouldn't unsafely overlap.
    /// @param dest address of the destination memory region
    /// @param src address of the source memory region
    /// @param num number of bytes to copy
    void memcpy(void* dest, const void* src, usize num) {
        bfor(usize i = 0, i < num, i++, {
            ((char*)dest)[i] = ((const char*)src)[i];
        });
    }


    /// @brief Copy `num` bytes from `src` to `dest`. If the memory regions are unsafely overlapping, use an intermediate buffer to ensure correct copying.
    /// @param dest address of the destination memory region
    /// @param src address of the source memory region
    /// @param num number of bytes to copy
    void memmove(void* dest, const void* src, usize num) {

        auto overlapping = [dest, src, num] () -> void {
            void* buf = malloc(num);
            memcpy(dest, buf, num);
            free(buf);
        };

        auto non_overlapping = [dest, src, num] () -> void {
            memcpy(dest, src, num);
        };
        
        // Check for unsafe overlaps
        if_then_else(src < dest && (char*)src + num > dest,
            overlapping,
            non_overlapping
        );

    }


    Option<usize> find_first(const char* str, std::function<bool(char)> condition) {

        bfor(usize i = 0, str[i] != '\0', i++, {
            bif(condition(str[i]), {
                return Option(i);
            });
        });

        return Option<usize>::None;
    }

}

