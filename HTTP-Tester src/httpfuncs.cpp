/*
HTTP-Tester - file: httpfuncs.cpp - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
*/


#include "httpfuncs.h"

httpfuncs::httpfuncs(TesterGui *testerObj) //Costruttore.
{

    testerGuiObj = testerObj; //Puntatore alla grafica.
    nmanager = new QNetworkAccessManager(this);

    credError = false;

    //Slot richiesta autenticazione.
    connect(nmanager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this, SLOT(credentials(QNetworkReply*,QAuthenticator*)));

    cookieJar = new cookieCache;        //Settaggio della cache dei cookies.
    nmanager->setCookieJar(cookieJar);
}

//SLOTS::

void httpfuncs::connectS() {

    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));

    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(slotSslErrors(QList<QSslError>)));

}

void httpfuncs::replyFinished() {
    //Viene richiamata all'arrivo dei dati e informa la grafica che li richiede con le funzioni apposite.

    //=======Viene preparata la statusLine della richiesta appena effettuata e passata alla grafica::

    QString status = "HTTP/1.1 ";

    status.append(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString() + " ");
    status.append(reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString());

    testerGuiObj->setStatusLine(status);

    //========

    //Si svuota rData e SHeaders per richieste successive.
    rData.clear(); SHeaders.clear();

    //Salva i dati ricevuti ::
    //Body.
    if (reply->isReadable() == true)
    rData = QString(reply->readAll());

    //Headers.

    QString app, app1; //Var. Appoggio.
    QPair<QString, QString> pair;

    rHeaders = reply->rawHeaderList();

    for (int i = 0; i < rHeaders.size(); ++i) {
        app = QString(rHeaders.at(i));

        pair.first = app;

        if (reply->hasRawHeader(rHeaders.at(i)) == true) //Controllo se l'header è stato inviato dal server.
        app1 = QString(reply->rawHeader(rHeaders.at(i)));

        pair.second = app1;

        SHeaders.insert(i, pair);
    }

    testerGuiObj->requestFinished(); //Informa la grafica dei dati pronti.

    reply->deleteLater();            //Elimina la reply.

}

//DA SISTEMARE GLI ERRORI di connessione.
void httpfuncs::slotError(QNetworkReply::NetworkError) {qWarning() << "Reply Error : " << reply->errorString();}
void httpfuncs::slotSslErrors(QList<QSslError>) {qWarning() << "Ssl Error : " << reply->errorString();}

void httpfuncs::credentials(QNetworkReply*,QAuthenticator* auth) { //Slot che chiede le credenziali, nel caso siano necessarie.

    //credError - Variabile booleana che determina se le credenziali sono già state chieste.

    if (credError == false) {  //Visualizzazione form credenziali :con:

        this->auth = auth;

        credentialDialog *c = new credentialDialog;
        c->sethttpfuncsP(this);
        c->show();

    } else {

        QMessageBox::warning(NULL, tr("HTTP-Tester"),
                                        tr("Wrong credentials!"), QMessageBox::Ok);
        credentialDialog *c = new credentialDialog;
        c->sethttpfuncsP(this);
        c->show();

    }

    credError = true;

}

//Funzioni ::

void httpfuncs::setRequestUrl(QUrl url) { //Imposta l'host della richiesta.

    static QString oldUrl; //Contiene l'url della richiesta precedente per evitare errore credenziali.

    if (QString::compare(oldUrl, url.toString(), Qt::CaseInsensitive) != 0) { //Se le due stringhe non sono uguali.

        //Al cambio di url credError viene reimpostata per evitare, nel caso di richieste multiple con passwd a siti diversi,
        //venga dato errore di credenziali alla prima richiesta.

        oldUrl = url.toString();
        credError = false;

    }

    request.setUrl(url);

    //std::cout << QString(url.encodedHost()).toStdString();
}

void httpfuncs::setRequestHeader(QByteArray header, QByteArray value){ //Imposta un'header per la richiesta da effettuare.
        request.setRawHeader(header, value);
}

//Scrive su file il body o gli headers Mode - True = Body, false = Headers.
void httpfuncs::saveOnfile(QString filePath, bool mode) {

    //Scrittura su file ::
    QTextStream out;
    QFile fileo;
    QString hString;

    fileo.setFileName(filePath);
    if (!fileo.open(QIODevice::WriteOnly | QIODevice::Text))
        std::cout << "Output file error!" << std::endl;

    out.setDevice(&fileo);

    if (mode == true) { //Salva Body.
    out << rData;

    } else { //Salva headers.

        for(int i=0; i< SHeaders.length(); i++) {

            hString += SHeaders.at(i).first + " = " + SHeaders.at(i).second + "\n";

        }
    }

    out << hString;

}

