/*Header file for client class
Alwalid Kiawu, July 2, 2026, 5:10 PM
*/

#include <iostream>
#include <string>
#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client{

    private:
        string name;
        int account_number;
        int pin;
        int balance;
        string account_type;
        int withdrawal_limit;
        int deposit_limit;
        int stock_value;
    
    public:

        Client(){
            name = "";
            account_number = 0;
            pin = 0;
            balance = 0;
            account_type = "";
            withdrawal_limit = 0;
            deposit_limit = 0;
            stock_value = 0;    
        }

        //setters
        void set_name(string n){};

        void set_account_number(){};

        void set_pin(){};

        void set_balance(){};

        void set_account_type(){};

        void set_stock_value(){};

        //getters
        string get_name(){};

        int get_account_number(){};

        int get_balance(){};

        int get_stock_value(){};

};



#endif