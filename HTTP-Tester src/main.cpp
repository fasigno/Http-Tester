/*
HTTP-Tester - file: main.cpp - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester". Under GPLv3.
*/

/*
Notes:
**************************************************************************************************************************************************
*-.QT Bug, class QNetworkAccessManager, the manual reset of http header Accept-Encoding with value "gzip" disables the body data decompression.  *
*  When executing the program you need to delete the header before any request, in that way the default header is setted on gzip and the body is *
*  decompressed correctly.														         *
**************************************************************************************************************************************************
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