//void httpfuncs::post(QByteArray pData) {reply = nmanager->post(request, pData); connectS(); reqDoneFlag = POST;}

void httpfuncs::sendRequest(reqDone flag, QByteArray* postData) { //Viene passata la stringa http e il flag del tipo di richiesta da effettuare.

    //Request definisce la stringa http di richiesta.
    //La richiesta personalizzata è definita in una stringa QBuffer di QByteArray secondo regole http.

    reqDoneFlag = flag;

    switch(flag) {

    case GET:
        reply = nmanager->get(request);
        break;

    case POST:
        reply = nmanager->post(request, *postData);
        break;

    case HEAD:
        reply = nmanager->head(request);
        break;

    case OPTIONS:
        reply = nmanager->sendCustomRequest(request, QByteArray("OPTIONS"));
        break;
    }

    connectS(); //Collegamento degli slot.

}

QString httpfuncs::getReplyBody() { //Restituisce il body di risposta.
    return rData;
}

QList< QPair<QString, QString> > httpfuncs::getReplyHeaders() { //Restituisce gli header di risposta.
    return SHeaders;
}

QString httpfuncs::ninterfaces() { // Restituisce un QString con la lista di interfacce.

    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();

    bool active = false;
    QString interfaces;


    for (int i = 0; i < ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);

             if ( iface.flags().testFlag(QNetworkInterface::IsUp)
             && !iface.flags().testFlag(QNetworkInterface::IsLoopBack) )
        {


/*#ifdef DEBUG
            qDebug() << "name:" << iface.name() << endl
                    << "ip addresses:" << endl
                    << "mac:" << iface.hardwareAddress() << endl;
#endif */

            for (int j=0; j<iface.addressEntries().count(); j++)
            {


                interfaces.append("IFace Name: " + iface.name() + "\n"
                                  "Ip Address: " + iface.addressEntries().at(j).ip().toString() + "  /  " + iface.addressEntries().at(j).netmask().toString() + "\n"
                                  "Mac Address: " + iface.hardwareAddress() + "\n\n"
                                  );

/*#ifdef DEBUG
                qDebug() << iface.addressEntries().at(j).ip().toString()
                        << " / " << iface.addressEntries().at(j).netmask().toString() << endl;

#endif */

                if (active == false)
                    active = true;
            }

        } // Fine IF.

    } // Fine FOR iniziale.

//    return active;

  return interfaces;
}

//Permettono L'impostazione di utente e password e sono richiamate dal credentialdialog ::
void httpfuncs::setPasswd(QString passwd){auth->setPassword(passwd); this->sendRequest(reqDoneFlag);} //Alla ricezione della password(ultimo parametro) si aggiorna la richiesta rieffettuandola.
void httpfuncs::setUser(QString user){auth->setUser(user);}

//Imposta credError a false quando l'utente preme su reject dopo aver sbagliato le credenziali.
void httpfuncs::setFalseCredError() {credError = false;}

//Funzione che restituisce i cookies impostati dai server.
QList<QNetworkCookie> httpfuncs::getCookiesList() {

    if(cookieJar->enabled() == true) {
    return cookieJar->allCookiesList();

    } else {

    QList<QNetworkCookie> p; //Se la cookiejar non è impostata passa un oggetto vuoto.
    p.clear();

        return p;

    }

}

//Abilita o disabilita la cookieJar.
void httpfuncs::enableCookieJar(bool b) {

    if (b == true) { //Abilitazione cookieJar.

        cookieJar->setEnabled(true);

    } else { //Disabilitazione cookieJar.

        cookieJar->setEnabled(false);
    }

}

//Restituisce lo stato della cookieJar per controlli futuri.
//True: Attiva, False: Disattiva.
bool httpfuncs::getCookieJarState() {
    return cookieJar->enabled();
}

//Restituisce alla grafica i cookie che devono essere rispediti al server.
QList<QNetworkCookie> httpfuncs::cookiesForUrl(const QUrl &url) {
    return cookieJar->cookiesForUrl(url);
}

//Invia alla cache gli url da evitare impostati dalla grafica.
void httpfuncs::setUrlConstraint(QList <QUrl> urls) {
    acceptCookieUrls =  urls;          //Vengono memorizzati per futuri accessi alla grafica.
    cookieJar->setUrlConstraint(urls); //Vengono passati alla cache.
}

//Invia alla grafica gli eventuali url precedentemente impostati.
QList <QUrl> httpfuncs::getUrlConstraint() {
return acceptCookieUrls;
}


