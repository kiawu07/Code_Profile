"""
ALwalid Kiawu, 8/2/2026, 11:11AM
Invest Class
"""

import random
from dataclasses import dataclass
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
    value: float

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

        with open('data/stocks.csv', 'r') as input_file:

            input_file.readline()  # Skip the header line
            lines = input_file.readlines()

            for line in lines:
                data = line.strip().split(',')
                self.stocks.append(Stock(data[0], data[1], float(data[2])))

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
            raise InvalidQuantityException("Quantity must be greater than 0 or -1 to sell all")

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
        for stock in self.stocks:
            percentage = random.randint(-5,5)
            stock.value += stock.value * (percentage/100)
            if stock.value < 0:
                stock.value = 1.0

        #putting the stock which has been bought in history list
        record = {"Day":self.day}
        for h in self.holdings:
            record[h.name] = self.get_stock_value(h.symbol)
        self.history.append(record)



        
    

    

        




    

        




