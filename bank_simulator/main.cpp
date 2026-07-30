/**
Main program for the investment bank simulator project. 
This program simulates a simple banking system where clients can create accounts, 
deposit and withdraw money, and invest in stocks. The program uses classes to represent clients,
accounts, and investments, and provides a command-line interface for users to interact with the system.
Alwalid Kiawu, 7/22/2026, 8:45AM
 */

#include "invest.hpp"
#include "account.hpp"
#include "client.hpp"
#include "exceptions.hpp"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>
using namespace std;

void intro();
Client create_client();
void main_menu();
void dashboard(Account &account, Invest &invest, Client &client);
void transfer_money(Account &account, Invest &invest);
void invest_menu(Invest &invest, Account &account);
void advance(int &days, Invest &invest);
void outro(Account &account, Invest &invest);
void report(Account &account, Invest &invest, Client &client);

int main(){
    srand(time(0));
    int days = 1;


    intro();
    Client client = create_client();
    cout << "Let's create your bank account now!\n";
    int PIN;
    cout << "Enter a 4-digit PIN for your account\n";
    while(!(cin>>PIN) || PIN < 1000 || PIN > 9999){
        cout << "Please enter a valid 4-digit PIN!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    Account account(client, PIN);
    Invest invest;
    cout << "Your bank and investment accounts have been created successfully!\n";
    cout << "For the purpose of this simulator, we will deposit $1,000 in your account and"
            " see how much you can grow it\n";
    account.deposit(1000);
    cout << "Transfer money to you investment account and try to grow it\n";
    
    bool running = true;

    while(running){
        dashboard(account, invest, client);

        main_menu();


        int input;

        while(!(cin>>input)){
            cout << "Please enter a valid input \n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch(input){
            case 1:{//transfer money to/from investing account
                transfer_money(account, invest);
                break;

            }

            case 2:{//invest in stocks
                invest_menu(invest, account);
                break;
            }

            case 3:{//Advance 
                advance(days, invest);
                break;
            }

            case 4:{//outro
                report(account, invest, client);
                outro(account, invest);
                running = false;
                break;
            }

            default :
                cout << "Please enter a valid input from 1-4!!\n";
        }
    }

    return 0;
}

//functions defination
void intro(){
    cout << "\n============KIAgrowTm*==============\n";
    cout << "Welcome to KIAGrowTm* Investment Bank Simulator by Alwalid Kiawu!\n";
    cout << "This program simulates a simple banking system where clients can create accounts, deposit and withdraw money, and invest in stocks.\n";
    cout << "You will be able to create an account, transfer money to/from your investing account, invest in stocks, and advance time to see how your investments perform.\n";
    cout << "Let's get started!\n";
    cout << "=====================================\n\n";
}

Client create_client(){
    // Implementation for creating a client
    cout << "Enter your informations to create you account to start investing!\n\n";
    string name;
    cout << "Enter your full name\n";
    getline(cin, name);
    int age;
    cout << "Enter your age\n";
    while(!(cin>>age)){
        cout << "Please enter a valid age!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    cin.ignore(1000,'\n');
    string address;
    cout << "Enter your address\n";
    getline(cin, address);
    string nationality;
    cout << "Enter your nationality\n";
    getline(cin, nationality);
    cout << "All your details have been saved!!\n";
    Client client(name, age, address, nationality);
    return client;
}

void dashboard(Account &account, Invest &invest, Client &client){
    cout << "\n=================DASHBOARD=================\n";
    cout << "CLIENT INFORMATION:\n";
    client.displayClientInfo();
    cout << "\n";
    cout << "ACCOUNT INFORMATION:\n";
    account.displayAccountInfo();
    cout << "Available to Trade in Investment Account: " << invest.getAvailableToTrade() << endl;
    cout << "Your Investment Account Worth: " << invest.networth() << endl;
    cout << "Your total net worth is: " << account.getBalance() + invest.networth() << endl;
    cout << "===========================================\n\n";
}

void main_menu(){
    cout << "\n================MAIN MENU=================\n";
    cout << "Enter...:\n";
    cout << "1. Transfer Money\n";
    cout << "2. Invest in Stocks\n";
    cout << "3. Advance Time\n";
    cout << "4. Exit\n";
    cout << "===========================================\n\n";
}

void transfer_money(Account &account, Invest &invest){
    // Implementation for transferring money
    cout << "\n\n";
    cout << "Transferring Money......\n";
    cout << "Enter 1, to tranfer money from your bank account to your investment account\n";
    cout << "Enter 2, to transfer money from your investment account to your bank account\n";
    int choice;
    while(!(cin>>choice) || (choice != 1 && choice != 2)){
        cout << "Please enter a valid choice (1 or 2)!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    double amount;
    cout << "Enter the amount to transfer in dollars\n";
    while(!(cin >> amount)){
        cout << "Please enter a valid amount!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    int PIN;
    cout << "Please enter your PIN\n";
    while(!(cin >> PIN)){
        cout << "Please enter a valid PIN!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    try{
        if(choice == 1){
            cout << "Tranfering money from your bank account to your investment account\n";
            invest.transfer_to_trade(account, amount, PIN);
            cout << "Confirmation of the transfer of " << amount << " to investment account\n";
        }else{
            cout << "Tranfering money from your investment account to your bank account\n";
            invest.transfer_to_bank(account, amount, PIN);
            cout << "Confirmation of the transfer of " << amount << " to bank account\n";
        }
    }catch(InvalidPINException &e){
        cout << e.what() << endl;
    }catch(InsufficientFundsException &e){
        cout << e.what() << endl;
    }
    cout << "\n\n";
    
}

void invest_menu(Invest &invest, Account &account){
    // Implementation for investing menu
    cout << "\n\n";
    cout << "Investing in Stocks......\n";
    cout << "Enter 1, to buy stocks\n";
    cout << "Enter 2, to sell some of your holdings\n";
    int choice;
    while(!(cin>>choice) || (choice != 1 && choice != 2)){
        cout << "Please enter a valid choice (1 or 2)!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    //Continue with the implementation for buying and selling stocks based on the user's choice
    if(choice == 1){//buy stocks
        int stock_index;
        cout << "Executing buy....\n";
        cout << "Enter the corresponding number for the stock you wish to buy\n";
        invest.displayStocks();
        while(!(cin>>stock_index)){
        cout << "Please enter a valid number!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
        }
        double fee;
        cout << "Enter the dollar amount you wish to invest in this stock\n";
        while(!(cin>>fee) || fee <= 0){
            cout << "Please enter a valid dollar amount!!\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }

        //executing buy
        try{
            double quantity_bought = invest.execute_buy(stock_index - 1, fee);
            cout << "Confirmation of the purchase of " << quantity_bought << " of stocks for $" << fee << endl;
        }catch(InvalidChoiceException &e){
            cout << e.what() << endl;
        }catch(InsufficientFundsException &e){
            cout << e.what() << endl;
        }

    }else{//sell stocks
        int stock_index;
        cout << "Executing sell....\n";
        cout << "Enter the corresponding number for the stock you wish to sell\n";
        invest.displayHoldings();
        while(!(cin>>stock_index)){
        cout << "Please enter a valid number!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
        }
        double quantity;
        cout << "Enter the quantity of shares you wish to sell\n";
        while(!(cin>>quantity) || quantity <= 0){
            cout << "Please enter a valid quantity!!\n";
            cin.clear();
            cin.ignore(1000,'\n');
        }

        //executing sell
        try{
            double proceeds = invest.execute_sell(stock_index - 1, quantity);
            cout << "Confirmation of the sale of " << quantity << " shares" << " for $" << proceeds << endl;
        }catch(InvalidChoiceException &e){
            cout << e.what() << endl;
        }catch(InsufficientSharesException &e){
            cout << e.what() << endl;
        }
    }
    cout << "\n\n";
}

void advance(int &days, Invest &invest){
    // Implementation for advancing time
    cout << "\n\n";
    cout << "Advancing Time......\n";
    cout << "Advancing time, watch out for the market fluctuations and see how your investments perform!\n";
    cout << "Day " << days << ":\n";
    days++;
    invest.Advance();
    cout << fixed << setprecision(2);
    double net_worth = invest.networth();
    cout << "After advancing time, your investment account worth is now: $" << net_worth << endl;
    cout << "\n\n";
}

void report(Account &account, Invest &invest, Client &client){
    ofstream report;
    report.open("reports.txt");
    report << fixed << setprecision(2);
    report << "============KIAgrowTm*==============\n\n\n";
    report << "Client Info(s)...\n";
    report << "Name: " << client.getName() << endl;
    report << "Age: " << client.getAge() << endl;
    report << "Address: " << client.getAddress() << endl;
    report << "Nationality: " << client.getNationality() << endl;
    report << "\n\n";
    report << "Bank Account Info(s)...\n";
    report << "Account Number: " << account.getAccountNumber() << endl;
    report << "Balance: $" << account.getBalance() << endl;
    report << "\n\n";
    report << "Bank Account Statements...\n";
    report << account.getStatement();
    report << "\n\n";
    report << "Investment Account Info...\n";
    report << "Available to Trade: $" << invest.getAvailableToTrade() << endl;
    report << "Investment Worth: $" << invest.networth() << endl;
    report << "Trade Histories...\n";
    report << invest.getTradeHistory();
    report << "\n\n";
    report << "From $1,000 initial deposit, your total net worth is: $" << account.getBalance() + invest.networth() << endl;
    report << "Thank you for using KIAgrowTm* Investment Bank Simulator by Alwalid Kiawu!\n";

    report.close();

}

void outro(Account &account, Invest &invest){
    cout << fixed << setprecision(2);
    cout << "Thank you for using KIAgrowTm* Investment Bank Simulator by Alwalid Kiawu!\n";
    cout << "At the end of the simulation, your investment account worth is: $" << invest.networth() << endl;
    cout << "Your bank account balance is: $" << account.getBalance() << endl;
    cout << "Your total net worth is: $" << account.getBalance() + invest.networth() << endl;
    cout << "We hope you enjoyed the experience and learned something about investing in stocks.\n";
    cout << "Goodbye!\n";
}
