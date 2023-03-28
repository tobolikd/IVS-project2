/**
 * @file calc-lib.hpp
 * @author Timotej Halenár (xhalen00), David Tobolík (xtobol06)
 * @brief Calculator math library header - IVS Project 2022/23 // VUT FIT
 * @version 0.1
 * @date 2023-03-28
 * 
 * 
 */

#ifndef IVS_MATH_LIB
#define IVS_MATH_LIB

#include <vector>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>


/**
* @brief Token structure.
* 
*/
typedef struct token
{
    int int_value;
    float float_value;
    int type;
}token_t;

/**
 * @brief Enumeration of token types.
 * 
 */
enum token_types{
    INT_T,
    FLT_T,
    ADD_T,
    SUB_T,
    MUL_T,
    DIV_T
};

template<typename T>
T add(T x, T y);

template<typename T>
T subtract(T x, T y);

template<typename T>
T multiply(T x, T y);

template<typename T>
T divide(T x, T y);

template<typename T>
T power(T x, int n);

double root(double x, double n);

template<typename T>
double sin(T x);

template<typename T>
double cos(T x);

long long int factorial(unsigned int x);

std::vector<token_t> parseExpression(std::string expression);

int evaluateIntExpression(std::vector<token_t> expression);

float evaluateFloatExpression(std::vector<token_t> expression);

void print_token(token_t token);

#endif //IVS_MATH_LIB

//**********End of file calc-lib.hpp************
