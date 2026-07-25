/*Implementation of the client class*/
#include "client.hpp"
#include <iostream>
using namespace std;

Client::Client(string name, int age, string address, string nationality){
    this->name = name;
    this->age = age;
    this->address = address;
    this->nationality = nationality;
}

//Getters
string Client::getName(){
    return name;
}

int Client::getAge(){
    return age;
}

void Client::displayClientInfo(){
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Address: " << address << endl;
    cout << "Nationality: " << nationality << endl;
}

string Client::getAddress(){
    return address;
}

string Client::getNationality(){
    return nationality;
}