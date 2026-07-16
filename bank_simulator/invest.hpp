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
        vector <Holding> holdings;
        string trade_history;

    public:

        Invest();

        void transfer(Account &account, int amount);

        double execute_buy(int stock_index, double dollar_amount);

        void execute_sell(int stock_index, double quantity);

        string getTradeHistory();


};

#endif