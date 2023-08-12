#pragma once


#include <utility>
#include <stdint.h>


namespace utils {

    typedef uint64_t usize;
    typedef int64_t isize;


    template <typename T>
    class Option {

    private:

        bool some;
        T value;

    public:

        Option<T> (T value) {
            this->some = true;
            this->value = value;
        }


        static Option<T> None() {
            return Option { false, nullptr };
        }


        bool is_some() {
            return this->some;
        }


        bool is_none() {
            return !this->some;
        }


        T unwrap() {
            return std::move(this->value);
        }

    };

}

