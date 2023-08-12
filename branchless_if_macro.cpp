#include <iostream>


#define RTSZ(i) RTSZ1(i, __LINE__)
#define RTSZ1(i, l) RTSZ2(i, l)
#define RTSZ2(i, l) RTSZ_##i##_##l

/// Expands to an if statement surrogate
#define bif(condition, body) {                          \
    __label__ RTSZ(0), RTSZ(1);                         \
\
    void* cases[2] = { && RTSZ(1), && RTSZ(0) };        \
\
    goto *cases[condition];                             \
    RTSZ(0):                                            \
\
    body;                                               \
\
    RTSZ(1):                                            \
    ;                                                   \
}


int main() {

    int i = 10;

    bif(i < 10, {
        std::cout << "Condition is true" << std::endl;
    });

}

