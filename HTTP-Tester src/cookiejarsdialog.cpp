/*
HTTP-Tester - file: cookieJarSDialog.cpp - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
*/

#include "cookiejarsdialog.h"

cookieJarSDialog::cookieJarSDialog(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.addCookieUrl, SIGNAL(clicked()), this, SLOT(addUrl()));
    connect(ui.rmCookieUrl, SIGNAL(clicked()), this, SLOT(rmUrl()));

    connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(ui.EnableCookieJar, SIGNAL(stateChanged(int)), this, SLOT(enableGUI()));

    init();
    this->centerWindow();
}

//Centra la finestra sullo schermo:
void cookieJarSDialog::centerWindow() {

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

void cookieJarSDialog::init()
{

      model =new QStandardItemModel();

      ui.tableView->setModel(model);
      ui.tableView->setFocusPolicy(Qt::NoFocus);
      ui.tableView->verticalHeader()->hide();
      ui.tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
      ui.tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
      ui.tableView->horizontalHeader()->setStretchLastSection(true);
      ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);

      ui.tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents); //Adatta il contenuto delle celle in base al contenuto.

      model->setHorizontalHeaderLabels(QStringList("URL"));

}

//Pressione annulla.
void cookieJarSDialog::reject() {
    this->close();
}

//Pressione ok.
void cookieJarSDialog::accept() {

    if(ui.EnableCookieJar->isChecked() == true) {

    if(cookieJarState != true) //Se già impostato così non si effettua la reimpostazione.
    httpfuncsp->enableCookieJar(true);

    } else {

    if(cookieJarState != false) //Se già impostato così non si effettua la reimpostazione.
    httpfuncsp->enableCookieJar(false);

    }

    //Si inviano i vincoli alla cache::
    //Che sono una serie di url impostati dall'utente.

    QModelIndex modelIndex;
    QList< QUrl> acceptCookieUrls; //Contiene gli url settati dall'utente che riceveranno i cookies.

    int urlRows = model->rowCount(QModelIndex());

    for (int i =0; i< urlRows; i++) {

        modelIndex = model->index(i, 0, QModelIndex());

        acceptCookieUrls.append(QUrl(model->data(modelIndex).toString()));
    }

    httpfuncsp->setUrlConstraint(acceptCookieUrls);

    this->close();
}

//Rimozione url.
void cookieJarSDialog::rmUrl() {

    QItemSelectionModel *selectionModel = ui.tableView->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows(); //Conterrà una sola riga di selezione.

        if (indexes.isEmpty() == false) { //Se è stato selezionato un elemento.
            int row;
            row = indexes.at(0).row();
            model->removeRow(row);

        }
}

//Aggiunta url.
void cookieJarSDialog::addUrl() {

    QStandardItem *newItem = new QStandardItem("HTTP://");
    int pos = model->rowCount(QModelIndex());
    model->setItem(pos, newItem);
}

//Abilita o disabilita gli oggetti grafici.
void cookieJarSDialog::enableGUI() {

    if(ui.EnableCookieJar->isChecked() == true) {

        ui.tableView->setEnabled(true);
        ui.addCookieUrl->setEnabled(true);
        ui.rmCookieUrl->setEnabled(true);

        //Ripopola la lista se headers sono presenti ::
        QList <QUrl> urls = httpfuncsp->getUrlConstraint();

        for(int i=0; i< urls.size(); i++) {

            QStandardItem *newItem = new QStandardItem(urls.at(i).toString());
            model->setItem(i ,0, newItem);
        }

    } else {

        ui.tableView->setEnabled(false);
        ui.addCookieUrl->setEnabled(false);
        ui.rmCookieUrl->setEnabled(false);

    }
}

//Imposta il puntatore di httpfuncs.
void cookieJarSDialog::setHttpFuncp(httpfuncs *tester) {
    httpfuncsp = tester;
}

//Imposta lo stato attuale della cookieJar per aperture future.
void cookieJarSDialog::setCookieJarState(bool state) {
    cookieJarState = state;
    ui.EnableCookieJar->setChecked(state);
    this->enableGUI();
}


