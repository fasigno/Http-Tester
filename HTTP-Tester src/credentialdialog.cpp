/*
HTTP-Tester - file: credentialdialog.cpp - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
*/


#include "credentialdialog.h"

credentialDialog::credentialDialog(QWidget *parent) :
    QWidget(parent)
{

    setWindowTitle(tr("Richiesta credenziali")); // Titolo della finestra

    passwd= new QLabel(this); username= new QLabel(this); text= new QLabel(this);

    usernameL= new QLineEdit(this); passwdL= new QLineEdit(this);

    buttons = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);

     connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
     connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));

    vertical= new QVBoxLayout; centralH= new QGridLayout;

        passwd->setText("Password :");
        username->setText("Username :");
        text->setText("Inserire le credenziali per la pagina ::");

        passwdL->setEchoMode(QLineEdit::Password);


    centralH->addWidget(username, 0,0);
    centralH->addWidget(usernameL, 0,1);

    centralH->addWidget(passwd, 1,0);
    centralH->addWidget(passwdL, 1,1);

    vertical->addWidget(text, Qt::AlignCenter);
    vertical->addLayout(centralH);
    vertical->addWidget(buttons, Qt::AlignRight);

    this->setLayout(vertical);
    this->centerWindow();           //Centra la finestra sullo schermo.
}

void credentialDialog::centerWindow() {

    // adatta la finestra secondo i widget, sia in altezza che in larghezza.
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()

      ));
}

void credentialDialog::accept(){

    if(usernameL->text() != "" && passwdL->text() != "") {

    httpfuncsP->setUser(usernameL->text());
    httpfuncsP->setPasswd(passwdL->text());

    } else {

        QMessageBox::warning(this, tr("HTTP-Tester"),
                                        tr("Credenziali incomplete"), QMessageBox::Ok);
        httpfuncsP->setFalseCredError(); //Così alla seconda richiesta non da messaggio di errate credenziali.

    }

    this->close();
}

void credentialDialog::reject(){httpfuncsP->setFalseCredError(); this->close();}

void credentialDialog::sethttpfuncsP(httpfuncs *httpfuncsP){this->httpfuncsP = httpfuncsP;}
