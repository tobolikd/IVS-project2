/**
 * @file calc-lib.cpp
 * @author Timotej Halenár (xhalen00), David Tobolík (xtobol06)
 * @brief Calculator math library - IVS Project 2022/23 // VUT FIT
 * @version 0.1
 * @date 2023-03-28
 * 
 * 
 */

#include <stdexcept>
#include <string>
#include <variant>
#include <vector>
#include <iostream>

#include "calc-lib.hpp"

using namespace std;

template<typename T>
T add(T x, T y) {
    return x + y;
}

template<typename T>
T subtract(T x, T y) {
    return x - y;
}

template<typename T>
T multiply(T x, T y) {
    return x * y;
}

template<typename T>
T divide(T x, T y) {
    if (y == 0)
        throw std::runtime_error("Division by zero");
    return x / y;
}

/**
 * @brief Helper function for printing tokens.
 * 
 * @param token token to be printed
 */
void print_token(token_t token){
    if (token.type == INT_T){
        cout<<"type: int, value: "<<token.int_value<<endl;
    }
    else if (token.type == ADD_T)
    {
        cout<<"type: +"<<endl;
    }
    else if (token.type == SUB_T)
    {
        cout<<"type: -"<<endl;
    }
    else if (token.type == MUL_T)
    {
        cout<<"type: *"<<endl;
    }
    else if (token.type == DIV_T)
    {
        cout<<"type: /"<<endl;
    }
    else{
        cout<<"unknown token!"<<endl;
    }
    
}

/**
 * @brief Parses an expression from string form into a vector of tokens.
 * 
 * Currently only supports +, -, *, / and integer values
 * 
 * @param expression mathematical expression (e.g. 5*7+123)
 * @return vector<token_t> vector of tokens ready to be evaluated
 */
std::vector<token_t> parseExpression(std::string expression) {
    //remove whitespace
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    
    vector<token_t> tokens_vector;
    token_t current;
    string token = "";
    for (int i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if (isdigit(c)) {
            token += c;
        } else {
            if (token != "") {
                current.int_value = stoi(token);
                current.type = INT_T;
                tokens_vector.push_back(current);
                token = "";
            }
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                if (c == '+')
                    current.type = ADD_T;
                if (c == '-')
                    current.type = SUB_T;
                if (c == '*')
                    current.type = MUL_T;
                if (c == '/')
                    current.type = DIV_T;
                tokens_vector.push_back(current);
            }
            else{
                fprintf(stderr, "Invalid Expression\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (token != "") {
        current.type = INT_T;
        current.int_value = stoi(token);
        tokens_vector.push_back(current);
    }

    return tokens_vector;
}

/**
 * @brief Evaluates an expression containing int values and returns result.
 * 
 * @param expression vector of tokens representing an expression to be evaluated
 * @return int result
 */
int evaluateIntExpression(std::vector<token_t> expression){
    return 0;
}

/**
 * @brief Evaluates an expression containing float values and returns result.
 * 
 * @param expression vector of tokens representing an expression to be evaluated
 * @return float result
 */
float evaluateFloatExpression(std::vector<token_t> expression){
    return 0.0;
}

//**********End of file calc-lib.cpp************