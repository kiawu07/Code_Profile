"""
ALwalid Kiawu, 8/2/2026, 10:52AM
Client Class
"""

class Client():

    def __init__(self, name, age, address, nationality):
        self.name = name
        self.age = age
        self.address = address
        self.nationality = nationality

    def get_name(self)->str:
        return self.name

    def get_age(self)->int:
        return self.age

    def get_address(self)->str:
        return self.address

    def get_nationality(self)->str:
        return self.nationality

    def display_info(self)->None:
        print(f"Name: {self.name}")
        print(f"Age: {self.age}")
        print(f"Address: {self.address}")
        print(f"Nationality: {self.nationality}")   