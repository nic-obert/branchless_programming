#pragma once


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


/// Expands to a while loop surrogate
#define bwhile(condition, body) {                       \
    __label__ RTSZ(0), RTSZ(1), RTSZ(2);                \
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

