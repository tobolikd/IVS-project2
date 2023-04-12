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
#include <stack>

#include "calc-lib.hpp"

using namespace std;

double root(double num, double n_){
    double x;
    double A(num);
    double dx;
    double eps(10e-6);
    double n(n_);
    x = A * 0.5;
    dx = (A/power(x,n-1)-x)/n;
    while(dx >= eps || dx <= -eps){
        x = x + dx;
        dx = (A/power(x,n-1)-x)/n;
    }
   return x;
}

long long int factorial(unsigned int x) {
    for (unsigned int i=x-1; i>0; i--){
        x=x*i;
    }
    return x;
}

/**
 * @brief Helper function for printing tokens.
 * 
 * @param token token to be printed
 */
void printToken(token_t token){
    const char *type[] = {"+", "*", "(", ")", "id", ";", "/", "-", "!", "^", "√", "E"};

    if (token.type == ID_T){
        cout<<token.int_value<<", ";
    }
    else {
        cout<<type[token.type]<<", ";
    }
}

void printTokenVector(std::vector<token_t> token_vector){
    for (int i=0; i<token_vector.size(); i++){
        printToken(token_vector[i]);
    }
    cout<<endl;
}

token_t topTerminal(std::vector<token_t> token_vector){
    for (int i=0; i<token_vector.size(); i++){
        if(token_vector[i].type!=EXPR_T){
            return token_vector[i];
        }
    }
    fprintf(stderr, "No terminal found");
    exit(EXIT_FAILURE);
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
                current.type = ID_T;
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
        current.type = ID_T;
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
    //precedence table
    const char p_table[11][11] = {
    //+    *    (    )    i    $    /    -    !    ^    √  
    {'>', '<', '<', '>', '<', '>', '<', '>', '<', '<', '<'}, // +
    {'>', '>', '<', '>', '<', '>', '>', '>', '<', '<', '<'}, // *
    {'<', '<', '<', '=', '<', 'x', '<', '<', '<', '<', '<'}, // (
    {'>', '>', 'x', '>', 'x', '>', '>', '>', '>', '>', '>'}, // )
    {'>', '>', 'x', '>', 'x', '>', '>', '>', '>', '>', '>'}, // i
    {'<', '<', '<', 'x', '<', 'x', '<', '<', '<', '<', '<'}, // $
    {'>', '>', '<', '>', '<', '>', '>', '>', '>', '>', '<'}, // /
    {'>', '<', '<', '>', '<', '>', '<', '>', '<', '<', '<'}, // -
    {'>', '<', '<', '>', '<', '>', '<', '>', 'x', '>', '>'}, // !
    {'<', '<', '<', '>', '<', '>', '<', '<', '<', '>', '<'}, // ^
    {'<', '<', '<', '>', '<', '>', '<', '<', '<', '>', '<'}, // √
    };


    vector<token_t> token_stack;
    token_t bottom_element;
    bottom_element.type = END_T;
    token_stack.insert(token_stack.begin(), bottom_element);

    while(expression.size()>0){
        token_t input = expression.front();
        expression.erase(expression.begin());

        cout<<"***stack: ***"<<endl;
        printTokenVector(token_stack);
        cout<<"***input token: ***"<<endl;
        printToken(input);
        cout<<endl;
        cout<<"***remaining expression: ***"<<endl;
        printTokenVector(expression);

        switch (p_table[topTerminal(token_stack).type][input.type]){
            case '<':
                cout<<"<"<<endl;
                token_stack.insert(token_stack.begin(), input);
                break;
            case '>':
                cout<<">"<<endl;
                return 0;
                break;
            case '=':
                cout<<"="<<endl;
                return 0;
                //TODO
                break;
            case 'x':
                cout<<"x"<<endl;
                return 0;
                //TODO
                break;
        }
    }

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
