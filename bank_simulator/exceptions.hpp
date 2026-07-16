/*
Header file for Exceptions
ALwalid Kiawu, 7/8/2026, 9:59AM
*/

#ifndef INVEST_EXCEPTIONS_HPP_
#define INVEST_EXCEPTIONS_HPP_

#include <string>
#include <exception>
using namespace std;

class InsufficientFundsException : public exception{

    string message;

    public:
        InsufficientFundsException(string m){
            message = m;
        }

        const char* what() const noexcept override { return message.c_str(); }


};

class InvalidChoiceException : public exception{

    string message;

    public:
        InvalidChoiceException(string m){
            message = m;
        }

        const char* what() const noexcept override { return message.c_str(); }


};

class InsufficientSharesException : public exception {

    string message;

    public:
        InsufficientSharesException(string m){
            message = m;
        }

        const char* what() const noexcept override { return message.c_str(); }

};
#endif