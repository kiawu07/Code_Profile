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
using namespace std;

void intro();
Client create_client();
void main_menu();
void dashboard(Account account, Invest invest, Client client);
void transfer_money(Account &account, Invest &invest);
void invest_menu(Invest &invest, Account &account);
void advance();
void outro();

int main(){
    srand(time(0));


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
    cout << "For the purpose of this simulator, we will deposit $1,000 in your account and
            see how much you can grow it\n";
    account.deposit(1000);
    cout << "Transfer money to you investment account and try to grow it\n";
    dashboard(account, invest, client);
    
    bool running = true;

    while(running){
        main_menu();

        int input;

        while(!(cin>>input)){
            cout << "Please enter a valid input \n";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch(input){
            case 1:{//transfer money to/from investing account

                break;

            }

            case 2:{//invest in stocks

                break;
            }

            case 3:{//Advance 

                break;
            }

            case 4:{//outro
                running = false;
                break;
            }

            default{
                cout << "Please enter a valid input from 1-4!!\n";
            }
        }
    }

    return 0;
}

//functions defination
void intro(){
    cout << "Welcome to the Investment Bank Simulator by Alwalid Kiawu!\n";
    cout << "This program simulates a simple banking system where clients can create accounts, deposit and withdraw money, and invest in stocks.\n";
    cout << "You will be able to create an account, transfer money to/from your investing account, invest in stocks, and advance time to see how your investments perform.\n";
    cout << "Let's get started!\n";
}

Client create_client(){
    // Implementation for creating a client
    cout << "Enter your informations to create you account to start investing!\n";
    string name;
    cout << "Enter your full name\n";
    cin>>name;
    int age;
    cout << "Enter your age\n";
    while(!(cin>>age)){
        cout << "Please enter a valid age!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    string address;
    cout << "Enter your address\n";
    cin>>address;
    string nationality;
    cout << "Enter your nationality\n";
    cin>>nationality;
    cout << "All your details have been saved!!\n";
    Client client(name, age, address, nationality);
    return client;
}

void dashboard(Account account, Invest invest, Client client){
    cout << "See below our account informations\n";
    client.displayClientInfo();
    cout << "see below your account informations\n";
    account.displayAccountInfo();
    cout << "Available to Trade in Investment Account: " << invest.getAvailableToTrade() << endl;
}

void main_menu(){
    cout << "Main Menu:\n";
    cout << "Enter...:\n"
    cout << "1. Transfer Money\n";
    cout << "2. Invest in Stocks\n";
    cout << "3. Advance Time\n";
    cout << "4. Exit\n";
}

void transfer_money(Account &account, Invest &invest){
    // Implementation for transferring money
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
    
}

void invest_menu(Invest &invest, Account &account){
    // Implementation for investing menu
    cout << "Enter 1, to buy stocks\n";
    cout << "Enter 2, to sell some of your holdings\n";
    int choice;
    while(!(cin>>choice) || (choice != 1 && choice != 2)){
        cout << "Please enter a valid choice (1 or 2)!!!\n";
        cin.clear();
        cin.ignore(1000,'\n');
    }
    //Continue with the implementation for buying and selling stocks based on the user's choice
    
}

void advance(){
    // Implementation for advancing time
}

void outro(){
    cout << "Thank you for using the Investment Bank Simulator by Alwalid Kiawu!\n";
}
