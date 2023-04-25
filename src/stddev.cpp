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
#include "calc-lib.hpp"

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
        deviation = add<double>(deviation, power<double>(val,2));
        avg = add<double>(avg, val);
    }
    avg = divide<double>(avg, N);
    return root(multiply<double>(divide<double>(1, subtract<double>(N, 1)),
        subtract<double>(deviation, multiply<double>(N, power<double>(avg, 2)))), 2);
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
