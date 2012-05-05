/*
HTTP-Tester - file: httpfuncs.h - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
*/

#ifndef HTTPFUNCS_H
#define HTTPFUNCS_H

#include "testergui.h"
#include "credentialdialog.h"
#include "cookiecache.h"

#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkConfigurationManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkSession>
#include <QtDebug>

#include <QSslError>

#include <iostream>
#include <string>
#include <QString>
#include <QHostAddress>

#include <QTextStream>
#include <QFile>
#include <QBuffer>
#include <QMessageBox>

class TesterGui;
class cookieCache;

class httpfuncs : public QObject
{
Q_OBJECT

public:

    enum reqDone {POST, GET, HEAD, OPTIONS};                    //Indica la richiesta fatta.

private:

    reqDone reqDoneFlag;                                        //Allocazione del tipo enumerato che memorizza la richiesta che è stata processata/deve essere processata.
    TesterGui *testerGuiObj;                                    //Puntatore alla grafica.

    bool credError;                                             //Variabile booleana che determina se le credenziali sono già state chieste.

    QString rData;                                              //stringa di dati ricevuti dal server.
    QList<QByteArray> rHeaders;                                 //Lista di header ricevuti dal server.
    QList< QPair<QString, QString> > SHeaders;                  //Qlist che contiene le coppie di headers in qstring da dare alla grafica.

    QAuthenticator* auth;                                       //Oggetto che contiene le credenziali per la richiesta.

    cookieCache *cookieJar;                                     //Cache dei cookies.

    QNetworkAccessManager *nmanager;
    QNetworkRequest request;
    QNetworkReply *reply;
    QUrl url;

    void connectS();                                            //Connette gli slot della richiesta http.
    void resetHeades();                                         //Ripristina gli headers a 0.

    QList <QUrl> acceptCookieUrls;                              //Lista di cookie policy da reinviare alla grafica.

public slots:
    void replyFinished();
    void slotError(QNetworkReply::NetworkError);
    void slotSslErrors(QList<QSslError>);

    void credentials(QNetworkReply*, QAuthenticator*);

public:
    httpfuncs(TesterGui *);

    void sendRequest(reqDone, QByteArray* = 0);                 //Il QByteArray contiene i dati da inviare solo con il metodo POST.

    //Imposta i dati (parametri e url) per una richiesta generica definita successivamente.
    void setRequestUrl(QUrl);
    void setRequestHeader(QByteArray, QByteArray);              //Imposta un solo parametro aggiuntivo
                                                                //Per più parametri va richiamata più volte.

    //Restituisce il body e gli header di risposta.
    QString getReplyBody();
    QList< QPair<QString, QString> >getReplyHeaders();

    void saveOnfile(QString filePath, bool mode);               //Scrive su file il body o gli headers Mode - True = Body, false = Headers.

    QString ninterfaces();                                      //Indica le interfacce di rete attiva e l'eventuale ip. Restituisce un QString per la grafica.

    void setPasswd(QString);                                    //Permettono L'impostazione di utente e password e sono richiamate dal credentialdialog.
    void setUser(QString);

    void setFalseCredError();                                   //Imposta credError a false quando l'utente preme su reject dopo aver sbagliato le credenziali.

    QList<QNetworkCookie> getCookiesList();                     //Funzione che restituisce i cookies impostati dai server.

    void enableCookieJar(bool);                                 //Abilita o disabilita la cookieJar.

    bool getCookieJarState();                                   //Restituisce lo stato della cookieJar per controlli futuri.

    QList<QNetworkCookie> cookiesForUrl(const QUrl &url);       //Restituisce alla grafica i cookie che devono essere rispediti al server.

    void setUrlConstraint(QList <QUrl>);                        //Invia alla cache gli url da evitare impostati dalla grafica.

    QList <QUrl> getUrlConstraint();                            //Invia alla grafica gli eventuali url precedentemente impostati.

};

#endif // HTTPFUNCS_H
