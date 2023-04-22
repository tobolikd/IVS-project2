/**
 * @file main.cpp
 * @author Jakub Štětina
 * @brief Calculator main
 * runs the gui event loop
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "calc.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calc w;
    w.show();
    return a.exec();
}
