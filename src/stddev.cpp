/**
 * @file stddev.cpp
 * @author Jakub Stetina (xsteti05)
 * @brief Math library profiling using the calculation of standard diviation
 * @version 0.1
 * @date 2023-03-30
 * 
 */


#include <iostream>
#include <vector>
#include <math.h>

// TO BE ADDED
// #include "calc-lib.hpp"

// MOCKUP FUNCTIONS
double add(double a, double b) { return a+b; }
double divide(double a, double b){return a/b;}
double multiply(double a, double b){return a*b;}
double subtract(double a, double b){return a-b;}
double power(double a, double b){return a*a;}

using namespace std;

/**
 * @brief Function for calculating standard deviation 
 * using the formula specified in the assignment
 * 
 * @param values vector containg input values
 * @return standard deviation
 */
double calculate_deviation(vector <double> values)
{
    double deviation, avg;
    double N = (double)values.size();
    deviation = avg = 0; 
    for(auto val: values){
        deviation = add(deviation, power(val,2));
        avg = add(avg, val);
    }
    avg = divide(avg, N);
    // cout << "Avg: " << avg << endl;
    return sqrt(multiply(divide(1, subtract(N, 1)), subtract(deviation, multiply(N, power(avg, 2)))));
}

// Only for debugging
void print_values(vector <double> values)
{
    for (auto i: values)
        cout << i << ' ';
    cout << endl;
}


int main(void)
{
    vector <double>values;
    double val;
    while(scanf("%lf", &val) != EOF){
        // TODO - CHECK FOR VALID NUMBER
        values.push_back(val);
    }

    // cout << "Deviation: " << calculate_deviation(values) << endl;
    // print_values(values);
    
    cout << calculate_deviation(values) << endl;
    return 0;
}
