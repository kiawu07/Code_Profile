/*
Authour: Alwalid Kiawu
Date: April 22,2026 2:43 PM
Title: Header file for Node class(Final Project)
*/
#ifndef _NODE_H_
#define _NODE_H_
#include <string>
using namespace std;
class Node{

    private:
        string workout;
        int duration;
        Node * next;

    public:
        Node(string a_workout, int time);

        string getName();

        int getDuration();

        Node* getNext();

        void setNext(Node * new_next);
};
#endif