/*
Implementation file for Invest class
ALwalid Kiawu, 7/8/2026, 9:12PM
*/

#include "invest.hpp"
#include "account.hpp"
#include "stock.hpp"
#include "holding.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

Invest::Invest(){
    stock_value = 0;
    available_to_trade = 0;
    trade_history = "";
    
    ifstream in_file;
    in_file.open("stocks.csv");
    //read from file and store stocks syblols and their values in vector
    string line;
    getline(in_file, line); // Skip the header line
    string name, symbol;
    double value;
    while(getline(in_file,line)){
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, symbol, ',');
        ss >> value;
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

double Invest::execute_buy(int stock_index, double dollar_amount){
        if(stock_index < 0 || stock_index >= stocks.size()){
            throw InvalidChoiceException("Invalid stock index");
        }
        if(dollar_amount > available_to_trade){
            throw InsufficientFundsException("Insufficient funds to execute buy");
        }
        double quantity = dollar_amount / stocks[stock_index].value;
        Holding stock_purchased = {stocks[stock_index].name,stocks[stock_index].symbol, quantity, dollar_amount};
        holdings.push_back(stock_purchased);
        trade_history += "\nYou bought " + to_string(quantity) + " shares of " + stocks[stock_index].name + " (" + stocks[stock_index].symbol + ") for $" + to_string(dollar_amount);
        available_to_trade -= dollar_amount;
        return quantity;
    }


void Invest::execute_sell(int stock_index, double quantity){
    if(stock_index < 0 || stock_index >= holdings.size()){
            throw InvalidChoiceException("Invalid stock index");
        }
    if(quantity > holdings[stock_index].quantity){
        throw InsufficientSharesException("Insufficient quantity of shares to sell");
    }
    double curr_price;
    for(Stock stock : stocks){
        if(stock.symbol == holdings[stock_index].symbol){
            curr_price = stock.value;
            break;
        }
        curr_price = 0;
    }
    if(quantity >= holdings[stock_index].quantity){
        trade_history += "\nYou sold all of " + holdings[stock_index].name + " (" + holdings[stock_index].symbol + ") for $" + to_string(quantity * curr_price);
        available_to_trade += quantity * curr_price;
        holdings.erase(holdings.begin() + stock_index);
    }else{
        holdings[stock_index].quantity -= quantity;
        trade_history += "\nYou sold " + to_string(quantity) + " shares of " + holdings[stock_index].name + " (" + holdings[stock_index].symbol + ") for $" + to_string(quantity * curr_price);
        available_to_trade += quantity * curr_price;
    }
}