/*
Implementation file for Invest class
ALwalid Kiawu, 7/8/2026, 9:12PM
*/

#include "invest.hpp"
#include "account.hpp"
#include "stock.hpp"
#include "holding.hpp"
#include "exceptions.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const string STOCKS_FILE = "stocks.csv";

Invest::Invest(){
    available_to_trade = 0;
    trade_history = "";
    ifstream in_file;
    in_file.open(STOCKS_FILE);
    if(!in_file.is_open()){
        throw runtime_error("Could not open stocks file "+STOCKS_FILE);
    }
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
        stock.value = value;
        stocks.push_back(stock);
    }
    in_file.close();
    
}

double Invest::transfer_to_trade(Account &account, double amount, int PIN){
    if(account.getPIN() != PIN){
        throw InvalidPINException("Invalid PIN");
    }
    //cheking bank balance
    if(account.getBalance() < amount){
        throw InsufficientFundsException("Insufficient funds to transfer to trade");
    }else{
        available_to_trade += amount;
        account.withdraw(amount);
    }
    return available_to_trade;
}

double Invest::transfer_to_bank(Account &account, double amount, int PIN){
    if(account.getPIN() != PIN){
        throw InvalidPINException("Invalid PIN");
    }
    

    //cheking available balance to trade
    if(available_to_trade < amount){
        throw InsufficientFundsException("Insufficient funds to transfer to bank");
    }else{
        available_to_trade -= amount;
        account.deposit(amount);
    }
    return available_to_trade;
}

double Invest::getStockValue(string symbol){
    for(Stock stock : stocks){
        if(stock.symbol == symbol){
            return stock.value;
        }
    }
    return 0;
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



double Invest::execute_sell(int stock_index, double quantity){
    if(holdings.size() == 0){
        throw NoHoldingsException("No shares to sell");
    }
    if(stock_index < 0 || stock_index >= holdings.size()){
            throw InvalidChoiceException("Invalid stock index");
        }
    if(quantity <= 0){
        throw InvalidQuantityException("Quantity must be greater than 0");
    }
    if(quantity > holdings[stock_index].quantity){
        throw InsufficientSharesException("Insufficient quantity of shares to sell");
    }
    double curr_price = getStockValue(holdings[stock_index].symbol);
    double proceeds = quantity * curr_price;
    if(quantity >= holdings[stock_index].quantity){
        trade_history += "\nYou sold all of " + holdings[stock_index].name + " (" + holdings[stock_index].symbol + ") for $" + to_string(proceeds);
        available_to_trade += proceeds;
        holdings.erase(holdings.begin() + stock_index);
    }else{
        holdings[stock_index].quantity -= quantity;
        trade_history += "\nYou sold " + to_string(quantity) + " shares of " + holdings[stock_index].name + " (" + holdings[stock_index].symbol + ") for $" + to_string(proceeds);
        available_to_trade += proceeds;
    }
    return proceeds;
}


double Invest::networth(){
    double tot_val = available_to_trade;
    for(Holding holding: holdings){
        string symbol = holding.symbol;
        double the_quantity = holding.quantity;
        double the_value = getStockValue(symbol);
        tot_val += the_quantity * the_value;
    }
    return tot_val;
}

string Invest::getTradeHistory(){
    return trade_history;
}

double Invest::getAvailableToTrade(){
    return available_to_trade;
}

void Invest::displayStocks(){
    cout << "Available Stocks for Trading:\n";
    cout << left << setw(5) << "No." << setw(15) << "Name" << setw(7) << "Symbol" << "Value" << endl;
    for(int index = 0; index != stocks.size(); index++){
        cout << left << setw(5) << index +1 << setw(15) << stocks[index].name << setw(7) << stocks[index].symbol;
        cout << fixed << setprecision(2) << stocks[index].value << endl;
    }
}

void Invest::displayHoldings(){
    cout << "Your Current Holdings:\n";
    cout << left << setw(5) << "No." << setw(15) << "Name" << setw(7) << "Symbol" << setw(10) << "Quantity" << "Value" << endl;
    for(int index = 0; index != holdings.size(); index++){
        cout << left << setw(5) << index +1 << setw(15) << holdings[index].name << setw(7) << holdings[index].symbol;
        cout << fixed << setprecision(2) << holdings[index].quantity << " " << holdings[index].cost_basis << endl;
    }

}

void Invest::Advance(){
    for(Stock &stock : stocks){
        int percentage = (rand() % 11) -5;// -5% to +5%
        stock.value += stock.value * (percentage/100.0);// update stock value by percentage
        if(stock.value < 0){
            stock.value = 1.0; // prevent negative stock value
        }
    }
}
