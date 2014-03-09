/*
HTTP-Tester - file: browserviewdialog.h - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
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
