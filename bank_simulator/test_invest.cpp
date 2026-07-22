/*
 Test file for Invest class
    Author: ALwalid Kiawu, 7/8/2026, 10:31AM
    Using AAA of testing(Arrange- set up the objects/data you need
                         Act- call the one thing you're actually testing
                         Assert- check that the result is what you expected
)
 */

#include "invest.hpp"
#include "account.hpp"
#include "exceptions.hpp"
#include "client.hpp"
#include <cassert>
#include <iostream>

#include <string>

using namespace std;

void test_buy_stock_success(){
    //Arrange

    Client client("Prince", 30, 123456789, "123 Main St", "USA");
    Account acc(client, 1234);
    acc.deposit(1000);

    Invest inv;
    inv.transfer_to_trade(acc, 1000, 1234); // give it money to trade with

    //Act
    inv.execute_buy(0,500.00);

    //Assert
    assert(acc.getBalance() < 1000.00);
    assert(inv.networth() > 0);

    cout << "test_buy_stock_success passed!\n";

}

void test_buy_stock_insufficient_funds(){
    //Arrange
    Client client("Prince", 30, 123456789, "123 Main St", "USA");
    Account acc(client, 1234);
    acc.deposit(1000);

    Invest inv;
    inv.transfer_to_trade(acc, 1000, 1234); // give it money to trade with

    //Act and Assert
    try{
        inv.execute_buy(0,1500.00);
        assert(false); // should not reach here
    }catch(InsufficientFundsException &e){
        assert(true); // expected exception
    }

    cout << "test_buy_stock_insufficient_funds passed!\n";
}

void test_sell_stock_success(){
    //Arrange
    Client client("Prince", 30, 123456789, "123 Main St", "USA");
    Account acc(client, 1234);
    acc.deposit(1000);

    Invest inv;
    inv.transfer_to_trade(acc, 1000, 1234); // give it money to trade with

    inv.execute_buy(0,500.00); // buy some stock

    //Act
    double result = inv.execute_sell(0, 2); // sell some stock
    inv.transfer_to_bank(acc, result, 1234); // transfer back to bank
    //Assert
    assert(acc.getBalance() == result);
    assert(inv.networth() > 0);

    cout << "test_sell_stock_success passed!\n";
}

void test_sell_stock_insufficient_shares(){
    //Arrange
    Client client("Prince", 30, 123456789, "123 Main St", "USA");
    Account acc(client, 1234);
    acc.deposit(1000);

    Invest inv;

    //Act and Assert
    try{
        inv.execute_sell(0, 100); // try to sell more than owned
        assert(false); // should not reach here
    }catch(NoHoldingsException &e){
        assert(true); // expected exception
    }

    cout << "test_sell_stock_insufficient_shares passed!\n";
}

int main(){
    cout << "Running test1...\n";
    test_buy_stock_success();
    cout << "Running test2...\n";
    test_buy_stock_insufficient_funds();
    cout << "Running test3...\n";
    test_sell_stock_success();
    cout << "Running test4...\n";
    test_sell_stock_insufficient_shares();

    cout << "All tests passed!\n";

    return 0;
}

