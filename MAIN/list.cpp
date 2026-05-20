/*
Authour: Alwalid Kiawu
Date: April 22,2026 2:44 PM
Title: Implementation file for LinkedList class(Final Project)
*/
#include <iostream>
#include <string>
#include "node.hpp"
#include "list.hpp"
#include <vector>
using namespace std;

    LinkedList::LinkedList(){
        first = nullptr;
        count = 0;
    }

    //Destructor
    LinkedList::~LinkedList(){
        Node * current = first;
        while(current != nullptr) {
            Node * temp = current;
            current = current->getNext();
            delete temp;
        }
        first = nullptr;
        count = 0;
    }

    bool LinkedList::add_one(string name, int duration){
        Node * new_task = new Node(name, duration);
        if(new_task == nullptr){
            return false;
        }
        if(count == 0){
            first = new_task;//making the first point to the address of the first item if it is the first item
            count++;
        }else{
            new_task->setNext(first);
                first = new_task;
                count++;
            }
            return true;
        }

    string LinkedList::get_exercises(){
        string exercises;
        //Special case if no task in list
        if(count == 0){
            return " ";
        }
        //start transversing
        Node * temp = first;
        while(temp != nullptr){
            string name = temp->getName();
            int duration = temp->getDuration();
            exercises += name + " for: " + to_string(duration) + " minutes";
            exercises += "\n";
            temp = temp->getNext();   
        } 
    return exercises;
    }

    vector<int> LinkedList::get_durations(){
        vector<int> dura_vect;
        string exercises;
        //Special case if no task in list
        if(count == 0){
            cout<<"Workout List empty!!"<<endl;
            return dura_vect;
        }
        //start transversing
        Node * temp = first;
        while(temp != nullptr){
            int duration = temp->getDuration();
            dura_vect.push_back(duration);
            temp = temp->getNext();
        } 
    return dura_vect;
    }


    void LinkedList::reset(){
        //will delete all nodes
        count = 0;
        while(first != nullptr){
            Node * temp = first;
            first = first->getNext();
            delete temp;
        }
    }

    int LinkedList::getCount(){
        return count;
    }
    
        