#include <iostream>


#define RTSZ(i) RTSZ1(i, __LINE__)
#define RTSZ1(i, l) RTSZ2(i, l)
#define RTSZ2(i, l) RTSZ_##i##_##l

/// Expands to a while loop surrogate
#define bwhile(condition, body) {                       \
    __label__ RTSZ(0), RTSZ(1);                         \
\
    void* cases[2] = { && RTSZ(2), && RTSZ(1) };        \
\
    RTSZ(0):                                            \
    goto *cases[condition];                             \
    RTSZ(1):                                            \
\
    body;                                               \
\
    goto RTSZ(0);                                       \
\
    RTSZ(2):                                            \
    ;                                                   \
}


int main() {

    int i = 0;

    bwhile(i < 10, {
        std::cout << "Looping " << i << std::endl;
        i++;
    });

}

