/*
HTTP-Tester - file: credentialdialog.h - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
*/


#ifndef CREDENTIALDIALOG_H
#define CREDENTIALDIALOG_H

#include "testergui.h"
#include "httpfuncs.h"

#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QWidget>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>

class httpfuncs;

class credentialDialog : public QWidget
{
    Q_OBJECT

    QLabel *passwd, *username, *text;
    QLineEdit *usernameL, *passwdL;
    QDialogButtonBox *buttons;

    QVBoxLayout *vertical;
    QGridLayout *centralH;

    httpfuncs *httpfuncsP;                                         //Puntatore ad httfuncs.

    void centerWindow();                                           //Centra la finestra sullo schermo.

public:
    explicit credentialDialog(QWidget *parent = 0);

    void sethttpfuncsP(httpfuncs *);                               //Imposta un puntatore di httpfuncs.

signals:

public slots:
    void accept();
    void reject();

};

#endif // CREDENTIALDIALOG_H