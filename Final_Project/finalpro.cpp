/*
Authour: Alwalid Kiawu and Isaac Romano
Date: April 22,2026 2:44 PM
Title: FITalis (Final Project)

Citations: This project relied heavily on secondary sources of data for 
            uncovering the micros in food and the METs for different workouts.
            Please see file credits.txt for more detailed citations and credits.

            Texts art made with help from : ASCII Art Generator(Link in crdits.txt)

*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>
#include "node.hpp"
#include "list.hpp"
#include "user.hpp"
using namespace std;

//useful functions here

//function to display the Intoduction
void printbanner(){
    cout << "\n\n";
    cout << R"(
 _______ ___________________________ _______  _       _________ _______ 
(  ____ \\__   __/\__   __/\__   __/(  ___  )( \      \__   __/(  ____ \
| (    \/   ) (      ) (      ) (   | (   ) || (         ) (   | (    \/
| (__       | |      | |      | |   | (___) || |         | |   | (_____ 
|  __)      | |      | |      | |   |  ___  || |         | |   (_____  )
| (         | |      | |      | |   | (   ) || |         | |         ) |
| )      ___) (___   | |      | |   | )   ( || (____/\___) (___/\____) |
|/       \_______/   )_(      )_(   |/     \|(_______/\_______/\_______)
                                                                        

    )";
    cout << "\n\n";
}


void Intro(){
    cout<<"Welcome to FITTalis. Your personal fitness partner\n"
        "We are a fitness plantform designed by Alwalid and Isaac to help you at every step of your fitness journey\n"
        "Please follow the instructions carefully to build your personal profile and start achieving your fitness goals\n"<<endl;  
    }

//function to great user
string Greet(string name, int curr_weight, int desired_weight){
    int index = name.find(" ");
    string substr = name.substr(0, index);
    cout<<"Welcome, "<<substr<<" all your information have been saved"<<endl;
    cout<<"You are just a step away from achieving your fitness goals"<<endl;
    if(curr_weight > desired_weight){
        cout << "It seems like you would like to LOSE some weight!!" <<endl;
        cout << "Loosing weight takes time, dedication, and stern commitment,\n"
        "But, you have come to the right place, the goal is just to stay in a CALORIE DEFICIT!!"<<endl;
    }
    else if(curr_weight == desired_weight) {
        cout << "It seems like you would like to MAINTAIN your weight!!" << endl;
        cout << "Maintaining weight is a great goal which takes dedication, and great eating,\n"
        "But you need to make sure you consume as much calories as you burn to MAINTAIN your weight!!" << endl;
    }

    
    else{
        cout << "It seems like you would like to GAIN some weight!!" <<endl;
        cout << "Gaining weight takes time, dedication, and great eating,\n"
        "But, you have come to the right place, the goal is just to stay in a CALORIE SURPLOUS!!"<<endl;
    }
    cout<<"Select one of the options to start maximizing your fitness potential!!!"<<endl;
    return substr;
}

//function to display main menu. Should display after user create their profile
void MainMenu(){
    cout<<"Please enter: \n"
        "1 to log a new exercise\n"
        "2 to view your log records\n"
        "3 to view your personal profile\n"
        "4 to view some curated food for your fitness goals\n"
        "5 to save your infos in a file and progress to the next day\n"
        "6 to exit"<<endl;
}

//function to open a file and get two vectors of exercises and mets
void mets(vector<string> &workouts, vector<float> &mets){
    //openning file
    ifstream infile;
    infile.open("mets.csv");
    
    //reading first unwanted line(header);
    string line;
    getline(infile, line);

    //getting datas
    while(getline(infile, line)){
        int pos = line.find(',');
        string workout = line.substr(0, pos);
        float met = stof(line.substr(pos+1));
        workouts.push_back(workout);
        mets.push_back(met);
    }
    infile.close();
}

//should take a vector of user's exercise times, and print the user's PRs and records;
void record(vector<int> durations_vect, string exercises){
    //string PRs;
    int max = durations_vect[0];
    int sum = durations_vect[0];
    //finding maximum value in vector
    for(unsigned int i = 1; i<durations_vect.size(); i++){
        if(durations_vect[i] > max){
            max = durations_vect[i];
        }
        sum += durations_vect[i];
    }
    cout<<"Printing records..."<<endl;
    cout<<endl;
    cout<<"You have exercised for a total of "<<sum<<" minutes "<<" doing "<<durations_vect.size()<<" workout(s)!!"<<endl;
    cout<<"You PR for longest time spent exercising is... "<<max<<" minutes"<<endl<<endl;
    cout<<"Workouts Completed so far: "<<endl;
    cout<<exercises<<endl;
}

//function to filter user input for workouts
string filter(string a_workout){
    //removing non alphabetic characters
    string filtered;
    for(char c : a_workout){
        if(isalpha(c)){
            filtered += tolower(c);
        }
    }
return filtered;
}

//calorie counter function
float calorie_counter(string exercise, int minutes, int weight, vector<float> all_mets, vector<string> all_workouts){
    int index = -1;
    unsigned int i = 0;
    bool found = false;
    while(i<all_workouts.size() && !found){
        if(exercise == all_workouts[i]){
            index = i;
            found = true;
        }
        i++;
    }
    if(index == -1){
        throw runtime_error("Workout entered NOT found, please enter the name of the workout correctly");
    }else{
    float MET = all_mets[index];
    float burned = MET * weight * (minutes/60.0);
    return burned;
    }
}

//funtion to display exercises(should take all available aorkouts and display them)
void displayWorkouts(vector<string> all_workouts){
    for(unsigned int i=0; i<all_workouts.size(); i++){
        cout<<all_workouts[i]<<" "<<", ";
        if((i+1) % 5 == 0){
            cout<<endl;
        }
    }
}

//funtion to write in a file
void write(string file, User user, string history){
    ofstream output;
    output.open(file);
    output << "\n\n";

    output << R"(
 ______ _____ _______ _______    _ _     
 |  ____|_   _|__   __|__   __|  | (_)    
 | |__    | |    | |     | | __ _| |_ ___ 
 |  __|   | |    | |     | |/ _` | | / __|
 | |     _| |_   | |     | | ()_| | | \__ \
 |_|    |_____|  |_|     |_|\__,_|_|_|___/
    )";
    output << "\n\n";

    //writing infos
    output << "Name: " << user.getName() << endl;
    output << "Age: " << user.getAge() <<" years"<< endl;
    output << "Height: " << user.getHeight() <<" meters"<< endl;
    output << "Weight: " << user.getWeight() <<" kilograms"<<endl;
    output << "Weight Goal: " << user.getWeightGoal() << " kilograms"<< endl;
    output << "BMI: " << user.calculateBMI() << endl;
    output << endl;

    //writing records
    output << "======Exercises completed so far=====" << endl;
    output << history;
    output.close();
}

//function to recommend food for user
void food_curate(User user){
    ifstream infile;
    srand(time(0));
    if(user.getWeight() < user.getWeightGoal()){
        //want to gain
        infile.open("gain.csv");
        string line;
        getline(infile, line);
        vector<string> gains;
        while(getline(infile, line)){
            gains.push_back(line);
            }
    cout << "Since you want to GAIN weight, here are couple of recommended food!!" <<endl;
    cout << endl;
    int pre = -1;
    for(int i=1; i<3; i++){
        int num = rand() % gains.size();
        while(num == pre){
        num = rand() % gains.size();
        }
        pre = num;
        string line = gains[num];
        //tring to find commas
        stringstream ss(line);
        string part;
        vector<string> sub_vect;
        while(getline(ss,part,',')){
            sub_vect.push_back(part);
        }
        
        cout << "Name: " << sub_vect[0] <<"\n"
             << "Mass: " << sub_vect[2] <<" grams \n"
             << "Calories: " << sub_vect[3] << "\n"
             << "Protein: " << sub_vect[4] << " grams\n"
             << "Fat: " << sub_vect[5] << " grams\n"
             << "Fiber: " << sub_vect[7] << " grams\n"
             << "Carbs: " << sub_vect[8] << " grams\n" << endl;
        }
        infile.close();
    }
    
    else{
        //want to loose
        infile.open("lose.csv");
        string line;
        getline(infile, line);
        vector<string> loose;
        while(getline(infile, line)){
            loose.push_back(line);
            }
    cout << "Since you want to LOSE/ MAINTAIN weight, here are couple of recommended food!!" <<endl;
    cout << endl;
    int pre = -1;
    for(int i=1; i<3; i++){
        int num = rand() % loose.size();
        while(num == pre){
        num = rand() % loose.size();
        }
        pre = num;
        string line = loose[num];
        //tring to find commas
        stringstream ss(line);
        string part;
        vector<string> sub_vect;
        while(getline(ss,part,',')){
            sub_vect.push_back(part);
        }
        
        cout << "Name: " << sub_vect[0] <<"\n"
             << "Measure: " << sub_vect[1] <<" grams \n"
             << "Mass: " << sub_vect[2] <<" grams \n"
             << "Calories: " << sub_vect[3] << "\n"
             << "Protein: " << sub_vect[4] << " grams\n"
             << "Fat: " << sub_vect[5] << " grams\n"
             << "Fiber: " << sub_vect[7] << " grams\n"
             << "Carbs: " << sub_vect[8] << " grams\n" << endl;
        }
        infile.close();
    }
}

void next_day(string &history, int &day_count, User &user, LinkedList &list){
    history += "\n ==========Day " + to_string(day_count) + " ================\n\n";
    history += list.get_exercises();
    history += "Calories Burnt Today: " + to_string(user.getCalBurnt()) + "\n";
    user.resetCal();
    list.reset();
    cout<< " Exercises List reset successful"<<endl;
    day_count++;
}



int main(int argc, char* argv[]){

    if(argc < 2){
        cout<<"Please input a file name that will be used to save your info(s)"<<endl;
        exit(1);
    }



    string filename = argv[1];
    //linked list
    LinkedList list;

    printbanner();
    Intro();

    //making user class
    string username;
    cout<<"Please enter your full name"<<endl;
    getline(cin, username);

    int age;
    cout<<"Please enter your age"<<endl;
    while(!(cin>>age && age > 0)){
        cout<<"Please enter a valid age"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }

    double height;
    cout<<"Please enter your height in meters"<<endl;
    while(!(cin>>height && height > 0)){
        cout<<"Please enter a valid height"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }

    double weight;
    cout<<"Please enter your weight in kilograms"<<endl;
    while(!(cin>>weight && weight > 0)){
        cout<<"Please enter a valid weight"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }

    double weight_goal;
    cout<<"Please enter your desired weight goal in kilograms"<<endl;;
    while(!(cin>>weight_goal && weight_goal > 0)){
        cout<<"Please enter a valid weight"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }

    User client(username, age, height, weight, weight_goal);
    vector<string> available_workouts;
    vector<float> available_mets;
    mets(available_workouts, available_mets);//filling in vectors
    cout<<endl;
    string firstname = Greet(client.getName(), weight, weight_goal);

    string records;
    int day_num = 1;

    int input;

    cout << " \n\n========= Day 1 ===============\n\n";

    do{
        cout<<endl;
        MainMenu();
        while(!(cin>>input)){
            cout<<"Invalid input!!!"<<endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch(input){
            
            //log exercise
            case 1:{
                cout<<endl;
                cout<<"==============Logging New Workouts=============="<< endl << endl;
                string workout;
                cout<<"Lets log in your workout "<< firstname <<endl;
                cout<<"Please select an exercise from the menu below"<<endl;
                cout<<"Please type in the exercise name"<<endl;
                cout<<endl;
                displayWorkouts(available_workouts);
                cout<<endl;
                cin.ignore(1000, '\n');
                getline(cin, workout);
                string filtered = filter(workout);
                int duration;
                cout<<"How long was it done for in minutes"<<endl;
                while(!(cin>>duration && duration > 0)){
                    cout<<"Please enter a valid time in minutes"<<endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                float burned;
                try{
                burned = calorie_counter(filtered, duration, client.getWeight(), available_mets, available_workouts);
                list.add_one(filtered, duration);
                cout<<endl;
                cout<<"Great work!!! "<<firstname<<" "<< workout <<" for "<<duration<<" minutes"<<" burning "<<burned<<" calories\n";
                cout<<"Workout addition successfull"<<endl;
                client.addCalories(burned);
                } catch(exception &c){
                    cerr<<c.what()<<endl;
                }
                break;
            }
            //view log history
            case 2:{
                if(list.getCount() == 0){
                    cout << "You haven't saved any exercises yet as for Today!! " << firstname << endl;
                    break;
                }else{
                    cout << endl;
                    cout << "=============Workout History=============" << endl<<endl;
                    string exercises = list.get_exercises();
                    vector<int> dura_vect = list.get_durations();
                    cout << "Here are your records so far, " << firstname << endl << endl;
                    record(dura_vect,exercises);
                    cout << "Total number of calories burnt: " << to_string(client.getCalBurnt()) << endl;
                    break;
                }
            
            }
        
            //view personal profile
            case 3:{
                cout << endl;
                cout << "=============Personal Profile=============" << endl <<endl;
                client.displayInfo();
                break;
            }

            //food recommendation
            case 4:{
                cout << endl;
                cout << "=============Food Curation=============" << endl << endl;
                food_curate(client);
                break;
            }

            case 5:{
                cout << endl;
                if(list.getCount() == 0){
                    cout << "You haven't logged anything for today \n";
                    break;
                }else{
                    cout << "Your data was successfully copied in "<< filename <<endl;
                    next_day(records, day_num, client, list);
                    cout << "\n Welcome " << firstname << " to a Day " << day_num << "\n\n";
                    write(filename, client, records);
                    break;
                }

            }

            case 6:{
                cout << "Thanks for using FITTalis, Hope your enjoyed our platform" << endl;
                cout << "Don't forget to give us a 5 star review " << endl;
            }
        }

    }while(input != 6);

    return 0;
}