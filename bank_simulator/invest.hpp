/*
Header file for Invest class
ALwalid Kiawu, 7/8/2026, 9:59AM
*/

#ifndef INVEST_HPP_
#define INVEST_HPP_

using namespace std;

class Invest{

    private:

        double stock_value;
        double available_to_trade;
        vector <Stock> stocks;
        vector <Stock> stocks_bought;
        string trade_history;

    public:

        Invest();

        void transfer(Account &account, int amount);

        void buy_stock();

        void sell_stock();

        string getTradeHistory();


};

#endif