/*Header file for client class
Alwalid Kiawu, July 2, 2026, 5:10 PM
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

using namespace std;


class Client{

    private:
        string name;
        int age;
        string address;
        string nationality;

    public:
        Client(string name, int age, string address, string nationality);

        //Getters
        string getName();
        int getAge();
        string getAddress();
        string getNationality();
        void displayClientInfo();
};



#endif