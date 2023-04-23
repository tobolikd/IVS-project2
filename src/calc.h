/**
 * @file calc.h
 * @author Jakub Štětina
 * @brief Header file for the calc class
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CALC_H
#define CALC_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QKeyEvent>
#include <string>
#include <map>
#include "ui_calc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class calc; }
QT_END_NAMESPACE

/**
 * @brief Calculator window class
*/
class calc : public QMainWindow
{
    Q_OBJECT

public:
    calc(QWidget *parent = nullptr);
    QSignalMapper* buttonToChar;
    ~calc();
private slots:
    void updateUserInput(QString);
    void clearUserInput();
    void evalInput();
    void clearInputStrings();
    void deleteChar();
    void retrieveAnswer();

private:
    Ui::calc *ui;
    std::string userInputStr;
    std::string mathlibInputStr;
    std::string prevAnswer;
    bool result;
    bool exception;
    unsigned int unclosedBrackets;
    void updateUnclosedBrackets();
    void addUnclosedBrackets();
    void convertExpression();


    /**
     * @brief Defines press events for keyboard input
     * 
     * @param event Key event
     */
    void keyPressEvent(QKeyEvent *event) override
    {
        // Defines control buttons with non-functional roles
        switch(event->key()){
            case Qt::Key_Delete:
                this->clearInputStrings();
                return;
            case Qt::Key_Backspace:
                this->deleteChar();
                return;
            case Qt::Key_Equal:
            case Qt::Key_Enter:
            case Qt::Key_Return:
                this->evalInput();
                return;
        }
        
        // Maps symbol buttons
        std::map<int, std::string> keyToSymbol = {
            {Qt::Key_0, "0"},
            {Qt::Key_1, "1"},
            {Qt::Key_2, "2"},
            {Qt::Key_3, "3"},
            {Qt::Key_4, "4"},
            {Qt::Key_5, "5"},
            {Qt::Key_6, "6"},
            {Qt::Key_7, "7"},
            {Qt::Key_8, "8"},
            {Qt::Key_9, "9"},

            {Qt::Key_ParenLeft,   "("},
            {Qt::Key_ParenRight,  ")"},
            {Qt::Key_Exclam,      "!"},
            {Qt::Key_AsciiCircum, "^"},
            {Qt::Key_Plus,        "+"},
            {Qt::Key_Minus,       "-"},
            {Qt::Key_Asterisk,    "*"},
            {Qt::Key_Slash,       "/"},
            {Qt::Key_C,           "C"},
            {Qt::Key_Period,      "."}
        };

        // If key is not found
        if(keyToSymbol.find(event->key()) == keyToSymbol.end()){
            return;
        }

        // Print user input on screen
        this->updateUserInput(QString::fromStdString(keyToSymbol[event->key()]));

    }}; // class calc
#endif // CALC_H
