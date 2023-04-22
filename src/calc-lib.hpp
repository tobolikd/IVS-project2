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
    double value;
    int type;
}token_t;

/**
 * @brief Enumeration of token types.
 * 
 */
enum token_types{
    ADD_T,
    MUL_T,
    LBR_T,
    RBR_T,
    ID_T,
    END_T,
    DIV_T,
    SUB_T,
    FAC_T,
    EXP_T,
    SQR_T,
    EXPR_T,
    HANDLE_T
};

/**
 * @brief Adds two numbers together
 * @param x First number
 * @param y Second number
 * @return Their sum; same type as operands
*/
template<typename T>
T add(T x, T y) {
    return x + y;
}

/**
 * @brief Subtracts the second number from the first one
 * @param x First number
 * @param y Second number
 * @return Their difference; same type as operands
*/
template<typename T>
T subtract(T x, T y) {
    return x - y;
}

/**
 * @brief Multiplies two numbers together
 * @param x First number
 * @param y Second number
 * @return Their product; same type as operands
*/
template<typename T>
T multiply(T x, T y) {
    return x * y;
}

/**
 * @brief Divides first number by the second number
 * @param x First number = dividend
 * @param y Second number = divisor (non-zero)
 * @return Their quotient; same type as operands
 * @throw Runtime error if a divisor is zero
*/
template<typename T>
T divide(T x, T y) {
    if (y == 0)
        throw std::runtime_error("Division by zero");
    return x / y;
}

/**
 * @brief Counts the nth power of a given number
 * @param x Base
 * @param n Exponent
*/
template<typename T>
T power(T x, int n) {
    T result = 1;
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

/**
 * @brief Counts nth root of num
 * @param num Number to be "rooted"
 * @param n Nth root
*/
double root(double num, double n_);

/**
 * @brief Counts sin(x)
 * @param x
*/
template<typename T>
double sin(T x) {return 0;}

/**
 * @brief Counts cos(x)
 * @param x
*/
template<typename T>
double cos(T x) {return 0;}


/**
 * @brief Counts factorial of a given number
 * @param x Positive integer
*/
long long int factorial(unsigned int x);

std::vector<token_t> parseExpression(std::string expression);

double evaluateExpression(std::vector<token_t> expression);

/**
 * @brief Helper function for printing tokens.
 * 
 * @param token token to be printed
 */
void printToken(token_t token);

/**
 * @brief Helper function for printing token vectors.
 * 
 * @param token_vector vector of tokens to be printed
 */
void printTokenVector(std::vector<token_t> token_vector);

/**
 * @brief Finds the top most terminal token in token_vector.
 * 
 * @param token_vector vector of tokens
 * @return token_t terminal token
 */
token_t topTerminal(std::vector<token_t> token_vector);

#endif //IVS_MATH_LIB

//**********End of file calc-lib.hpp************
