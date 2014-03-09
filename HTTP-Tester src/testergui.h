/*
HTTP-Tester - file: testergui.h - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
*/

#ifndef TESTERGUI_H
#define TESTERGUI_H

#include "httpfuncs.h"
#include "tablemodel.h"
#include "credentialdialog.h"
#include "bdatadialog.h"
#include "showhidebutton.h"
#include "browserviewdialog.h"
#include "cookiejarsdialog.h"
#include "viewcookiecache.h"

#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QNetworkAccessManager>

#include <QObject>
#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QSpinBox>
#include <QComboBox>
#include <QRadioButton>
#include <QFileDialog>
#include <QMovie>

#include <QGroupBox>
#include <QDialog>
#include <QToolTip>

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDialogButtonBox>

//Per la scrollbar::
#include <QScrollBar>
#include <QScrollArea>

//Per la tableView ::
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QHeaderView>

class httpfuncs;
class TableModel;
class cookieJarSDialog;
class viewCookieCache;

class TesterGui: public QWidget
{
    Q_OBJECT

public:
    TesterGui(QWidget *parent = 0);
    ~TesterGui();

    void requestFinished();                                //Viene richiamata quando la richiesta è stata completata.
    void updateCustomLine();                               //Viene richiamata all'inserimento di parametri GET che modificano la sintassi della richiesta.

    //void setDtable(TableModel);                          //Restituisce i dati presenti nella DTable solo per storage.

    void setBodyData(QList< QPair<QString, QString> >);    //Riceve i dati dal form btdata da accodare alla richiesta.

    void setStatusLine(QString);                //Aggiorna la statusLine con l'esito della richiesta http.

private slots:

    void showhideBody();                                   //Mostra o nasconde la sezione del body.
    void showhideHeader();                                 //Mostra o nasconde la sezione del header.

    void showUrltt();                                      //Slot che mostra il tooltip dell'urline.

    void viewBodyBrowser();                                //Mostra un dialogo con il body nel browser.

    void methodItemCh(QListWidgetItem*, QListWidgetItem*); //Viene richiamato al cambio di metodo selezionato.
    void sendRequest();                                    //Invia la request
    void addQData();                                       //Mostra un form per l'inserimento dei dati da accodare alla Q.
    void addQHeader();                                     //Aggiunge alla listView degli header una riga modificabile - tasto +.
    void rmQHeader();                                      //Rimuove l'header selezionato dalla listView - tasto -.

    void about();                                          //Messaggio informazioni.
    void showInterfaces();                                 //Mostra le intefacce attive.
    void exitTester();                                     // Esce dal programma.

    void adaptTextBody();                                  //Adatta automaticamente la grandezza dei QLineEdit in base al testo e abilita/disabilita i tasti funzione.
    void adaptTextHeader();

    void addHostHeader();                                  //Slot per l'aggiunta dell'header host quando si aggiunge url della richiesta, viene inoltre aggiornata la requestLine.

    void saveBodyDialog();                                 //Mostra un dialogo per il salvataggio del body ricevuto.
    void saveHeaderDialog();                               //Mostra un dialogo per il salvataggio degli headers ricevuti.

    void cookieJarSettings();                              //Mostra il dialogo di impostazione cookieJar.
    void viewCookies();                                    //Mostra il dialogo di visualizzazione cookies.

private:

    //Graphic ::

    QListWidget *methodList; //Contiene gli oggetti in ordine della QList dei metodi.

    void maximizeWindow();

    QAction *exitAct;

    QMovie *idleMovie;                              //Animazione attesa dati.
    QLabel *movieLabel;                             //Label che visualizzerà l'animazione.

    // Menu
    /*QMenu *fileMenu;
    QMenu *cookiesMenu;
    QMenu *interfacesMenu;
    QMenu *helpMenu;

    */

    QGroupBox *gridGroupBox1;
    QGroupBox *gridGroupBox2;

    QLabel *customLabel;
    QLineEdit *customLine;                      //Casella della richiesta.
    QLabel *urlLabel;
    QLineEdit *urlLine;                         //Casella Url.

    QTableView *rHeadersList;                   //Vista tabella request headers.
    TableModel Dtable;                          //Vista tabella dati da reinviare ogni volta al form che li visualizza.

    QPushButton *sendButton;                    //Pulsante invia richiesta.
    QPushButton *qDataButton;                   //Pulsante aggiungi dati da accodare alla richiesta.
    QLabel *statusLabel;
    QLineEdit *statusLine;

    QGroupBox *reHeaderGroupBox;
    QLabel *reHeaderLabel;

    ShowHideButton *shHeaderButton;             //Pulsante che mostra o nasconde la sezione headers.
    ShowHideButton *shBodyButton;               //Pulsante che mostra o nasconde la sezione body.

    QTextEdit *reHeader;
    QPushButton *saveHeader;

    QGroupBox *reBodyGroupBox;
    QLabel *reBodyLabel;

    QTextEdit *reBody;
    QPushButton *saveBody;
    QPushButton *browserView;                   //Pulsante che mostra una finestra browser con il body.
    QPushButton *exitButton;                    //Bottone per uscire dal programma

    //Code ::
    enum reqDone {POST, GET, HEAD, OPTIONS};    //Tipo enumerato che indica la richiesta da svolgere premendo send.
    reqDone reqFlag;                            //Allocazione del tipo enumerato.

    httpfuncs *tester;                          //Oggetto httpfunc che contine il codice per le richieste.
    QUrl url;                                   //QUrl che contiene l'url e i dati da passare alla richiesta.

    QString rGData;                             //Stringa di dati ricevuti dal server della GUI.
    QList< QPair<QString, QString> > rGHeaders; //Lista di header ricevuti dal server della GUI.
    QByteArray encodedQueryData;                //Contiene la stringa dei dati da accodare a una richiesta POST.

    QList< QPair<QString, QString> > bodydata;  //Lista di dati inviati al server copia da reinviare al form.

    TableModel *Htable;                         //Modello per la tabella degli headers.

    void addEntry(QString, QString);            //Inserimento headers in tabella
    void rmEntry();                             //Eliminazione headers in tabella.

    void defaultHeaders();                      //Mostra gli headers di default.

};

#endif // TESTERGUI_H
