/*
HTTP-Tester - file: viewcookiecache.h - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
*/

#ifndef VIEWCOOKIECACHE_H
#define VIEWCOOKIECACHE_H

#include "httpfuncs.h"

#include <QWidget>
#include <QDesktopWidget>

namespace Ui {
    class viewCookieCache;
}

class httpfuncs;

class viewCookieCache : public QWidget
{
    Q_OBJECT

public:
    explicit viewCookieCache(QWidget *parent = 0);
    ~viewCookieCache();

    void setHttpFuncp(httpfuncs*);    //Imposta il puntatore ad httpfunc e preleva la lista di cookies.

private:
    Ui::viewCookieCache *ui;

    void centerWindow();              //Centra la finestra sullo schermo.

private slots:

    void accept();                    //Ok Dialogo.
};

#endif // VIEWCOOKIECACHE_H
