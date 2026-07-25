/*
Header file for Invest class
ALwalid Kiawu, 7/8/2026, 9:59AM
*/

#ifndef INVEST_HPP_
#define INVEST_HPP_

#include <string>
#include <vector>
#include "stock.hpp"
#include "holding.hpp"
#include "account.hpp"

using namespace std;

class Invest{

    private:
        double available_to_trade;
        vector <Stock> stocks;
        vector <Holding> holdings;
        string trade_history;

    public:

        Invest();

        double transfer_to_trade(Account &account, double amount, int PIN);
        double transfer_to_bank(Account &account, double amount, int PIN);

        double getStockValue(string symbol);

        double execute_buy(int stock_index, double dollar_amount);

        double execute_sell(int stock_index, double quantity);

        double networth();

        string getTradeHistory();

        void displayStocks();
        void displayHoldings();

        void advance();
};

#endif