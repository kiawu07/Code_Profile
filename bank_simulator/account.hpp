/*
Header file for account class
ALwalid Kiawu, 7/5/2026, 11:17AM
*/

#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_

using namespace std;

class Account{

    private:
        int account_number;
        string client_name;
        int PIN;
        int balance;
        string statement;

    public:
        Account(Client client, int PIN);

        //getters
        int getAccountNumber();
        string getClientName();
        int getPIN();
        int getBalance(); 
        string getStatement();

        void deposit(int amount);
        void withdrawal(int amount);
        

};
#endif // ACCOUNT_HPP_
