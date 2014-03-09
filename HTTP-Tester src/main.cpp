/*
HTTP-Tester - file: main.cpp - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.

                                HTTP-Tester
A simple http tester written in qt that allows the examination of server responses.

*/

#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <iostream>

#include "testergui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TesterGui *testerGui = new TesterGui;
    testerGui->show();
    return app.exec(); // start event handling
}
