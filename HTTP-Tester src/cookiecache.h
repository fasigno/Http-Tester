/*
HTTP-Tester - file: cookiecache.h - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
*/

#ifndef COOKIECACHE_H
#define COOKIECACHE_H

#include <QObject>
#include <QNetworkCookieJar>

class cookieCache : public QNetworkCookieJar
{

    bool mEnabled;                                      //Indica se la cache è abilitata.

    QList <QUrl> acceptCookieUrls;                      //Unici url da accettare se attiva.

public:
    cookieCache();

    QList<QNetworkCookie> allCookiesList();             //Restituisce tutti i cookie presenti.

    void setAllCookies(const QList<QNetworkCookie> &);  //Restituisce i cookie da associare alla richiesta successiva dopo che i cookie sono stat impostati.

    QList<QNetworkCookie> cookiesForUrl(const QUrl &);  //Impostare una politica di ricezione cookie per url.

    bool setCookiesFromUrl(const QList<QNetworkCookie>&, const QUrl &);

    void setEnabled(bool);

    bool enabled();                                     //Restituisce lo stato.

    void setUrlConstraint(QList <QUrl>);                //Imposta i siti che devono essere rifiutati dall'impostazione dei cookies.
};

#endif // COOKIECACHE_H
