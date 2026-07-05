/*Header file for client class
Alwalid Kiawu, July 2, 2026, 5:10 PM
*/

#include <iostream>
#include <string>

#ifndef CLIENT_HPP
#define CLIENT_HPP


class Client{

    private:
        string name;
        int age;
        int SSN;
        string address;
        string nationality;

    public:
        Client(string name, int age, int SSN, string address, string nationality);

        //Getters
        string getName();
        int getAge();
        int getSSN();
        string getAddress();
        string getNationality(); 
};



#endif