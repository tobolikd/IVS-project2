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
    const char *type[] = {"+", "*", "(", ")", "id", ";", "/", "-", "!", "^", "√", "E", ">"};

    if (token.type == ID_T){
        cout<<token.value<<", ";
    }
    else {
        cout<<type[token.type]<<", ";
    }
}

/**
 * @brief Helper function for printing token vectors.
 * 
 * @param token_vector vector of tokens to be printed
 */
void printTokenVector(std::vector<token_t> token_vector){
    for (int i=0; i<token_vector.size(); i++){
        printToken(token_vector[i]);
    }
    cout<<endl;
}

/**
 * @brief Finds the top most terminal token in token_vector.
 * 
 * @param token_vector vector of tokens
 * @return token_t terminal token
 */
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
 * @brief Finds and pops handle from stack
 * 
 * @param stack vector of tokens representing stack
 * @return std::vector<token_t> vector of tokens representing handle
 */
std::vector<token_t> getHandle(std::vector<token_t> *stack){
    std::vector<token_t> handle;
    int stack_len = stack->size();

    for (int i=0; i<stack_len; i++){
        if ((*stack)[i].type != HANDLE_T){
            handle.insert(handle.begin(), (*stack)[i]);
        }
        else{
            break;
        }
    }

    for (int i=0; i<handle.size(); i++){
        stack->erase(stack->begin());
    }
    stack->erase(stack->begin());

    return handle;

}

/**
 * @brief Performs calculation, creates token with result, and inserts it back into stack
 * 
 * @param stack token vector representing stack
 * @param handle token vector representing handle
 */
void calculateHandle(std::vector<token_t> *stack, std::vector<token_t> handle){
    token_t result_token;
    result_token.type = EXPR_T;

    if (handle.size() == 1){
        result_token.value = handle[0].value;
        stack->insert(stack->begin(), result_token);
        return;
    }
    else if (handle.size() == 2){
        //TODO
        return;
    }
    else if (handle.size() == 3){
        if (handle[0].type == EXPR_T && handle[2].type == EXPR_T){
            if (handle[1].type == MUL_T){
                result_token.value = handle[0].value * handle[2].value;
            }
            else if (handle[1].type == ADD_T){
                result_token.value = handle[0].value + handle[2].value;
            }
            else if (handle[1].type == SUB_T){
                result_token.value = handle[0].value - handle[2].value;
            }
            else if (handle[1].type == DIV_T){
                result_token.value = handle[0].value / handle[2].value;
            }
            stack->insert(stack->begin(), result_token);
            return;
        }
        if (handle[0].type == LBR_T &&  handle[1].type == EXPR_T && handle[2].type == RBR_T){
            result_token.value = handle[1].value;
            stack->insert(stack->begin(), result_token);
            return;
        }
    }
}

/**
 * @brief Inserts special HANDLE_START symbol onto stack in correct position
 * 
 * @param stack token vector representing stack
 */
void insertHandleStart(std::vector<token_t> *stack){
    int stack_size = stack->size();
    token_t handle_start;
    handle_start.type = HANDLE_T;

    for (int i=0; i<stack_size; i++){
        if ((*stack)[i].type != EXPR_T){
            stack->insert(stack->begin() + i, handle_start);
            return;
        }
    }
}

/**
 * @brief Parses an expression from string form into a vector of tokens.
 * 
 * Currently only supports +, -, *, / and parentheses
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
        if (isdigit(c) || c == '.') {
            token += c;
        } else {
            if (token != "") {
                current.value = stod(token);
                current.type = ID_T;
                tokens_vector.push_back(current);
                token = "";
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
                if (c == '+')
                    current.type = ADD_T;
                if (c == '-')
                    current.type = SUB_T;
                if (c == '*')
                    current.type = MUL_T;
                if (c == '/')
                    current.type = DIV_T;
                if (c == '(')
                    current.type = LBR_T;
                if (c == ')')
                    current.type = RBR_T;
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
        current.value = stod(token);
        tokens_vector.push_back(current);
    }

    token_t end_token;
    end_token.type = END_T;
    tokens_vector.push_back(end_token);

    return tokens_vector;
}

/**
 * @brief Evaluates an expression and returns result.
 * 
 * @param expression vector of tokens representing an expression to be evaluated
 * @return double result
 */
double evaluateExpression(std::vector<token_t> expression){
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
    vector<token_t> handle;
    token_t bottom_element;
    bottom_element.type = END_T;
    token_stack.insert(token_stack.begin(), bottom_element);

    token_t handle_start;
    handle_start.type = HANDLE_T;

    token_t input = expression.front();
    expression.erase(expression.begin());

    
    while(!(token_stack.size() == 2 && token_stack.front().type == EXPR_T && token_stack[1].type == END_T && input.type == END_T)){
        /* DEBUG PRINTS
        cout<<"***stack: ***"<<endl;
        printTokenVector(token_stack);
        cout<<"***input token: ***"<<endl;
        printToken(input);
        cout<<endl;
        cout<<"***remaining expression: ***"<<endl;
        printTokenVector(expression);
        cout<<topTerminal(token_stack).type<<endl;
        cout<<input.type<<endl;
        */

        switch (p_table[topTerminal(token_stack).type][input.type]){
            case '<':
                //cout<<"<"<<endl;
                insertHandleStart(&token_stack);
                token_stack.insert(token_stack.begin(), input);
                input = expression.front();
                expression.erase(expression.begin());
                break;
            case '>':
                //cout<<">"<<endl;
                handle = getHandle(&token_stack);
                calculateHandle(&token_stack, handle);
                break;
            case '=':
                //cout<<"="<<endl;
                token_stack.insert(token_stack.begin(), input);
                input = expression.front();
                expression.erase(expression.begin());
                break;
            case 'x':
                cout<<"x"<<endl;
                fprintf(stderr, "Invalid expression\n");
                exit(EXIT_FAILURE);
                break;
        }

    }

    cout<<"result: "<<token_stack.front().value<<endl;
    return 0;
}

//**********End of file calc-lib.cpp************
