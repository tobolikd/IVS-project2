#ifndef CALC_H
#define CALC_H

#include <QMainWindow>
#include <QSignalMapper>
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
    bool sqrt;
};
#endif // CALC_H
