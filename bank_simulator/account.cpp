/*
Implementation file for account class
ALwalid Kiawu, 7/7/2026, 9:12PM
*/

#include "account.hpp"
#include "client.hpp"
#include <cstring>
using namespace std;

//constructor
Account::Account(Client client, int Pin){
    client_name = client.getName();
    account_number = 0;
    PIN = Pin;
    balance = 0;
    statement = "";

    //hash to generate account number
    string s_num = "";
    
    for(unsigned char x : client.getName()){
        if(s_num.size() < 7)break;
            s_num += to_string(int(tolower(x)));
            
        }
    
    while(s_num.size() < 7){
        s_num.push_back('0');
    }  
    
    this->account_number = stoi(s_num.substr(0, 7));

    }

    //Getters
int Account::getAccountNumber(){
    return account_number;
}

string Account::getClientName(){
    return client_name;
}

double Account::getBalance(){
    return balance;
}

int Account::getPIN(){
    return PIN;
}

string Account::getStatement(){
    return statement;
}

void Account::displayAccountInfo(){
    cout << "Account Number: " << account_number << endl;
    cout << "Balance: $" << balance << endl;
}

//deposit and withdrawal
void Account::deposit(double amount){
    balance += amount;
    statement +="\n";
    statement +="You deposited " + to_string(amount) + " to your account";
}

void Account::withdraw(double amount){
    balance -= amount;
    statement += "\n";
    statement += "You withdrew " + to_string(amount) + " from your account";
}