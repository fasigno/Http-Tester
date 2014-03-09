/*
HTTP-Tester - file: browserviewdialog.cpp - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
*/


#include "browserviewdialog.h"

browserViewDialog::browserViewDialog(QWidget *parent) :
    QWidget(parent)
{

    // Titolo della finestra
    setWindowTitle(tr("HTTP-Tester Body"));

    QVBoxLayout *centralLayout = new QVBoxLayout;

    browser = new QWebView(parent);
    browser->setObjectName(QString::fromUtf8("webView"));
    browser->setUrl(QUrl("about:blank"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    centralLayout->addWidget(browser);
    centralLayout->addWidget(buttonBox);

    this->setLayout(centralLayout);

    this->centerWindow();

}

void browserViewDialog::accept() {this->close();}

void browserViewDialog::centerWindow() {

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

//Riceve il codice html da mostrare.
void browserViewDialog::setHtmlCode(QString htmlCode) {

    browser->setHtml(htmlCode);

    //browser->setFixedHeight(sizeHint().height());
    //browser->setFixedWidth(sizeHint().width());

}

