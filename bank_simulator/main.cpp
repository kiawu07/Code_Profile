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
void create_account();
void main_menu();
void transfer_money(Account &account, Invest &invest);
void invest_menu(Invest &invest, Account &account);
void dashboard(Account &account, Invest &invest);
void advance();
void outro();

int main(){
    srand(time(0));


    intro();
    create_account()


    bool running = true;

    while(running){
        main_menu();

        int input;

        while(!(cin>>input)){
            cout << "Please enter a valid input \n";
            cin.clear()
            cin.ignore(1000, '\n');
        }

        switch(input){
            case 1;{//transfer money to/from investing account

            }

            case 2:{//invest in stocks

            }

            case 3:{//Advance 

            }

            case 3:{//outro
                running = false;
            }

            default{
                cout << "Please enter a valid input from 1-3!!\n";
            }
        }
    }

    return 0;
}

//functions defination

