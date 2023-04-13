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

private:
    Ui::calc *ui;
    std::string userInputStr;
    std::string mathlibInputStr;
    bool result;
    unsigned int unclosedBrackets;
    void updateUnclosedBrackets();

    void keyPressEvent(QKeyEvent *event) override
    {
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
            {Qt::Key_C,           "C"}
        };

        if(keyToSymbol.find(event->key()) == keyToSymbol.end()){
            return;
        }
        this->updateUserInput(QString::fromStdString(keyToSymbol[event->key()]));

    }};
#endif // CALC_H
