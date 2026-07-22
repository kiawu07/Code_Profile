/*
Header file for account class
ALwalid Kiawu, 7/5/2026, 11:17AM
*/

#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_

#include <string>
#include "client.hpp"

using namespace std;

class Account{

    private:
        int account_number;
        string client_name;
        int PIN;
        double balance;
        string statement;

    public:
        Account(Client client, int Pin);

        //getters
        int getAccountNumber();
        string getClientName();
        int getPIN();
        double getBalance(); 
        string getStatement();

        void deposit(double amount);
        void withdraw(double amount);
        

};
#endif // ACCOUNT_HPP_
