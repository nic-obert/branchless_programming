#include <cstring>
#include <iostream>


int recursive_search(const char* bytes, unsigned int index, unsigned int length, char target) {

    typedef int (*SearchF)(const char*, unsigned int, unsigned int, char);

    struct Local {

        /// Bytes are not equal, continue the search
        static int not_equal(const char* bytes, unsigned int index, unsigned int length, char target) {
            // Increment the index
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

            // Check if the byte array is finished
            return (*cases[index == length])(bytes, index, length, target);
        }

        /// Bytes are equal, end the search with success
        static int equal(const char* bytes, unsigned int index, unsigned int length, char target) {
            return index;
        }

    };

    SearchF cases[2] = { Local::not_equal, Local::equal };

    // Check if the bytes are equal
    return (*cases[*(bytes + index) == target])(bytes, index, length, target);
}


int linear_search(const char* bytes, unsigned int length, char target) {
    return recursive_search(bytes, 0, length, target);
}


int main() {

    const char* str = "Hi nic\0";

    int index_of_c = linear_search(str, strlen(str), 'c');

    std::cout << "Index of c is " << index_of_c << ", length is " << strlen(str) << std::endl;

}