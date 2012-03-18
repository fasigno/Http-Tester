/*
HTTP-Tester - file: browserviewdialog.h - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
*/

#ifndef BROWSERVIEWDIALOG_H
#define BROWSERVIEWDIALOG_H

#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>

#include <QtWebKit/QWebView>

#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QStyle>
#include <QDesktopWidget>

class browserViewDialog : public QWidget
{
    Q_OBJECT

    QWebView *browser;
    QDialogButtonBox *buttonBox;

    void centerWindow();                //Centra la finestra sullo schermo.

public:
    explicit browserViewDialog(QWidget *parent = 0);

    void setHtmlCode(QString);          //Riceve il codice html da mostrare.

signals:

private slots:

    void accept();

};

#endif // BROWSERVIEWDIALOG_H
