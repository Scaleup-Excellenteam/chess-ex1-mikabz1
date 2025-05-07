#pragma once
#include <iostream>
#include <utility>

// Exception class for handling invalid input during piece promotion.
class WrongPromotionInput : public std::exception{
public:
    explicit WrongPromotionInput(std::string  msg) : _msg(std::move(msg)){}
    const char* what() const noexcept override{
        return _msg.c_str();
    }

private:
    std::string _msg;
};

// Exception class for handling cases where a null piece is encountered unexpectedly.
class NullPiece : public std::exception{
public:
    explicit NullPiece(std::string  msg) : _msg(std::move(msg)){}
    const char* what() const noexcept override{
        return _msg.c_str();
    }

private:
    std::string _msg;
};

