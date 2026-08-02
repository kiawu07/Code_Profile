"""
ALwalid Kiawu, 8/2/2026, 10:52AM
Exception class(Inherited from python's built-in exceptions)
"""

class InsufficientFundsException(Exception):

    def __init__(self,message):
        super().__init__(message)

class InvalidChoiceException(Exception):

    def __init__(self,message):
        super().__init__(message) 

class InsufficientSharesException(Exception):

    def __init__(self,message):
        super().__init__(message)

class InvalidPINException(Exception):

    def __init__(self,message):
        super().__init__(message)

class InvalidQuantityException(Exception):

    def __init__(self, message):
        super().__init__(message)

class NoHoldingsException(Exception):

    def __init__(self, message):
        super().__init__(message)
