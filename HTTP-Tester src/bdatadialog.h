/*
HTTP-Tester - file: bdatadialog.h - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
*/

#ifndef BDATADIALOG_H
#define BDATADIALOG_H

#include "tablemodel.h"
#include "testergui.h"

#include <QWidget>
#include <QUrl>

//Per le tableView ::
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QHeaderView>

//Grafica ::
#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QStyle>
#include <QDesktopWidget>

class TesterGui;
class httpfuncs;

class bdataDialog : public QWidget
{
    Q_OBJECT

     TableModel *Dtable;                         // Modello per la tabella degli headers.
     QTableView *rDataList;                      // Vista tabella request headers.
     QLabel *text;

     TesterGui *TesterGuiP;                      //Puntatore a TesterGui.

     void addEntry(QString, QString);            //Inserimento headers in tabella
     void rmEntry();                             //Eliminazione headers in tabella.

     void centerWindow();                        //Centra la finestra sullo schermo.

public:
    explicit bdataDialog(QList< QPair<QString, QString> > bodydata, QWidget *parent = 0);

    void setTesterGuiP(TesterGui *);

signals:

private slots:

    void upClicked();                           //Muove un'entrata della tabella verso su.
    void downClicked();                         //Muove un'entrata della tabella verso giù.

public slots:

     void addDHeader();                          //Aggiunge alla listView degli header una riga modificabile - tasto +.
     void rmDHeader();                           //Rimuove l'header selezionato dalla listView - tasto -.

     void accept();                              //Pulsante ok - form.
     void reject();                              //Pulsante annulla - form.

};

#endif // BDATADIALOG_H
