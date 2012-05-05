/*
HTTP-Tester - file: bdatadialog.cpp - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
*/

#include "bdatadialog.h"

bdataDialog::bdataDialog(QList< QPair<QString, QString> > bodydata, QWidget *parent) :
    QWidget(parent)
{

    this->setWindowTitle("HTTP-Tester Data");

    //Definizione e proprietà QTableView ::

    rDataList = new QTableView(this);

    Dtable = new TableModel(bodydata); //Allocamento dell'oggetto tablemodel.
    rDataList->setModel(Dtable);

    rDataList->setSelectionBehavior(QAbstractItemView::SelectRows);
    rDataList->horizontalHeader()->setStretchLastSection(true);
    rDataList->verticalHeader()->hide();
    rDataList->setEditTriggers(QAbstractItemView::DoubleClicked);
    rDataList->setSelectionMode(QAbstractItemView::SingleSelection);

    rDataList->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents); //Adatta il contenuto delle celle in base al contenuto.

    //Pulsanti + e - per l'inserimento dei parametri ::
    QPushButton *addHeader = new QPushButton(tr("+"), this);
    QPushButton *rmHeader = new QPushButton(tr("-"), this);

    connect(addHeader, SIGNAL(clicked()), this, SLOT(addDHeader()));
    connect(rmHeader, SIGNAL(clicked()), this, SLOT(rmDHeader()));

    addHeader->setFixedSize(25,25);
    rmHeader->setFixedSize(25,25);

    //Pulsanti su e giù per lo spostamento dell'ordine dei parametri ::
    QPushButton *upLine = new QPushButton(tr("<"), this);
    QPushButton *downLine = new QPushButton(tr(">"), this);

    connect(upLine, SIGNAL(clicked()), this, SLOT(upClicked()));
    connect(downLine, SIGNAL(clicked()), this, SLOT(downClicked()));

    upLine->setFixedSize(25,25);
    downLine->setFixedSize(25,25);

    text = new QLabel(this); text->setText("Accodamento dati alla richiesta ::");

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);

    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));

    //Layouts ::

    QVBoxLayout *vertical = new QVBoxLayout;

    vertical->addWidget(text, Qt::AlignCenter);

    QHBoxLayout *central = new QHBoxLayout;
    QVBoxLayout *centralRight = new QVBoxLayout;

    central->addWidget(rDataList);

    centralRight->addWidget(addHeader);
    centralRight->addWidget(rmHeader);
    centralRight->addWidget(upLine);
    centralRight->addWidget(downLine);

    central->addLayout(centralRight);

    vertical->addLayout(central);
    vertical->addWidget(buttons, Qt::AlignRight);

    this->setLayout(vertical);

    this->centerWindow(); //Centra la finestra sullo schermo.
}

//Inserimento headers in tabella.
void bdataDialog::addEntry(QString header, QString data)
{
    QList< QPair<QString, QString> >list = Dtable->getList();
    QPair<QString, QString> pair(header, data);

    if (!list.contains(pair)) {

        Dtable->insertRows(Dtable->rowCount(QModelIndex()), 1, QModelIndex()); //Aggiunge una nuova riga vuota al modello della tabella in fondo.

        QModelIndex index = Dtable->index(Dtable->rowCount(QModelIndex())-1, 0, QModelIndex());

        Dtable->setData(index, header, Qt::EditRole);
        index = Dtable->index(Dtable->rowCount(QModelIndex())-1, 1, index);
        Dtable->setData(index, data, Qt::EditRole);

    } else {
        QMessageBox::information(this, tr("Duplicate Headers"),
            tr("The header \"%1\" already exists.").arg(header));
    }
}

//Eliminazione headers in tabella.
void bdataDialog::rmEntry() {

    //QTableView *temp = static_cast<QTableView*>(rHeadersList);
    //QSortFilterProxyModel *proxy = static_cast<QSortFilterProxyModel*>(rHeadersList->model());
    QItemSelectionModel *selectionModel = rDataList->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    if (indexes.isEmpty() == false) { //Se è stato selezionato un elemento.

        int row = indexes.at(0).row();
        Dtable->removeRows(row, 1, QModelIndex());
    }

}

//Aggiunge alla listView degli header una riga modificabile - tasto +.
void bdataDialog::addDHeader() {this->addEntry("<Header>", "<Data>");}

//Rimuove l'header selezionato dalla listView - tasto -.
void bdataDialog::rmDHeader() {this->rmEntry();}

//Pulsante ok - form.
void bdataDialog::accept() {

    //Ricezione di tutti gli header inseriti dalla QTableView ::
    QList< QPair<QString, QString> > Headers = Dtable->getList();

    TesterGuiP->setBodyData(Headers);

    this->close();
}

