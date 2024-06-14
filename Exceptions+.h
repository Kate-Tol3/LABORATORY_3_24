#pragma once

#include <exception>
#include <iostream>
#include <string>

class EmptyExeption: public std::exception {
private:
    std::string message;
public:
    explicit EmptyExeption(){
        message = "Error Length is Null";
    };

    const char* what() const throw() override
    {
        return message.c_str();
    }
};
