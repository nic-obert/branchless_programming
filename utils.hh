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


        constexpr Option<T> () {
            this-> some = false;
        }

    public:

        static const Option<T> None;

        Option<T> (T value) {
            this->some = true;
            this->value = value;
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

    template <typename T> const Option<T> Option<T>::None = Option<T>();

}

