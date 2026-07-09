/*
Implementation file for Invest class
ALwalid Kiawu, 7/8/2026, 9:12PM
*/

#include "invest.hpp"
#include "account.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

Invest::Invest(){
    stock_value = 0;
    available_to_trade = 0;
    trade_history = "";
}

void Invest::transfer(Account &account, int amount){
    int input;
    cout << "Enter bank PIN \n";
    while(!(cin>>input) || account.getPIN() != input){
        cout << "Wrong PIN !!!!!!\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    ifstream in_file;
    in_file.open("stocks.txt");
    //read from file and store stocks syblols and their values in vectors

    //cheking bank balance
    if(account.getBalance() < amount){
        cout << "Insufficient balance in your account!!!\n";
    }else{
        available_to_trade += amount;
        account.withdrawal(amount);
    }
}

void Invest::buy_stock(int amount){
    if(available_to_trade < amount){
        cout << "Insufficient balance to buy stocks!!!\n";
    }else{
        available_to_trade -= amount;
        stock_value += amount;
        trade_history += "\nYou bought stocks worth " + to_string(amount);
    }
}

void Invest::sell_stock(int amount){
    
}



