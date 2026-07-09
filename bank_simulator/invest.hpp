/*
Header file for Invest class
ALwalid Kiawu, 7/8/2026, 9:59AM
*/

#ifndef INVEST_HPP_
#define INVEST_HPP_

using namespace std;

class Invest{

    private:

        int stock_value;
        int available_to_trade;
        vector <string> stocks;
        vector <int> stock_values;
        vector <string> stocks_bought;
        vector <int> stock_values_bought;
        string trade_history;

    public:

        Invest();

        void transfer(Account &account, int amount);

        void buy_stock(int amount);

        void sell_stock(int amount);

        string getTradeHistory();


};

#endif