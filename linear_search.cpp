#include <cstring>
#include <iostream>


int recursive_search(const char* bytes, unsigned int index, unsigned int length, char target) {

    typedef int (*SearchF)(const char*, unsigned int, unsigned int, char);

    /// A Local struct to contain the case handler functions
    struct Local {

        /// Bytes are not equal, continue the search
        static int not_equal(const char* bytes, unsigned int index, unsigned int length, char target) {
            // Increment the index to check the next character
            index ++;

            struct Local {

                /// Index and length are equal, end the search with failure
                static int equal(const char* bytes, unsigned int index, unsigned int length, char target) {
                    return -1;
                }

                /// Index and length are not equal, continue the search
                static int not_equal(const char* bytes, unsigned int index, unsigned int length, char target) {
                    return recursive_search(bytes, index, length, target);
                }
            };

            SearchF cases[2] = { Local::not_equal, Local::equal };

            // Check if the byte array is finished and call the handler function
            return (*cases[index == length])(bytes, index, length, target);
        }

        /// Bytes are equal, end the search with success
        static int equal(const char* bytes, unsigned int index, unsigned int length, char target) {
            return index;
        }

    };

    // Create an array of function pointers to the case handler functions
    SearchF cases[2] = { Local::not_equal, Local::equal };

    // Check if the bytes are equal and call the handler function
    return (*cases[*(bytes + index) == target])(bytes, index, length, target);
}


/// Search for the specified target byte. 
///
/// Return the index of the char. Return -1 is not found.
int linear_search(const char* bytes, unsigned int length, char target) {
    // Start the recursive search and set the start index to 0
    return recursive_search(bytes, 0, length, target);
}


int main() {

    const char* str = "Hi nic\0";
    unsigned int length = strlen(str);

    int index_of_c = linear_search(str, length, 'c');

    std::cout << "Index of c is " << index_of_c << ", length is " << strlen(str) << std::endl;

}

