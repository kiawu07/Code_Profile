"""
ALwalid Kiawu, 8/2/2026, 11:11AM
Account Class
"""


class Account():

    def __init__(self, client, PIN):
        name = client.get_name()
        self.PIN = PIN
        self.balance = 0
        self.statement = ""

        #hash funtion to generate account number
        str_acc_num = ""
        for letter in name:
            if len(str_acc_num) >= 7:
                break
            str_acc_num += str(ord(letter.lower()))

        while len(str_acc_num) < 7:
            str_acc_num += '0'

        self.account_number = int(str_acc_num[:7])

    def display_info(self):
        print(f"Account Number: {self.account_number}")
        print(f"Balance: ${self.balance}")

    def deposit(self, amount:float):
        self.balance += amount
        self.statement += "You deposited " + str(amount) + " to your account"

    def withdraw(self, amount:float):
        self.balance -= amount
        self.statement += "You withdrew " + str(amount) + " from your account"

    def get_statement(self):
        return self.statement

    def get_account_num(self):
        return self.account_number

    def get_balance(self):
        return self.balance

    def get_PIN(self):
        return self.PIN



    









    