#include <iostream>
#include "user.hpp"
using namespace std;

User::User(string n, int a, double h, double w, double wg) {
    name = n;
    age = a;
    height = h;
    weight = w;
    weight_goal = wg;
    calories_burnt = 0;
}

void User::setName(string n) {
    name = n;
}


void User::setAge(int a) {
    age = a;
}
void User::setHeight(double h) {
    height = h;
}
void User::setWeight(double w) {
    weight = w;
}
void User:: setWeightGoal(double wg) {
    weight_goal = wg;
}

string User::getName() {
    return name;
}


int User::getAge() {
    return age;
}
double User::getHeight() {
    return height;
}
double User::getWeight() {
    return weight;
}
double User::getWeightGoal() {
    return weight_goal;
}
float User::getCalBurnt() {
    return calories_burnt;
}

void User::addCalories(int c) {
    calories_burnt += c;
}
void User::resetCal() {
    calories_burnt = 0;
}

double User::calculateBMI() {
    return ((weight / (height * height)));
}

void User::displayInfo() {
    cout << "Name: " << name << endl;
    cout << "Age: " << age <<" years"<< endl;
    cout << "Height: " << height <<" meters"<< endl;
    cout << "Weight: " << weight <<" kilograms"<<endl;
    cout << "Weight Goal: " << weight_goal << " kilograms"<< endl;
    cout << "Calories Burnt: " << calories_burnt << endl;
    cout << "BMI: " << calculateBMI() << endl;
}
