#include "calc.h"
#include "ui_calc.h"
#include <map>
#include <string>
#include <regex>
#include <QSignalMapper>
#include <QKeyEvent>
#include <QDebug>

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

    // If result is being shown
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
    QPushButton * comma_button = ui->Button_comma;

    // Function buttons
    QPushButton * clr_button    = ui->Button_clr;
    QPushButton * del_button    = ui->Button_del;
    QPushButton * equal_button  = ui->Button_equal;

    QPushButton * comb_button   = ui->Button_comb;
    QPushButton * fact_button   = ui->Button_fact;
    QPushButton * lBrckt_button = ui->Button_lbracket;
    QPushButton * rBrckt_button = ui->Button_rbracket;
    QPushButton * plus_button   = ui->Button_plus;
    QPushButton * minus_button  = ui->Button_minus;
    QPushButton * power_button  = ui->Button_power;
    QPushButton * sqrt_button   = ui->pushButton;
    QPushButton * div_button    = ui->Button_divide;
    QPushButton * mult_button   = ui->Button_multiply;


    // Button mapping
    QSignalMapper * signalMapper = new QSignalMapper(this);

    // Clear button
    connect(clr_button, SIGNAL(pressed()), this, SLOT(clearUserInput()));

    // Delete button
    connect(del_button, SIGNAL(pressed()), this, SLOT(deleteChar()));

    // Equal button
    connect(equal_button, SIGNAL(pressed()), this, SLOT(evalInput()));

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
    connect(comma_button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

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
    signalMapper -> setMapping(comma_button, ",");

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

calc::~calc()
{
    delete ui;
}

bool endsWith(std::string_view str, std::string_view substr)
{
    return str.size() >= substr.size() && 0 == str.compare(str.size()-substr.size(), substr.size(), substr);
}

// Convert user input string for mathlib library
void calc::convertExpression()
{
    this->mathlibInputStr = std::regex_replace(this->userInputStr, std::regex("√"), "_");
}

// Evaluates expression (stored in mathlibInputStr)
void calc::evalInput()
{
    // TODO -- connect with mathlib
    //      -- catch possible exceptions (from mathlib)
    //      -- convert userInputStr to mathlibInputStr

    this->addUnclocedBrackets();
    this->convertExpression();

    qDebug() << "Expression: " << this->userInputStr << "\n";
    qDebug() << "Mathlib epxression: " << this->mathlibInputStr << "\n";

    this->clearUserInput();
    std::string evaluated = "RESULT";
    QString qevaluated = QString::fromStdString(evaluated);
    this->updateUserInput(qevaluated);
    this->result = true;
}

void calc::clearInputStrings()
{
    this->userInputStr = "";
    this->mathlibInputStr = "";
    this->unclosedBrackets = 0;
}


// Add unclosed brackets to the end of the expression
void calc::addUnclocedBrackets()
{
    this->updateUnclosedBrackets();
    //Add close unclosed brackets
    if(this->unclosedBrackets){
        for(unsigned int i = 0; i < this->unclosedBrackets; i++)
            this->userInputStr += ")";
    }
}


// Updates value of unclosed brackets in the whole expression
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

void calc::deleteChar()
{
    if(this->result){
        this->clearUserInput();
        return;
    }

    std::string newStr = this->userInputStr;
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

// Clears user input strings
void calc::clearUserInput()
{
    this->clearInputStrings();
    QString qstr = QString::fromStdString(userInputStr);
    this->updateUserInput(qstr);
}

// Updates text on userInputLabel
void calc::updateUserInput(QString qstr)
{
    std::string str = qstr.toStdString();


    // If result is being shown, delete it first
    if(this->result){
        this->clearInputStrings();
        this->result = false;
    }

    // Insert default 2 before √ (if other number not specified)
    if(str == "√" && !isdigit(this->userInputStr[this->userInputStr.length() - 1])){
        qDebug() << this->userInputStr[this->userInputStr.length() - strlen("√") - 1] << "\n";
        this->userInputStr += "2";
    }

    this->userInputStr += str;

    QLabel * userInputLabel = this->ui->userInput;
    qstr = QString::fromStdString(this->userInputStr);
    userInputLabel->setText(qstr);
}




