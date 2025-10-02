//
// Created by 邱姜铭 on 2023/12/13.
//

#ifndef DATA_STRUCTURE_COMMON_EXCEPTION_H
#define DATA_STRUCTURE_COMMON_EXCEPTION_H


#include <exception>

namespace flight {
    class overflow : public std::exception {
    private:
        const char *msg;
    public:
        explicit overflow(const char *msg) {
            this->msg = msg;
        }

        const char *what() const noexcept override {
            return this->msg;
        }
    };

    class underflow : public std::exception {
    private:
        const char *msg;
    public:
        explicit underflow(const char *msg) {
            this->msg = msg;
        }

        const char *what() const noexcept override {
            return this->msg;
        }
    };

    class out_of_range : public std::exception {
    private:
        const char *msg;
    public:
        explicit out_of_range(const char *msg) {
            this->msg = msg;
        }

        const char *what() const noexcept override {
            return this->msg;
        }
    };

    class key_not_found : public std::exception {
    private:
        const char *msg;
    public:
        explicit key_not_found(const char *msg) {
            this->msg = msg;
        }

        const char *what() const noexcept override {
            return this->msg;
        }
    };

    class invalid_argument : public std::exception {
    private:
        const char *msg;
    public:
        explicit invalid_argument(const char *msg) {
            this->msg = msg;
        }

        const char *what() const noexcept override {
            return this->msg;
        }
    };

}
#endif //DATA_STRUCTURE_COMMON_EXCEPTION_H