void bdataDialog::centerWindow() {

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

//Pulsante annulla - form.
void bdataDialog::reject() {this->close();}

//Imposta i puntatori.
void bdataDialog::setTesterGuiP(TesterGui * TesterGuiP) {this->TesterGuiP = TesterGuiP;}

//Muove un'entrata della tabella verso su.
void bdataDialog::upClicked() {

    QItemSelectionModel *selectionModel = rDataList->selectionModel(); //Prende il modello di selezione elementi della tabella.
    QModelIndexList indexes = selectionModel->selectedRows(); //Preleva il QModelIndex dell'elemento selezionato.

    if (indexes.size() != 0) {int selectedRow = indexes.at(0).row(); //Viene restituita la posizione dell'elemento selezionato.
    //(Viene restituita una lista ma, selezionando una riga sola alla volta, la pos. dell'elemento nella lista sarà sempre 0).

      if (selectedRow != 0) { //Sposta in su solo se non è la prima riga.

      //Colonna 1:
      QModelIndex selectedRowsC1 = Dtable->index(selectedRow, 0, QModelIndex()); //L'elemento selezionato che si deve spostare su.
      QVariant selectedC1 = Dtable->data(selectedRowsC1, 0); //Viene prelavata la coppia di dati relativa alla riga.

      //Colonna 2:
      QModelIndex selectedRowsC2 = Dtable->index(selectedRow, 1, QModelIndex()); //L'elemento selezionato che si deve spostare su.
      QVariant selectedC2 = Dtable->data(selectedRowsC2, 0); //Viene prelavata la coppia di dati relativa alla riga.

      //Colonna 1:
      QModelIndex moveRowC1 = Dtable->index(selectedRow-1, 0, QModelIndex()); //L'elemento che si deve spostare giù.
      QVariant movedRowC1 = Dtable->data(moveRowC1, 0);

      //Colonna 2:
      QModelIndex moveRowC2 = Dtable->index(selectedRow-1, 1, QModelIndex()); //L'elemento che si deve spostare giù.
      QVariant movedRowC2 = Dtable->data(moveRowC2, 0);

      //Si effettua lo scambio dei dati ricevuti ::
      //Nella posizione selezionata si copiano i dati della riga che precede ::
      Dtable->setData(selectedRowsC1, movedRowC1.toString(), Qt::EditRole);
      Dtable->setData(selectedRowsC2, movedRowC2.toString(), Qt::EditRole);

      //Nella posizione che precede si copiano i dati della riga selezionata ::
      Dtable->setData(moveRowC1, selectedC1.toString(), Qt::EditRole);
      Dtable->setData(moveRowC2, selectedC2.toString(), Qt::EditRole);

      rDataList->selectRow(selectedRow-1); //Si seleziona la riga spostata.


      }

        }

}

//Muove un'entrata della tabella verso giù.
void bdataDialog::downClicked() {

    //Si determina il num. di elementi nella tabella.
    QList< QPair<QString, QString> >list = Dtable->getList();
    int tableSize = list.size();

    QItemSelectionModel *selectionModel = rDataList->selectionModel(); //Prende il modello di selezione elementi della tabella.
    QModelIndexList indexes = selectionModel->selectedRows(); //Preleva il QModelIndex dell'elemento selezionato.

    if (indexes.size() != 0) {int selectedRow = indexes.at(0).row(); //Viene restituita la posizione dell'elemento selezionato.
    //(Viene restituita una lista ma, selezionando una riga sola alla volta, la pos. dell'elemento nella lista sarà sempre 0).

      if (selectedRow != tableSize-1) { //Sposta in su solo se non è la prima riga.

      //Colonna 1:
      QModelIndex selectedRowsC1 = Dtable->index(selectedRow, 0, QModelIndex()); //L'elemento selezionato che si deve spostare giù.
      QVariant selectedC1 = Dtable->data(selectedRowsC1, 0); //Viene prelavata la coppia di dati relativa alla riga.

      //Colonna 2:
      QModelIndex selectedRowsC2 = Dtable->index(selectedRow, 1, QModelIndex()); //L'elemento selezionato che si deve spostare giù.
      QVariant selectedC2 = Dtable->data(selectedRowsC2, 0); //Viene prelavata la coppia di dati relativa alla riga.

      //Colonna 1:
      QModelIndex moveRowC1 = Dtable->index(selectedRow+1, 0, QModelIndex()); //L'elemento che si deve spostare su.
      QVariant movedRowC1 = Dtable->data(moveRowC1, 0);

      //Colonna 2:
      QModelIndex moveRowC2 = Dtable->index(selectedRow+1, 1, QModelIndex()); //L'elemento che si deve spostare su.
      QVariant movedRowC2 = Dtable->data(moveRowC2, 0);

      //Si effettua lo scambio dei dati ricevuti ::
      //Nella posizione selezionata si copiano i dati della riga che precede ::
      Dtable->setData(selectedRowsC1, movedRowC1.toString(), Qt::EditRole);
      Dtable->setData(selectedRowsC2, movedRowC2.toString(), Qt::EditRole);

      //Nella posizione che precede si copiano i dati della riga selezionata ::
      Dtable->setData(moveRowC1, selectedC1.toString(), Qt::EditRole);
      Dtable->setData(moveRowC2, selectedC2.toString(), Qt::EditRole);

      rDataList->selectRow(selectedRow+1); //Si seleziona la riga spostata.

      }

        }

}

