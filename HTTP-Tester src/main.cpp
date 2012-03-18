/*
HTTP-Tester - file: main.cpp - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
*/

/*
Note::
**********************************************************************************************************************************************
*-.BUG DI QT, class QNetworkAccessManager, il risettaggio manuale dell'header Accept-Encoding con "gzip" disabilita la compressione dei dati.*
*                                                                                                                                            *
*-.ERRORE QT, In testergui.cpp->updateCustomLine() - Line751, Parsing non corretto della linea newCustomLine.lastIndexOf("/");               *
*                                                                                                                                            *
**********************************************************************************************************************************************
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
