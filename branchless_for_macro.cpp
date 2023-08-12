#include <iostream>


#define RTSZ(i) RTSZ1(i, __LINE__)
#define RTSZ1(i, l) RTSZ2(i, l)
#define RTSZ2(i, l) RTSZ_##i##_##l

/// Expands to a for loop surrogate
#define bfor(init, condition, post, body) {             \
    __label__ RTSZ(0), RTSZ(1), RTSZ(2);                \
\
    init;                                               \
\
    void* cases[2] = { && RTSZ(2), && RTSZ(1) };        \
\
    RTSZ(0):                                            \
    goto *cases[condition];                             \
    RTSZ(1):                                            \
\
    body;                                               \
\
    post;                                               \
\
    goto RTSZ(0);                                       \
\
    RTSZ(2):                                            \
    ;                                                   \
}


int main() {

    bfor(int i = 0, i < 10, i++, {
        std::cout << "Looping " << i << std::endl;
    });

}

