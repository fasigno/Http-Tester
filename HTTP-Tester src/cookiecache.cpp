/*
HTTP-Tester - file: cookiecache.cpp - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
*/


#include "cookiecache.h"
#include <QDebug>

cookieCache::cookieCache()
{
    mEnabled = false;
}

QList<QNetworkCookie> cookieCache::allCookiesList() { //Restituisce tutti i cookie presenti.
    return this->allCookies();
}


void cookieCache::setAllCookies(const QList<QNetworkCookie>& cookieList) {

    if(mEnabled)
        return QNetworkCookieJar::setAllCookies(cookieList);
}

QList<QNetworkCookie> cookieCache::cookiesForUrl(const QUrl &url) { //Restituisce i cookie da associare alla richiesta successiva dopo che i cookie sono stati impostati.

    if(mEnabled) { //Se abilitata.

        //Restituisce il cookie solo se la lista dei cookies è vuota oppure il sito è in elenco.
        if (acceptCookieUrls.isEmpty() == true || acceptCookieUrls.contains(url.toString(QUrl::StripTrailingSlash))) {

            return QNetworkCookieJar::cookiesForUrl(url);

        } else {

            return QList<QNetworkCookie>();
        }

    } else {
        return QList<QNetworkCookie>();
    }
}


bool cookieCache::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url) {

    if(mEnabled ) {

        //Imposta il cookie solo se la lista dei cookies è vuota oppure il sito è in elenco.

        if (acceptCookieUrls.isEmpty() == true || acceptCookieUrls.contains(url.toString(QUrl::StripTrailingSlash)) == true) {

            return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);

        } else {
            return false;
        }

    } else {

        return false;
    }
}

void cookieCache::setEnabled(bool enabled) { //Abilitazione o disabilitazione della cache.

    if(mEnabled != enabled) {

        mEnabled = enabled;

        QList<QNetworkCookie> p; //cancellazione di tutti i cookies.
        p.clear();               //Inizializzazione vuoto.
        this->setAllCookies(p);  //Si cancellano impostandoli a 0.

    }
}

bool cookieCache::enabled() {
    return mEnabled;
}

//Imposta i siti che devono essere rifiutati dall'impostazione dei cookies.
void cookieCache::setUrlConstraint(QList <QUrl> urls) {
    acceptCookieUrls = urls;
}




