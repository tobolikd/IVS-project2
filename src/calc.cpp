/**
 * @file calc.cpp
 * @author Jakub Štětina
 * @brief The Calculator class
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <map>
#include <string>
#include <regex>
#include <QSignalMapper>
#include <QKeyEvent>

#include "calc.h"
#include "ui_calc.h"
#include "calc-lib.hpp"


/**
 * @brief Calc class constructor
 * 
 * @param parent parent widget
 */
calc::calc(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calc)
{

    ui->setupUi(this);

    // Disable resize
    this->setFixedSize(QSize(800,600));

    // Displayed user input
    userInputStr = "";

    // Input string for mathlib parser
    mathlibInputStr = "";

    // Previous answer (retrievable with ANS button)
    prevAnswer = "";

    // Indicates if result is being shown
    result = false;

    // Auto close brackets after "equals" button
    unclosedBrackets = 0;

    // Number buttons
    QPushButton * but_num_1 = ui->Button_num1;
    QPushButton * but_num_2 = ui->Button_num2;
    QPushButton * but_num_3 = ui->Button_num3;
    QPushButton * but_num_4 = ui->Button_num4;
    QPushButton * but_num_5 = ui->Button_num5;
    QPushButton * but_num_6 = ui->Button_num6;
    QPushButton * but_num_7 = ui->Button_num7;
    QPushButton * but_num_8 = ui->Button_num8;
    QPushButton * but_num_9 = ui->Button_num9;
    QPushButton * point_button = ui->Button_point;

    // Function buttons
    QPushButton * clr_button    = ui->Button_clr;
    QPushButton * del_button    = ui->Button_del;
    QPushButton * equal_button  = ui->Button_equal;
    QPushButton * answ_button   = ui->Button_answer;

    QPushButton * comb_button   = ui->Button_comb;
    QPushButton * fact_button   = ui->Button_fact;
    QPushButton * lBrckt_button = ui->Button_lbracket;
    QPushButton * rBrckt_button = ui->Button_rbracket;
    QPushButton * plus_button   = ui->Button_plus;
    QPushButton * minus_button  = ui->Button_minus;
    QPushButton * power_button  = ui->Button_power;
    QPushButton * sqrt_button   = ui->Button_sqrt;
    QPushButton * div_button    = ui->Button_divide;
    QPushButton * mult_button   = ui->Button_multiply;


    // Button mapping
    QSignalMapper * signalMapper = new QSignalMapper(this);

    // clear, delete, equal, answ buttons:
    connect(clr_button,     SIGNAL(pressed()), this, SLOT(clearUserInput()));
    connect(del_button,     SIGNAL(pressed()), this, SLOT(deleteChar()));
    connect(equal_button,   SIGNAL(pressed()), this, SLOT(evalInput()));
    connect(answ_button,    SIGNAL(pressed()), this, SLOT(retrieveAnswer()));

    // Number buttons
    connect(but_num_1, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_2, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_3, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_4, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_5, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_6, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_7, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_8, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(but_num_9, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(point_button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

    // Function buttons
    connect(comb_button,    SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(fact_button,    SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(rBrckt_button,  SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(lBrckt_button,  SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(plus_button,    SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(minus_button,   SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(mult_button,    SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(div_button,     SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(power_button,   SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    connect(sqrt_button,    SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

    // Number mapping
    signalMapper -> setMapping(but_num_1, "1");
    signalMapper -> setMapping(but_num_2, "2");
    signalMapper -> setMapping(but_num_3, "3");
    signalMapper -> setMapping(but_num_4, "4");
    signalMapper -> setMapping(but_num_5, "5");
    signalMapper -> setMapping(but_num_6, "6");
    signalMapper -> setMapping(but_num_7, "7");
    signalMapper -> setMapping(but_num_8, "8");
    signalMapper -> setMapping(but_num_9, "9");
    signalMapper -> setMapping(point_button, ".");

    // Symbols mapping
    signalMapper -> setMapping(comb_button,   "C");
    signalMapper -> setMapping(fact_button,   "!");
    signalMapper -> setMapping(rBrckt_button, ")");
    signalMapper -> setMapping(lBrckt_button, "(");
    signalMapper -> setMapping(plus_button,   "+");
    signalMapper -> setMapping(minus_button,  "-");
    signalMapper -> setMapping(mult_button,   "*");
    signalMapper -> setMapping(div_button,    "/");
    signalMapper -> setMapping(power_button,  "^");
    signalMapper -> setMapping(sqrt_button,   "√");

    connect(signalMapper, SIGNAL(mappedString(QString)), this, SLOT(updateUserInput(QString)));

}

/**
 * @brief Calc class destructor
 * 
 */
calc::~calc()
{
    delete ui;
}

/**
 * @brief Checks if string ends with specified substring
 * 
 * @param str String
 * @param substr Substring
 * @return true String ends with substring
 * @return false String does NOT end with substring
 */
bool endsWith(std::string_view str, std::string_view substr)
{
    return str.size() >= substr.size() && 0 == str.compare(str.size()-substr.size(), substr.size(), substr);
}

/**
 * @brief Checks if number (double) is a whole number
 * 
 * @param input input number (double)
 * @return true number has non-zero fractional part
 * @return false number is whole
 */
bool isWhole(double input){
    return input == (double)(int)input;
}

/**
 * @brief Converts inputString to mathlib-compatible expression
 * 
 */
void calc::convertExpression()
{
    this->mathlibInputStr = std::regex_replace(this->userInputStr, std::regex("√"), "_");
}

/**
 * @brief Evalueates user input, 
 * prints result on the screen,
 * uses mathlib functions
 * 
 */
void calc::evalInput()
{
    // TODO -- connect with mathlib
    //      -- catch possible exceptions (from mathlib)
    //      -- convert userInputStr to mathlibInputStr

    this->addUnclosedBrackets();
    this->convertExpression();

    double resultDouble = evaluateExpression(parseExpression(this->mathlibInputStr));
    this->clearUserInput();

    std::string resultStr = std::to_string(resultDouble);

    // If result is a whole number display only the whole part
    if(isWhole(resultDouble)){
        resultStr = std::to_string((int)resultDouble);
    }

    QString qResultStr= QString::fromStdString(resultStr);
    this->prevAnswer = resultStr;
    this->updateUserInput(qResultStr);
    this->result = true;
}

/**
 * @brief Prints previous result on screen, 
 * connected with the 'ANS' button
 * 
 */
void calc::retrieveAnswer()
{
    this->updateUserInput(QString::fromStdString(this->prevAnswer));
}


/**
 * @brief Clears input strings
 * 
 */
void calc::clearInputStrings()
{
    this->userInputStr = "";
    this->mathlibInputStr = "";
    this->unclosedBrackets = 0;
}

/**
 * @brief Adds unclosed brackets to the end of the expression
 * 
 */
void calc::addUnclosedBrackets()
{
    this->updateUnclosedBrackets();
    //Add close unclosed brackets
    if(this->unclosedBrackets){
        for(unsigned int i = 0; i < this->unclosedBrackets; i++)
            this->userInputStr += ")";
    }
}


/**
 * @brief Counts the value of unclosed bracket in the usrInputStr
 * 
 */
void calc::updateUnclosedBrackets()
{
    this->unclosedBrackets = 0;
    for(auto &chr : this->userInputStr){
        if(chr == '('){
            this->unclosedBrackets++;
        }
        else if(chr == ')' && this->unclosedBrackets){
            this->unclosedBrackets--;
        }
    }
}


/**
 * @brief Deletes one character from user input, 
 * connected with the 'DEL' button
 * 
 */
void calc::deleteChar()
{
    if(this->result){
        this->clearUserInput();
        return;
    }

    std::string newStr = this->userInputStr;

    // Special case for sqrt symbol (takes up multiple bytes)
    if(this->userInputStr.size()){
        if(endsWith(this->userInputStr,"√")){
            newStr.resize(this->userInputStr.size() - strlen("√"));
        } else {
            newStr.resize(this->userInputStr.size() - 1);
        }
    }

    this->clearInputStrings();
    QString qstr = QString::fromStdString(newStr);
    this->updateUserInput(qstr);
}

/**
 * @brief Clears user input from the screen, 
 * connected with the 'CLR' button
 * 
 */
void calc::clearUserInput()
{
    this->clearInputStrings();
    QString qstr = QString::fromStdString(userInputStr);
    this->updateUserInput(qstr);
}

/**
 * @brief Updates and prints user input
 * 
 * @param qstr New symbol to be added
 */
void calc::updateUserInput(QString qstr)
{
    std::string str = qstr.toStdString();

    // If result is being shown, delete it first
    if(this->result){
        this->clearInputStrings();
        this->result = false;
    }

    // Insert default 2 before √ (if no other number specified)
    if(str == "√" && !isdigit(this->userInputStr[this->userInputStr.length() - 1])){
        this->userInputStr += "2";
    }

    // Update expression
    this->userInputStr += str;

    // Convert to QString
    QLabel * userInputLabel = this->ui->userInput;
    qstr = QString::fromStdString(this->userInputStr);
    userInputLabel->setText(qstr);
}




