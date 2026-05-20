/*
Authour: Alwalid Kiawu
Date: April 22,2026 2:43 PM
Title: Header file for LinkedList class(Final Project)
*/
#ifndef _LinkedList_H_
#define _LinkedList_H_
#include <string>
#include "node.hpp"
#include <vector>
using namespace std;

class LinkedList{

    private:
        Node * first;
        int count;

    public:
        LinkedList();
        
        //Destructor
        ~LinkedList();

        bool add_one(string name, int duration);

        string get_exercises();

        vector<int> get_durations();

        void reset();

        int getCount();

};
#endif
