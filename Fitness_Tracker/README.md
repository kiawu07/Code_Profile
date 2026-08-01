# FITTalis Fitness Tracker

A command-line fitness tracker built in C++. Users can create their fitness profile and log workouts completed,
generate the amount of calories they burned based on their weight and duration of the workout,
get meal recommendations based on their goals along with the micros in the food, keep track of their PRs and their workout history.

## Features

- **Workout Profile** — client personal info, goal-based
- **Calorie Counter** — uses MET to calculate the amount of calories burned from an activity
- **Meal Recommendation** — uses user-defined goals to recommend a wide range of meals for their goals with their micros
- **Personal Records** — keeps track of user's personal bests to see their progress.
- **Advancing** — an advancing day feature to reset user activities(but saves them), to simulate actual calorie outake
- **User Data** — User personal data, workout logs, etc are stored in (`info.txt`)

## Getting Started

### Prerequisites
- A C++ compiler supporting C++14 or later (e.g. `g++`)

### Build & Run
```bash
git clone https://github.com/kiawu07/Code_Profile.git
cd Fitness_Tracker
make
./final
```

Or manually:
```bash
g++ -std=c++14 finalpro.cpp node.cpp list.cpp user.cpp -o final
./final
```

## Project Structure
├── finalpro.cpp # program entry point, menu loop
├── user.hpp/.cpp # User class — personal info
├── node.hpp/.cpp # Node class — Workout Info
├── list.hpp/.cpp # Linked List class — All workout data and operations
├── food.csv/gains.csv/lose.csv # Meals data
├── mets.csv # Activities and mets data
├── info.txt # User data, and activities log history
├── credits.txt # Citations/credits

## Design Decisions

A few things worth calling out, since they weren't obvious on the first pass:

- **Using METs to calculate calories burned from workouts** Used the metabolic equivalent of each task (MET) to calculate
  calories burned so that it takes the user's weight and duration into consideration for accurate calculation.
- **Having different data for food** Used gain.csv and lose.csv separately so that when the user wants to gain weight
  meals in gain.csv are recommended and vice versa.

## Known Limitations / Future Improvements

- No calculation for calorie intake from food.
- Limited amount of food/exercises to log or recommend. 

## Author
Alwalid Kiawu and Isaac Romano — built as a final project for Data Structures strengthening
(OOP, data structures, file handling) at the end of freshman year.
