/*
HTTP-Tester - file: viewCookieCache.cpp - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
*/

#include "viewcookiecache.h"
#include "ui_viewcookiecache.h"

viewCookieCache::viewCookieCache(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewCookieCache)
{
    ui->setupUi(this);

    connect(ui->okButtonBox, SIGNAL(accepted()), this, SLOT(accept()));

    this->centerWindow();
}

viewCookieCache::~viewCookieCache()
{
    delete ui;
}

//Ok Dialogo.
void viewCookieCache::accept() { this->close();}

//Centra la finestra sullo schermo:
void viewCookieCache::centerWindow() {

    // adatta la finestra secondo i widget, sia in altezza che in larghezza.
    this->adjustSize();

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
      ));
}

//Imposta il puntatore ad httpfunc e preleva la lista di cookies.
void viewCookieCache::setHttpFuncp(httpfuncs *tester) {

    QString app;
    QList <QNetworkCookie> cookies = tester->getCookiesList();

         for(int i=0; i<cookies.length(); i++) {

             app.append(cookies.at(i).toRawForm() + "\n\n");

         }

     if (app.isEmpty()== true) {

         if(tester->getCookieJarState() == false) {

            app.append("CookieJar not enabled.");

         } else {

             app.append("No cookie setted");
         }

     }

     ui->textEdit->setText(app);

}
