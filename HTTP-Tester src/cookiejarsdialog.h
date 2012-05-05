/*
HTTP-Tester - file: cookiejarsdialog.h - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
*/

#ifndef COOKIEJARSDIALOG_H
#define COOKIEJARSDIALOG_H


#include "httpfuncs.h"

#include <ui_cookiejarsdialog.h>
#include <QDesktopWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QStandardItem>

class cookieJarSDialog;
class httpfuncs;

class cookieJarSDialog : public QWidget
{
    Q_OBJECT

    Ui::cookiesjarsdialog ui;
    void centerWindow();       //Centra la finestra sullo schermo.
    void init();               //Inizializza la tableView.

    httpfuncs *httpfuncsp;     //Puntatore ad httpfuncs.

    bool cookieJarState;       //Indica se la cookieJar è attiva.

    QStandardItemModel *model; //Modello della table.

private slots:

    void reject();            //Pressione annulla.
    void accept();            //Pressione ok.
    void rmUrl();             //Rimozione url.
    void addUrl();            //Aggiunta url.
    void enableGUI();         //Abilita o disabilita gli oggetti grafici.

public:
    cookieJarSDialog(QWidget *parent = 0);

    void setHttpFuncp(httpfuncs*);   //Imposta il puntatore di httpfuncs.

    void setCookieJarState(bool);        //Imposta lo stato attuale della cookieJar per aperture future.
};

#endif // COOKIEJARSDIALOG_H
