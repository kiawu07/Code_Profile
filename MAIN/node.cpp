/*
Authour: Alwalid Kiawu
Date: April 22,2026 2:44 PM
Title: Implementation file for Node class(Final Project)
*/
#include <iostream>
#include <string>
#include "node.hpp"
using namespace std;

Node::Node(string a_workout,int time){
    workout = a_workout;
    duration = time;
    next = nullptr;

}

string Node::getName(){
    return workout;
}

int Node::getDuration(){
    return duration;
}

Node* Node::getNext(){
    return next;
}

void Node::setNext(Node * new_next){
    next = new_next;
}