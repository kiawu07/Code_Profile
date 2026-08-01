#ifndef USER_HPP
#define USER_HPP

#include <string>
using namespace std;

class User {
    private:
        string name;
        int age;
        double height;
        double weight;
        double weight_goal;
        float calories_burnt;

    public:

        User(string n, int a, double h, double w, double wg);

        void setName(string n);
        void setAge(int a);
        void setHeight(double h);
        void setWeight(double w);
        void setWeightGoal(double wg);

        string getName();
        int getAge();
        double getHeight();
        double getWeight();
        double getWeightGoal();
        float getCalBurnt();

        void addCalories(int c);
        void resetCal();
        double calculateBMI();
        void displayInfo();

};

#endif