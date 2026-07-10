/*
Implementation file for Invest class
ALwalid Kiawu, 7/8/2026, 9:12PM
*/

#include "invest.hpp"
#include "account.hpp"
#include "stock.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

Invest::Invest(){
    stock_value = 0;
    available_to_trade = 0;
    trade_history = "";
    
    ifstream in_file;
    in_file.open("stocks.csv");
    //read from file and store stocks syblols and their values in vector
    string line;
    getline(in_file, line);
    string name, symbol;
    double value;
    while(in_file >> name >> symbol >> value){
        Stock stock;
        stock.name = name;
        stock.symbol = symbol;
        stock.quantity = 1;
        stock.value = value;
        stocks.push_back(stock);
    }
    
}

void Invest::transfer_to_trade(Account &account, int amount){
    int input;
    cout << "Enter bank PIN \n";
    while(!(cin>>input) || account.getPIN() != input){
        cout << "Wrong PIN !!!!!!\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    //cheking bank balance
    if(account.getBalance() < amount){
        cout << "Insufficient balance in your account!!!\n";
    }else{
        available_to_trade += amount;
        account.withdrawal(amount);
    }
}

void Invest::transfer_to_bank(Account &account, int amount){
    int input;
    cout << "Enter bank PIN \n";
    while(!(cin>>input) || account.getPIN() != input){
        cout << "Wrong PIN !!!!!!\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    //cheking available balance to trade
    if(available_to_trade < amount){
        cout << "Insufficient balance to transfer to bank account!!!\n";
    }else{
        available_to_trade -= amount;
        account.deposit(amount);
    }
}

void Invest::buy_stock(){
    unsigned int choice;
    cout << "Select a stock to buy from the following list by entering its number:\n";
    for(int i = 0; i < stocks.size(); i++){
        cout << i+1 << ". " << stocks[i].name << " (" << stocks[i].symbol << ") - $" << stocks[i].value << endl;
    }
    while(!(cin >> choice) || choice < 1 || choice > stocks.size()){
        cout << "Please enter a valid choice!!!\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    double amount;
    double quantity;
    cout << "How much(dollars) you want to spend buying " << stocks[choice-1].name << "?\n";
    while(!(cin>>amount)){
        cout << "Enter enter a valid amount!!!\n";
    }
    if(available_to_trade < amount){
        cout << "Insufficient balance to buy stocks!!!\n";
        cout << "Transaction failed!!!!!\n";
        return;
    }else{
        //buying stock
        quantity = amount / stocks[choice-1].value;
        Stock stock_purchased = {stocks[choice-1].name,stocks[choice-1].symbol, quantity, stocks[choice-1].value};
        stocks_bought.push_back(stock_purchased);
        cout << "You bought " << quantity << " shares of " << stocks[choice-1].name << " (" << stocks[choice-1].symbol << ") for $" << amount << endl;
        trade_history += "\nYou bought " + to_string(quantity) + " shares of " + stocks[choice-1].name + " (" + stocks[choice-1].symbol + ") for $" + to_string(amount);
        available_to_trade -= amount;
        stock_value += amount;
    }
}

void Invest::sell_stock(){
    cout << "Please select a stock to sell from your portfolio by entering its number:\n";
    for(int i = 0; i < stocks_bought.size(); i++){
        cout << i+1 << ". " << stocks_bought[i].name << " (" << stocks_bought[i].symbol << ") - " << stocks_bought[i].quantity << " shares at $" << stocks_bought[i].value << endl;
    }
    unsigned int choice;
    while(!(cin >> choice) || choice < 1 || choice > stocks_bought.size()){
        cout << "Please enter a valid choice!!!\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    double amount;
    cout << "How much worth(dollars) of" << stocks_bought[choice-1].symbol << "You want to sell\n";
    while(!(cin>>amount)){
        cout << "Please enter a valid amount in dollars\n";
    }
    if(stocks_bought[choice-1].value < amount){
        cout << "Insufficinet amount of " << stocks_bought[choice-1].symbol << "to sell\n";
        cout << "Transaction failed!!!" << endl;
        return;
    }else if(stocks_bought[choice-1].value == amount){
        cout << "You are selling all of " << stocks_bought[choice-1].symbol << endl;
        trade_history += "\nYou sold all of " + stocks_bought[choice-1].name + " (" + stocks_bought[choice-1].symbol + ") for $" + to_string(amount);
        available_to_trade += amount;
        stocks_bought.erase(stocks_bought.begin() + choice - 1);
        stock_value -= amount;
    }else{
        cout << "You are selling " << amount << " worth of " << stocks_bought[choice-1].symbol << endl;
        stocks_bought[choice-1].value -= amount;
        stocks_bought[choice-1].quantity -= amount / stocks_bought[choice-1].value;
        trade_history += "\nYou sold " + to_string(amount) + " worth of " + stocks_bought[choice-1].name + " (" + stocks_bought[choice-1].symbol + ") for $" + to_string(amount);
        available_to_trade += amount;
        stock_value -= amount;
    }
}




