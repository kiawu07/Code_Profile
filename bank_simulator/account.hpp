/*
Header file for account class
ALwalid Kiawu, 7/5/2026, 11:17AM
*/

#ifndef 
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
        string getAccountType();
        int getBalance(); 

        //setters
        void setAccountNumber(int account_number);

        void deposit();
        void withdrawal();
        string getStatement();
        

};
#endif // ACCOUNT_HPP_
