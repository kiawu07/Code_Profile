/*
Authour: Alwalid Kiawu
Date: Feb. 28,2026 9:56 PM
Title: Person class
	
*/
#include <iostream>
#include <string>
using namespace std;

class Person{

    private:
    string user_name;

    public:
//defining constructor
    Person(string name){
        user_name = name;
    }

// defining greet function
    void greet(){
        cout <<"Wassup "<<user_name<<" Hope your day is rock on!!"<<endl;
    }

};

int main(){
//requesting user's name
    string name;
    cout <<"Enter your name for a lovely greet:)"<<endl;
    getline(cin,name);

//creating instances of the Person class
    Person* someone = new Person(name);
    someone ->greet();

    delete someone;

    return 0;
}

