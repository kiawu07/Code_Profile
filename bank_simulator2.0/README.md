# KIAgrowTm* Investment Bank Simulator2.0

A Streamlit GUI banking and investment simulator built in Python.  Users can create an account,
deposit/withdraw funds, transfer money into an investment account, buy and sell simulated 
stocks, each with separate volatilities, advance time to watch a randomized market affect their portfolio,
and view their portfolio analysis in tables and charts.

## Features

- **Account creation** — client info, auto-generated account number, PIN-based authentication
- **Banking** — deposit and withdraw funds from a checking account
- **Investing** — transfer funds to/from an investment account, buy and sell stocks
- **Market simulation** — an "advance time" feature that randomly moves stock prices day-to-day
- **Portfolio Analytics** - line charts, pie charts, and tables visualize portfolio movements 
- **Transaction history & reporting** — a running trade log, plus an exportable session report (`reports.txt`)
- **Input validation and custom exceptions** — invalid PINs, insufficient funds, invalid quantities, 
  and out-of-range selections are all handled via dedicated exception types rather than generic error codes

## Getting Started

### Prerequisites
- Python
- Streamlit
- Matplotlib

### Build & Run
```bash
git clone https://github.com/kiawu07/Code_Profile.git
cd bank_simulator2.0
streamlit run app.py or py -m streamlit run app.py
```

## Project Structure
├── data
    └──info.txt # output file for user info(s)
    └──logo.png # logo image for GUI
    └──stocks.csv # file with stocks, their values and volatilities
├── models
    └──account.py # Account class - banking operations
    └──client.py # Client class - personal info
    └──invest.py # Invest Class - investment operations
├──app.py # main streamlit program
├──exceptions.py # custom exceptions types
├──requirements.txt # requirements to run the program

## Design Decisions

- **Holdings track cost basis separately from current market value.** A `Holding` stores what 
  the user *paid* and how many shares they own; current worth is always recalculated live against 
  the market, rather than stored — since a stored "current value" would go stale the moment the 
  market moves.
- **Exceptions over generic error codes.** Each failure mode (`InvalidPINException`, 
  `InsufficientFundsException`, `InsufficientSharesException`, etc.) is its own type, letting calling 
  code react differently depending on what actually went wrong — and making the transaction logic 
  independently unit-testable, since it never touches `cin`/`cout` directly.
- **Floating-point precision in "sell all."** Since displayed share quantities are rounded for 
  readability, comparing a user-typed amount against the true stored value could leave a tiny, 
  invisible fraction of a share behind. A 'sell all' option lets users sell an exact holding 
  in full, without relying on a rounded number.
  -**Unique Stock Volatilities** Instead of all stocks' values changing randomly, each stock has a volatility.
  Higher volatility means higher risk and reward, simulating an actual stock market. 

  ## Known Limitations / Future Improvements

- PINs are stored as plain integers, not securely hashed (fine for a simulator, not for production)
- Account numbers are derived from the client's name, not guaranteed unique in a real-world sense
- Market news doesn't reflect the change in the values of the stocks.

## Author
Alwalid Kiawu — built as a self-directed summer project to strengthen Python and GUI programming fundamentals 
(GUI Programming, OOP, exception handling) ahead of sophomore year.
