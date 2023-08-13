#include "bless.hh"
#include "bcstdlib.hh"
#include "utils.hh"

#include <iostream>
#include <vector>
#include <cmath>


using namespace utils;
using namespace bless;


std::vector<unsigned int> factorize(unsigned int num) {

    std::vector<unsigned int> factors = std::vector<unsigned int>();

    bif(num == 0 || num == 1, {
        factors.push_back(num);
        return factors;
    });

    bwhile(num % 2 == 0, {
        factors.push_back(2);
        num /= 2;
    });

    usize i = 3;
    bwhile(i <= sqrt(num) + 1, {
        bif_else(num % i == 0, {
            factors.push_back(i);
            num /= i;
        }, {
            i += 2;
        });
    });

    bif(num > 2, {
        factors.push_back(num);
    });

    return factors;
}


int main(int argc, const char* argv[]) {

    bif(argc != 2, {
        std::cout << "Expected a single integer argument" << std::endl;
        return 1;
    });

    const char* str = argv[1];

    auto op = bcstdlib::atoi(str);
    
    bif(op.is_none(), {
        std::cout << "Input could not be converted into an integer: \"" << str << "\"" << std::endl;
        return 1;
    });

    int num = op.unwrap();

    bif(num < 0, {
        std::cout << "Cannot factorize negative numbers" << std::endl;
        return 1;
    });

    auto factors = factorize(num);

    std::cout << "Prime factors of " << num << " are: \n";
    bfor(usize i = 0, i < factors.size(), i++, {
        std::cout << factors[i] << ", ";
    });

    std::cout << std::endl;

}

