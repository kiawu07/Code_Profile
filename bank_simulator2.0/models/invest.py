"""
ALwalid Kiawu, 8/2/2026, 11:11AM
Invest Class
"""

import random
from dataclasses import dataclass
from pathlib import Path
from exceptions import (
    InsufficientFundsException,
    InvalidChoiceException,
    InsufficientSharesException,
    InvalidPINException,
    InvalidQuantityException,
    NoHoldingsException
)

@dataclass
class Stock:
    name : str
    symbol: str
    previous_val: float
    value: float
    volatility: int

@dataclass
class Holding:
    name : str
    symbol : str
    quantity : float
    cost_basis : float

class Invest():

    def __init__(self):
        self.available_to_trade = 0
        self.trade_history = ""
        self.stocks = []
        self.holdings = []
        self.day = 1
        self.history = []
        self.news = [
            "Technology stocks gain as AI demand continues to rise.",
            "Markets remain cautious ahead of new economic data.",
            "Investors show increased interest in renewable energy.",
            "Consumer spending strengthens across major markets.",
            "Markets experience a slight downturn as investors take profits.",
            "Major technology companies report strong quarterly results."
            ]
        self.current_news = None

        BASE_DIR = Path(__file__).parent.parent
        stocks_path = BASE_DIR / "data" / "stocks.csv"

        with open(str(stocks_path), 'r') as input_file:

            input_file.readline()  # Skip the header line
            lines = input_file.readlines()

            for line in lines:
                data = line.strip().split(',')
                self.stocks.append(Stock(data[0], data[1], float(data[2]),float(data[2]), int(data[3])))

    def transfer_to_trade(self, account, amount, PIN):
        if account.get_PIN() != PIN:
            raise InvalidPINException("Inputed PIN is incorrect")

        if account.get_balance() < amount:
            raise InsufficientFundsException("Insufficient funds in the bank account")

        self.available_to_trade += amount
        account.withdraw(amount)
        self.trade_history += f"Transferred ${amount:.2f} to trading account\n"

        return self.available_to_trade

    def transfer_to_bank(self, account, amount, PIN):
        if account.get_PIN() != PIN:
            raise InvalidPINException("Inputed PIN is incorrect")
        
        if self.available_to_trade < amount:
            raise InsufficientFundsException("Insufficient funds in the Investment Account")

        self.available_to_trade -= amount
        account.deposit(amount)
        self.trade_history += f"Transferred ${amount:.2f} to bank account\n"

    def get_stock_value(self, symbol):
        for Stock in self.stocks:
            if Stock.symbol == symbol:
                return Stock.value

        return 0

    def get_percent_change_in_stock_val(self,symbol):
        for Stock in self.stocks:
            if Stock.symbol == symbol:
                change =  (((Stock.value - Stock.previous_val)/Stock.previous_val)*100)
                if change < 0:
                    return f"{change:.1f}%"
                else:
                    return f"+{change:.1f}%"

        
        return 0
            

    def execute_buy(self, stock_index, dollar_amount):
        if stock_index < 0 or stock_index >= len(self.stocks):
            raise InvalidChoiceException("Invalid stock index")
        if dollar_amount > self.available_to_trade:
            raise InsufficientFundsException("Insufficient funds to execute buy")

        quantity = dollar_amount / self.stocks[stock_index].value
        stock_purchased = Holding(self.stocks[stock_index].name, self.stocks[stock_index].symbol, quantity, dollar_amount )
        self.holdings.append(stock_purchased)
        self.trade_history += f"You bought {quantity:.4f} shares of {self.stocks[stock_index].name} ({self.stocks[stock_index].symbol}) for $ {dollar_amount:.2f}\n"
        self.available_to_trade -= dollar_amount

        return quantity

    def execute_sell(self, stock_index, quantity):
        if len(self.holdings) == 0:
            raise NoHoldingsException("No shares to sell")

        if stock_index < 0 or stock_index >= len(self.holdings):
            raise InvalidChoiceException("Invalid stock index")

        if quantity == 0 or quantity <= -2:
            raise InvalidQuantityException("Quantity must be greater than 0")

        if quantity > self.holdings[stock_index].quantity:
            raise InsufficientSharesException("Insufficient quantity of shares to sell")

        curr_price = self.get_stock_value(self.holdings[stock_index].symbol)
        if quantity == -1:
            proceeds = self.holdings[stock_index].quantity * curr_price
            self.trade_history += f"You sold all of {self.holdings[stock_index].name} ({self.holdings[stock_index].symbol}) for ${proceeds:.2f}\n"
            self.available_to_trade += proceeds
            del self.holdings[stock_index]
        else:
            proceeds = curr_price * quantity
            self.holdings[stock_index].quantity -= quantity
            self.trade_history += f"You sold {quantity:.4f} shares of {self.holdings[stock_index].name} ({self.holdings[stock_index].symbol}) for ${proceeds:.2f}\n"
            self.available_to_trade += proceeds

        return proceeds

    def networth(self):
        tot_val = self.available_to_trade
        for holding in self.holdings:
            quantity = holding.quantity
            symbol = holding.symbol
            value = self.get_stock_value(symbol)
            tot_val += quantity * value

        return tot_val

    def get_trade_history(self):
        return self.trade_history

    def get_available_to_trade(self):
        return self.available_to_trade

    def advance(self):
        self.day += 1
        self.current_news = random.choice(self.news)
        for stock in self.stocks:
            stock.previous_val = stock.value 
            percentage = random.randint(-1*stock.volatility, stock.volatility)
            stock.value += stock.value * (percentage/100)
            if stock.value < 0:
                stock.value = 1.0

        #putting the stock which has been bought in history list
        record = {"Day":self.day}
        for h in self.holdings:
            record[h.name] = self.get_stock_value(h.symbol)
        record["Total Portfolio Value"] = self.networth()
        self.history.append(record)

    def info_file(self,account,client):

        BASE_DIR = Path(__file__).parent.parent
        info_path = BASE_DIR / "data" / "info.txt"

        with open(str(info_path),'w') as output_file:
            output_file.write("KIAGrowTM* Investment Bank Simulator\n\n")
            output_file.write("User Report\n\n")
            output_file.write("=======Personal Info==========\n")
            output_file.write(f"Name: {client.get_name()}\n")
            output_file.write(f"Age: {client.get_age()}\n")
            output_file.write(f"Address: {client.get_address()}\n")
            output_file.write(f"Nationality: {client.get_nationality()}\n\n")
            output_file.write("=======Bank Account Info========\n")
            output_file.write(f"Account Number: {account.get_account_num()}\n")
            output_file.write(f"BALANCE: {account.get_balance()}\n")
            output_file.write("STATEMENTS:\n")
            output_file.write(f"{account.get_statement()}\n\n")
            output_file.write("=======Investment Account Info========\n")
            output_file.write(f"Available to trade: {self.get_available_to_trade()}\n")
            output_file.write(f"Investment Net Worth: {self.networth()}\n")
            output_file.write("TRADE HISTORY:\n")
            output_file.write(f"{self.get_trade_history()}\n\n")
            total = self.networth() + account.get_balance()
            output_file.write(f"From $1,000.00 initial deposit, your total net worth is: ${total:,.2f}\n")
            output_file.write("Thanks for using KIAgrowTm* Investment Bank Simulator\n\n\n\n")
            output_file.write("Made and Designed by: Alwalid Prince Kiawu")



    



        
    

    

        




    

        




