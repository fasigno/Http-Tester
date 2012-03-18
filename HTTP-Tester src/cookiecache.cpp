/*
HTTP-Tester - file: cookiecache.cpp - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
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



