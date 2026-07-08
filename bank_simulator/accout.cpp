/*
Implementation file for account class
ALwalid Kiawu, 7/7/2026, 9:12PM
*/

#include "acount.hpp"
#include "client.hpp"
#include <iostream>
#include <cstring>
using namespace std;

//constructor
Account::Account(Client client, int PIN){
    this->client_name = client.getName();
    this->PIN = PIN;
    this->balance = 0;
    this->statement = "";

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

int Account::getBalance(){
    return balance;
}

string Account::getStatement(){
    return statement;
}

//deposit and withdrawal
void Acount::deposit(int amount){
    balance += amount;
    statement +="\n";
    statement +="You deposited " + to_string(amount) + " to your account";
}

void Acount::withdraw(int amount){
    balance -= amount;
    statement +="You withdrew " + to_string(amount) + " from your account";
}