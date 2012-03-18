/*
HTTP-Tester - file: viewcookiecache.h - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
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
