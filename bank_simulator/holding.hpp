/*
Header file for Holding struct
ALwalid Kiawu, 7/8/2026, 9:59AM
*/

#ifndef HOLDING_HPP_
#define HOLDING_HPP_

#include <string>
using namespace std;

struct Holding{
    string name;
    string symbol;
    double quantity;
    double cost_basis;
};
#endif