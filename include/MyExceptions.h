#pragma once
#include <iostream>
#include <utility>

// Exception class for handling invalid input during piece promotion.
class WrongPromotionInput : public std::exception{
public:
    // Constructs the exception with a custom error message.
    explicit WrongPromotionInput(std::string  msg) : _msg(std::move(msg)){}

    // Returns the error message associated with the exception.
    const char* what() const noexcept override{
        return _msg.c_str();
    }

private:
    std::string _msg;// Stores the error message.
};

// Exception class for handling cases where a null piece is encountered unexpectedly.
class NullPiece : public std::exception{
public:
    // Constructs the exception with a custom error message.
    explicit NullPiece(std::string  msg) : _msg(std::move(msg)){}

    // Returns the error message associated with the exception.
    const char* what() const noexcept override{
        return _msg.c_str();
    }

private:
    std::string _msg;// Stores the error message.
};

