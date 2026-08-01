# KIAgrowTm* Investment Bank Simulator

A command-line banking and investment simulator built in C++. Users can create an account, 
deposit/withdraw funds, transfer money into an investment account, buy and sell simulated 
stocks, and advance time to watch a randomized market affect their portfolio.

## Features

- **Account creation** — client info, auto-generated account number, PIN-based authentication
- **Banking** — deposit and withdraw funds from a checking account
- **Investing** — transfer funds to/from an investment account, buy and sell stocks
- **Market simulation** — an "advance time" feature that randomly moves stock prices day-to-day
- **Transaction history & reporting** — a running trade log, plus an exportable session report (`reports.txt`)
- **Input validation and custom exceptions** — invalid PINs, insufficient funds, invalid quantities, 
  and out-of-range selections are all handled via dedicated exception types rather than generic error codes

## Getting Started

### Prerequisites
- A C++ compiler supporting C++14 or later (e.g. `g++`)

### Build & Run
```bash
git clone https://github.com/kiawu07/Code_Profile.git
cd bank_simulator
make
./bank_simulator
```

Or manually:
```bash
g++ -std=c++14 main.cpp invest.cpp account.cpp client.cpp -o bank_simulator
./bank_simulator
```

## Project Structure
├── main.cpp # program entry point, menu loop
├── client.hpp/.cpp # Client class — personal info
├── account.hpp/.cpp # Account class — banking operations
├── invest.hpp/.cpp # Invest class — stocks, holdings, market simulation
├── stock.hpp # Stock struct — market listing data
├── holding.hpp # Holding struct — a user's owned shares
├── exceptions.hpp # custom exception types
├── stocks.csv # starting market data
└── reports.txt # users' info, bank and trade histories
└── test_invest.cpp # unit tests for the Invest class

## Design Decisions

A few things worth calling out, since they weren't obvious on the first pass:

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
  invisible fraction of a share behind. A `-1` sentinel value lets users sell an exact holding 
  in full, without relying on a rounded number.

## Known Limitations / Future Improvements

- No persistence — accounts and holdings reset each run
- PINs are stored as plain integers, not securely hashed (fine for a simulator, not for production)
- Account numbers are derived from the client's name, not guaranteed unique in a real-world sense

## Author
Alwalid Kiawu — built as a self-directed summer project to strengthen C++ fundamentals 
(OOP, exception handling, unit testing) ahead of sophomore year.
