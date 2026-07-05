/*Implementation of the client class*/
#include "client.hpp"
#include <iostream>
using namespace std;

Client::Client(string name, int age, int SSN, string address, string nationality){
    this->name = name;
    this->age = age;
    this->SSN = SSN;
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

int Client::getSSN(){
    return SSN;
}

string Client::getAddress(){
    return address;
}

string Client::getNationality(){
    return nationality;
}