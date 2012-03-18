/*
HTTP-Tester - file: testergui.cpp - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
*/

#include "testergui.h"
//#include <QPlainTextDocumentLayout>

TesterGui::TesterGui(QWidget *parent)
    : QWidget(parent)
{

    //Inizio disegno grafica preliminare ::

    //! [Grafica]

    // Titolo della finestra
    setWindowTitle(tr("HTTP-Tester"));

    // Configurazione Menù bar ::

    QMenuBar *menu_bar = new QMenuBar; // Menù bar della finestra principale.

    QMenu *menu_file = menu_bar->addMenu(tr("&File"));
    QAction *action_exit = menu_file->addAction(tr("&Esci"));

    QMenu *menu_cache = menu_bar->addMenu(tr("&Cookie Cache"));
    QAction *action_cache = menu_cache->addAction(tr("&Cache settings"));
    QAction *action_viewCookie = menu_cache->addAction(tr("Vi&ew Cookies"));

    QMenu *menu_interfaces = menu_bar->addMenu(tr("&Interfaces"));
    QAction *action_interfaces= menu_interfaces->addAction(tr("&Show Active Interfaces"));

    QMenu *menu_help = menu_bar->addMenu(tr("&?"));
    QAction *action_info = menu_help->addAction(tr("&Info"));

    QObject::connect(action_exit, SIGNAL(activated()),
                     this, SLOT(exitTester()));

    QObject::connect(action_info, SIGNAL(activated()),
                     this, SLOT(about()));

    QObject::connect(action_cache, SIGNAL(activated()),
                     this, SLOT(cookieJarSettings()));

    QObject::connect(action_viewCookie, SIGNAL(activated()),
                     this, SLOT(viewCookies()));

    QObject::connect(action_interfaces, SIGNAL(activated()),
                     this, SLOT(showInterfaces()));

    // Fine configurazione menù bar.

    maximizeWindow(); // Massimizza la finestra all'avvio.

    // Layouts ::
    // layout1 si occupa di formulare la request e corrisponde alla PARTE SUPERIORE della finestra (tutto ciò che sta sopra al Send).
    // layout2 si occupa della response e corrisponde alla PARTE INFERIORE della finestra (tutto ciò che sta sotto al Send).

//================================================================================================================
    // Layout superiore contenente la request ::

    gridGroupBox1 = new QGroupBox(tr("Request Message"), this);
    QGridLayout *layout1 = new QGridLayout();

    // Sezione Customize

    customLabel = new QLabel(tr("Request Line:"), this);
    customLine = new QLineEdit;
    customLine->setReadOnly(true);

    // Sezione per l'host

    urlLabel = new QLabel(tr("URL:"), this);
    urlLine = new QLineEdit(this);
    urlLine->setText("HTTP://");

    connect(urlLine, SIGNAL(returnPressed()), this, SLOT(addHostHeader())); //Slot per l'aggiunta dell'header host quando si aggiunge url della richiesta.
    connect(urlLine, SIGNAL(textEdited(QString)), this, SLOT(showUrltt())); //Slot che mostra il tooltip dell'urline.

    //Sezione pulsante dati richiesta.
    qDataButton = new QPushButton(tr("Query Data"), this);
    connect(qDataButton, SIGNAL(clicked()), this, SLOT(addQData()));

    // ListWidget per la scelta del metodo con cui verrà effettuata la richiesta

    {

    QGroupBox *methodGroup = new QGroupBox(tr("Methods:"));
    methodList = new QListWidget;
    QListWidgetItem *getMethod = new QListWidgetItem(methodList);
    getMethod->setText(tr("GET"));
    QListWidgetItem *postMethod = new QListWidgetItem(methodList);
    postMethod->setText(tr("POST"));
    QListWidgetItem *headMethod = new QListWidgetItem(methodList);
    headMethod->setText(tr("HEAD"));
    QListWidgetItem *optionsMethod = new QListWidgetItem(methodList);
    optionsMethod->setText(tr("OPTIONS"));
    QVBoxLayout *methodLayout = new QVBoxLayout;
    methodLayout->addWidget(methodList);        // L'oggetto methodList è aggiunto al layout methodLayout
    methodGroup->setLayout(methodLayout);       // Impostiamo il layout di methodGroup come methodLayout

    //Imposta la get come metodo di default autoselezionato.
    methodList->setCurrentItem(getMethod);
    reqFlag = GET;

    //methodItemCh(NULL, NULL); //Codice sostituito:
    this->updateCustomLine(); //Viene aggiornata la statusLine che scrive il primo metodo selezionato.

    //Signale/Slot di cambio selezione.
    connect(methodList, SIGNAL(currentItemChanged (QListWidgetItem*, QListWidgetItem*))
            ,this, SLOT(methodItemCh(QListWidgetItem*, QListWidgetItem*)));

    // TableWidget per l'introduzione degli header di richiesta.
    QGroupBox *rHeadersGroup = new QGroupBox(tr("Request Headers:"), this);
    rHeadersList = new QTableView(this);

    Htable = new TableModel(this); //Allocamento dell'oggetto tablemodel.
    rHeadersList->setModel(Htable);

    //Solo prova
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(Htable);
    //proxyModel->setDynamicSortFilter(true);
    //Fine prova

    rHeadersList->setModel(proxyModel);
    //rHeadersList->setSortingEnabled(true);
    rHeadersList->setSelectionBehavior(QAbstractItemView::SelectRows);
    rHeadersList->horizontalHeader()->setStretchLastSection(true);
    rHeadersList->verticalHeader()->hide();
    rHeadersList->setEditTriggers(QAbstractItemView::DoubleClicked);
    rHeadersList->setSelectionMode(QAbstractItemView::SingleSelection);

    rHeadersList->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents); //Adatta il contenuto delle celle in base al contenuto.

    //Pulsanti + e - per l'inserimento dei parametri.
    QPushButton *addHeader = new QPushButton(tr("+"), this);
    QPushButton *rmHeader = new QPushButton(tr("-"), this);

    connect(addHeader, SIGNAL(clicked()), this, SLOT(addQHeader()));
    connect(rmHeader, SIGNAL(clicked()), this, SLOT(rmQHeader()));

    addHeader->setFixedSize(25,25);
    rmHeader->setFixedSize(25,25);

    QVBoxLayout *rHeadersLayout = new QVBoxLayout();
    rHeadersLayout->addWidget(rHeadersList);    // L'oggetto protocolList è aggiunto al layout protocolLayout
    rHeadersGroup->setLayout(rHeadersLayout);   // Impostiamo il layout di protocolGroup come protocolLayout

    layout1->addWidget(customLabel,1,0);
    layout1->addWidget(customLine,1,1);
    layout1->addWidget(urlLabel,2,0);
    layout1->addWidget(urlLine,2,1);
    layout1->addWidget(qDataButton, 2, 2);      //Allineamento temporaneo con riga url.
    layout1->addWidget(methodGroup,3,0);
    layout1->addWidget(rHeadersGroup,3,1);
    gridGroupBox1->setLayout(layout1);

    //gridGroupBox1->setMaximumHeight(250);       //Imposta lo stiramento massimo in verticale del Box.

    //Pulsanti + e - con layout verticale..
    QVBoxLayout *headersButtons = new QVBoxLayout();
    headersButtons->addWidget(addHeader);
    headersButtons->addWidget(rmHeader);
    headersButtons->setSpacing(0);

    // Bottone per inviare la request
    sendButton = new QPushButton(tr("&Send"), this);
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendRequest()));
    sendButton->setFixedSize(115,35); //era 120,40.

    //Animazione di attesa difianco al SendButton :
    //In una qlabel.
    idleMovie = new QMovie(":/resources/loading.gif");
    movieLabel = new QLabel();
    movieLabel->setFixedSize(35,35);
    movieLabel->setMovie(idleMovie);    //Si imposta l'animazione di attesa nella label.

    layout1->addLayout(headersButtons, 3, 2);

    //Layout orizzontale per tasto button e animazione :
    QBoxLayout *sendAnimLayout= new QBoxLayout(QBoxLayout::LeftToRight);
    sendAnimLayout->addWidget(sendButton);
    sendAnimLayout->addWidget(movieLabel); //Movie Label di fianco al send.
    //sendAnimLayout->setSpacing(20);
    sendAnimLayout->addStretch();

    layout1->addLayout(sendAnimLayout, 4, 0);

    }

//================================================================================================================

    //Configurazione della scrollbar ::

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setFrameShape(QFrame::NoFrame); //Toglie il riquadro della scollArea.

    //Fine configurazione della scrollbar ::

    // Layout inferiore contenente la response ::
    gridGroupBox2 = new QGroupBox(tr("Server-Response"), this);
    gridGroupBox2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); //INUTILE PER IL MOMENTO.


    QGridLayout *layout2 = new QGridLayout(this);
    layout2->setSizeConstraint(QLayout::SetNoConstraint);
    QHBoxLayout *statuslineLayout = new QHBoxLayout();

    statusLabel = new QLabel(tr("Status-Line:"), this);
    statusLine = new QLineEdit(this);
    statusLine->setReadOnly(true);

    statuslineLayout->addWidget(statusLabel);
    statuslineLayout->addWidget(statusLine);

    reHeaderGroupBox = new QGroupBox(tr("Response Headers"), this);
    QGridLayout *layoutHeader = new QGridLayout();

    // QTextEdit che contiene il body della response
    reHeader = new QTextEdit(this);

    reHeader->setReadOnly(true);
    reHeader->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //scrollArea->setWidget(reHeader);

    connect(reHeader, SIGNAL(textChanged()), this, SLOT(adaptTextHeader())); //Evento ridimensionamento automatico dei QTextEdit in base al testo.

    // Bottone per salvare il body della response
    saveHeader = new QPushButton(tr("&Save as..."), this);
    saveHeader->setFixedSize(100,20); //Era 120*40.
    saveHeader->setEnabled(false); //Viene disabilitato all'avvio.
    connect(saveHeader, SIGNAL(clicked()), this, SLOT(saveHeaderDialog())); //Slot dialogo salva headers.

    reBodyGroupBox = new QGroupBox(tr("Response Body"), this);

    //Layout orizzontale che contiene il button per il salvataggio dell'header.
    QBoxLayout *headerBottomButtons = new QBoxLayout(QBoxLayout::LeftToRight);
    headerBottomButtons->addWidget(saveHeader,1,0);
    headerBottomButtons->addStretch();

    QGridLayout *layoutBody = new QGridLayout();

    //Pulsanti mostra/nascondi headers/body::
    shHeaderButton = new ShowHideButton();
    connect(shHeaderButton, SIGNAL(clicked()), this, SLOT(showhideHeader()));

    shBodyButton = new ShowHideButton();
    connect(shBodyButton, SIGNAL(clicked()), this, SLOT(showhideBody()));

    reBody = new QTextEdit(this);
    reBody->setReadOnly(true);
    reBody->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); //<============================ CONTROLLARE!!!!
    //scrollArea->setWidget(reBody);

    connect(reBody, SIGNAL(textChanged()), this, SLOT(adaptTextBody())); //Evento ridimensionamento automatico dei QTextEdit in base al testo.
                                                                         //Abilitazione dei tasti funzione relativi alla sezione.

    saveBody = new QPushButton(tr("&Save as..."), this);
    saveBody->setFixedSize(100,20); //Era 120*40.
    saveBody->setEnabled(false); //Viene disabilitato all'avvio.
    connect(saveBody, SIGNAL(clicked()), this, SLOT(saveBodyDialog())); //Slot dialogo salva body.

    browserView = new QPushButton(tr("Browser View"),this);
    browserView->setFixedSize(100,20);
    browserView->setEnabled(false); //Viene disabilitato all'avvio.
    connect(browserView, SIGNAL(clicked()), this, SLOT(viewBodyBrowser()));

    layoutHeader->addWidget(reHeader,1,0);
    layoutHeader->addLayout(headerBottomButtons,2,0);

    reHeaderGroupBox->setLayout(layoutHeader);

    layoutBody->addWidget(reBody,1,0);

    //Layout orizzontale che contiene i button per la sezione body.
    QBoxLayout *bodyBottomButtons = new QBoxLayout(QBoxLayout::LeftToRight);

    bodyBottomButtons->addWidget(saveBody);
    bodyBottomButtons->addWidget(browserView);
    bodyBottomButtons->setSpacing(20);
    bodyBottomButtons->addStretch();

    layoutBody->addLayout(bodyBottomButtons, 2, 0);

    reBodyGroupBox->setLayout(layoutBody);

    layout2->addLayout(statuslineLayout, 0, 0);

    layout2->addWidget(reHeaderGroupBox,3,0);
    layout2->addWidget(shHeaderButton,3,1);

    layout2->addWidget(reBodyGroupBox,4,0);
    layout2->addWidget(shBodyButton,4,1);

    gridGroupBox2->setLayout(layout2);

    exitButton = new QPushButton(tr("&Exit"), this);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitTester()));
    exitButton->setFixedSize(115,35); //Era 120,40.

    QGridLayout *mainLayout = new QGridLayout();          //Layout globale della finestra.

    mainLayout->addWidget(menu_bar, 0, 0);
    mainLayout->addWidget(gridGroupBox1, 1, 0);

    scrollArea->setWidget(gridGroupBox2);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(scrollArea, 2, 0);
    mainLayout->addWidget(exitButton, 3, 0);

    this->setLayout(mainLayout);                          //Imposta il layout fondamentale della finestra.

    //Fine disegno grafica preliminare::

    //! [Grafica]

    this->defaultHeaders(); // Imposta gli headers di default all'apertura.

    //Si nascondono le sezioni dei dati ricevuti all'avvio del programma.
    this->showhideHeader();
    this->showhideBody();

    this->setMinimumSize(1024, 600);                     //Grandezza minima che la finestra può assumere.

    //Creazione dell'oggetto che contiene il codice operativo :
    //Passaggio al costruttore.
    tester = new httpfuncs(this);

}

TesterGui::~TesterGui() {} //Distruttore.

//Graphic Functions ::

// Funzione per massimizzare la finestra
void TesterGui::maximizeWindow() {
    this->showMaximized();
}

// Funzione per nascondere o mostrare la sezione riguardante l'header
void TesterGui::showhideHeader() {

    switch(shHeaderButton->returnState()) {

    case false:

        shHeaderButton->setState(true);
        reHeader->hide();
        saveHeader->hide();

        break;

    case true:

        shHeaderButton->setState(false);
        reHeader->show();
        saveHeader->show();

        break;

    }
}

// Funzione per nascondere o mostrare la sezione riguardante il body.
void TesterGui::showhideBody() {

    switch(shBodyButton->returnState()) {

    case false:

        shBodyButton->setState(true);
        reBody->hide();
        saveBody->hide();
        browserView->hide();

        break;

    case true:

        shBodyButton->setState(false);
        reBody->show();
        saveBody->show();
        browserView->show();

        break;

    }
}

// Funzione per uscire dal Tester
void TesterGui::exitTester() {
    this->close();
}

void TesterGui::about()
{

    QString info;

    info.append("HTTP-Tester\n"
                "Progetto d'esame - Telematica A,\n"
                "Corso di laurea in ingegneria informatica.\n"

                "\nLuca Barili - 200316, luca.barili@studenti.unipr.it;\n"
                "Filippo Groppi - 201810, filippo.groppi@studenti.unipr.it;\n"
                "Fabrizio Signoretti - 201216, fabrizio.signoretti@studenti.unipr.it\n"

                "\nAmbiente: QT Creator - QT 4.7.4.\n\n Parma 2010/2011"
                );

    QMessageBox::information(this, tr("Info"), tr("%1").arg(info));
}

// End Graphic Functions.

//Viene richiamata alla fine della richiesta e ottiene i dati ricevuti.
void TesterGui::requestFinished() {

    //Ricezione di headers e body ::
    rGData = tester->getReplyBody();
    rGHeaders = tester->getReplyHeaders();

    //Visualizzazione di header e body ::
    //Visualizza i dati negli oggetti del form nascondendo le parti non ricevute.

    //Body ::
    reBody->clear();
    reBody->setPlainText(rGData);

    QString hString; //Contiene la stringa di headers che verrà visualizzata.

    //Headers ::
    reHeader->clear();

    for(int i=0; i< rGHeaders.length(); i++) {

        hString += rGHeaders.at(i).first + " = " + rGHeaders.at(i).second + "\n";

    }

    reHeader->setPlainText(hString);

    //Si nascondono le parti non ricevute ::
    //Se rGData == 0 non visualizza il body.
    //Se rGHeaders == 0 non visualizza gli header.

    //Si deve impostare lo stato contrario a quello desiderato che poi lo slot inverte.
    if (reBody->toPlainText() == "") {shBodyButton->setState(false); this->showhideBody();} else {shBodyButton->setState(true); this->showhideBody();}
    if (reHeader->toPlainText() == "") {shHeaderButton->setState(false); this->showhideHeader();} else {shHeaderButton->setState(true); this->showhideHeader();}

    sendButton->setEnabled(true);  //Si riabilita il pulsante send alla fine della richiesta.

    idleMovie->stop();             //Si ferma l'animazione e si cancella la label.
    movieLabel->clear();

    this->addHostHeader();         //Viene richiamata per l'aggiunta degli header cookie per future richieste.

}

//Inserimento headers in tabella.
void TesterGui::addEntry(QString header, QString data)
{
    QList< QPair<QString, QString> >list = Htable->getList();
    QPair<QString, QString> pair(header, data);

    if (!list.contains(pair)) {

        Htable->insertRows(Htable->rowCount(QModelIndex()), 1, QModelIndex()); //Aggiunge una nuova riga vuota al modello della tabella in fondo.

        QModelIndex index = Htable->index(Htable->rowCount(QModelIndex())-1, 0, QModelIndex());

        Htable->setData(index, header, Qt::EditRole);
        index = Htable->index(Htable->rowCount(QModelIndex())-1, 1, index);
        Htable->setData(index, data, Qt::EditRole);

    } else {
        QMessageBox::information(this, tr("Duplicate Headers"),
            tr("The header \"%1\" already exists.").arg(header));
    }
}

//Eliminazione headers in tabella.
void TesterGui::rmEntry() {

    QItemSelectionModel *selectionModel = rHeadersList->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows(); //Conterrà una sola riga di selezione.

    if (indexes.isEmpty() == false) { //Se è stato selezionato un elemento.
        int row;
        row = indexes.at(0).row();

        //________________
        //Prima dell'eliminazione viene impostato l'header vuoto, per richieste successive.

        //QList< QPair<QString, QString> >list = Htable->getList();
        QString removedHeader = Htable->data(indexes.at(0), Qt::DisplayRole).toString(); // si preleva l'header che si vuole eliminare.

        QByteArray p; p.append(removedHeader);
        tester->setRequestHeader(p, QByteArray(" "));                                    // lo si resetta per la richiesta.

        //________________

        Htable->removeRows(row, 1, QModelIndex()); //Lo si elimina dal modello.
    }

}

//---SLOTS ::

void TesterGui::methodItemCh(QListWidgetItem*, QListWidgetItem*) {

    url.clear(); //Si azzera l'URL eventualmente preimpostato da altre richieste.

    //Appoggio richiesta POST.
    QList< QPair<QString, QString> >list;
    int pos=-1;
    int posL=-1;

    //=====================================================================================

    //Eliminazione del campo Content-Type e il Content-Length se precedentemente impostato.
    //Si è optato per l'eliminazione dato che 3 metodi su 4 non li usano.

    if (Htable != NULL) {

    list = Htable->getList();

    for(int i=0; i<list.size(); i++) {

        if (list.at(i).first == "Content-Type") {pos = i;}
        if (list.at(i).first == "Content-Length") {posL = i;}

    }

    if (pos != -1) { Htable->removeRows(pos, 1, QModelIndex());}
    if (posL != -1) { Htable->removeRows(pos, 1, QModelIndex());}

    list.clear();
    pos = -1;

    }

    //======================================================================================


    switch(methodList->currentRow()) {

    case 0: reqFlag = GET;
        customLine->setText("GET / HTTP/1.1");
        qDataButton->setEnabled(true); //Viene sbloccato il tasto per l'accodamento dei dati.

        if(bodydata.isEmpty() == false)
        this->setBodyData(this->bodydata); //Vengono reimpostati tutti i parametri GET finora impostati.

        break;

    case 1: reqFlag = POST;
        customLine->setText("POST / HTTP/1.1");
        qDataButton->setEnabled(true); //Viene sbloccato il tasto per l'accodamento dei dati.

        //Inserimento Header "Content-Type" e controllo duplicato.
        //Si determina il num. di elementi nella tabella.

        list = Htable->getList();

        for(int i=0; i<list.size(); i++) {

            if (list.at(i).first == "Content-Type") {pos = i; break;}

        }

        if (pos == -1) {this->addEntry("Content-Type", "application/x-www-form-urlencoded");}

        if(bodydata.isEmpty() == false)
        this->setBodyData(this->bodydata); //Viene richiamata la funzione che aggiorna il Content-Length per la richiesta POST.

        break;

    case 2: reqFlag = HEAD;
        customLine->setText("HEAD / HTTP/1.1");
        qDataButton->setEnabled(false); //Viene bloccato il tasto per l'accodamento dei dati.
        break;

    case 3: reqFlag = OPTIONS;
        customLine->setText("OPTIONS * HTTP/1.1");
        qDataButton->setEnabled(false); //Viene bloccato il tasto per l'accodamento dei dati.
        break;

    }

    this->addHostHeader(); //Viene ripristinato l'url se impostato precedentemente e riaggiornata la customline.

}

// Funzione che effettua l'invio della request
void TesterGui::sendRequest() {

    //Controllo casella url vuota o incompleta.
    if(urlLine->text().isEmpty() == true || QString::compare("http://", urlLine->text(), Qt::CaseInsensitive) == 0) {
        QMessageBox::information(this, tr("Mancato inserimento dell'url"), tr("%1").arg("Url Mancante!"));
        return;}

    sendButton->setEnabled(false);      //Si disabilita il pulsante send all'invio della richiesta.
    movieLabel->setMovie(idleMovie);    //Si imposta l'animazione di attesa nella label.
    idleMovie->start();                 //Si fa partire l'animazione di attesa.


    //Ricezione di tutti gli header inseriti dalla QTableView ::
    QList< QPair<QString, QString> > Headers = Htable->getList();

    //Settaggio di tutti gli header inseriti ::
    for(int i=0; i<Headers.length(); i++) {

        QByteArray head1, data1;

        head1.append(Headers.at(i).first);
        data1.append(Headers.at(i).second);

        tester->setRequestHeader(head1, data1);
    }

    //Svolge la richiesta ::
    switch(reqFlag) {

    case GET:
        tester->sendRequest(httpfuncs::GET);
        break;

    case POST:

        //La stringa dei dati precedentemente pronta viene inviata con la richiesta.
        tester->sendRequest(httpfuncs::POST, &encodedQueryData);

        break;

    case HEAD:

        tester->sendRequest(httpfuncs::HEAD);

        break;

    case OPTIONS:

        tester->sendRequest(httpfuncs::OPTIONS);

        break;

    }
}

//Funzione che mostra il form inserimento dati da accodare alla richiesta.
void TesterGui::addQData() {

    bdataDialog *bdata = new bdataDialog(bodydata);
    bdata->setTesterGuiP(this);
    bdata->show();
}

//Mostra gli headers di default.
void TesterGui::defaultHeaders(){ //I due punti, capire perchè g...

    this->addEntry("Connection", "Keep-Alive");
    this->addEntry("Accept-Encoding", "gzip");
    this->addEntry("Accept-Language", "it-IT,en,*");
    this->addEntry("User-Agent", "Mozilla/5.0");

//      this->addEntry("Connection", "Close");
//      this->addEntry("Accept-Encoding", "gzip, deflate");
//      this->addEntry("Accept-Language", "it-IT,en,*");
//      this->addEntry("Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7");
//      this->addEntry("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:8.0.1) Gecko/20100101 Firefox/8.0.1");
//      this->addEntry("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

}

//Aggiunge alla listView degli header una riga modificabile.
void TesterGui::addQHeader() {this->addEntry("<Header>", "<Data>");}

//Rimuove l'header selezionato dalla listView.
void TesterGui::rmQHeader() {this->rmEntry();}

//Viene richiamata all'inserimento di parametri GET che modificano la sintassi della richiesta.
//e all'invio dopo aver cambiato l'urlLine.
void TesterGui::updateCustomLine() {

    //Reset della custom line per richieste successive o cambio dei parametri/pagina.

    QString newCustomLine = "";
    QString line = url.toString();

    switch(reqFlag) {

    case GET:
        newCustomLine.append("GET / HTTP/1.1");
        break;

    case POST:
        newCustomLine.append("POST / HTTP/1.1");
        break;

    case HEAD:
        newCustomLine.append("HEAD / HTTP/1.1");
        break;

    case OPTIONS:
        newCustomLine.append("OPTIONS * HTTP/1.1");
        return; //Con la options non si deve modificare la statusLine.
        break;  //Inutile, ma del costrutto.

    }

    //Si effettua un parsing di line da porre dopo / nella richiesta.

    QString params="";
    QString app="";
    QUrl urlPath;

    int i = line.lastIndexOf('?');

    if (i != -1) { //Se ci sono parametri nell'url impostato.

        i = line.length() - i;
        params = line.right(i);

    }

    urlPath = QUrl(line);
    app = urlPath.encodedPath();

    if(params.isEmpty() == false && app.isEmpty() == true) { // Se ci sono parametri ma non c'è path.
        //Si aggiunge uno slash alla fine del sito.
        //Se il sito è stato inserito!

        if (urlLine->text().isEmpty() == false && QString::compare("http://", urlLine->text(), Qt::CaseInsensitive) != 0)
        urlLine->setText(urlLine->text() + '/');

        app.append('/');
    }

    app.append(params);             //Riga pronta con path e parametri.

    if (app.isEmpty() == false) {   //Se non è stato inserito un sito senza path, nè parametri.

    int pos = /*newCustomLine.lastIndexOf("/");*/ 10; //La funzione non si comporta come dovrebbe, è stato fissato un valore numerico!
    pos = newCustomLine.length() - pos;
    newCustomLine.replace(pos ,1, app);

    }

    customLine->setText(newCustomLine);

}

//Riceve i dati dal form btdata da accodare alla richiesta.
void TesterGui::setBodyData(QList< QPair<QString, QString> > bodydata) {

    this->bodydata = bodydata; //Contiene i dati da accodare alla richiesta.

    url.setUrl(urlLine->text());

    if(reqFlag == GET) {

        //Settaggio di tutti i dati inseriti ::
        for(int i=0; i<bodydata.length(); i++) {

            QByteArray head1, data1;

            head1.append(bodydata.at(i).first);
            data1.append(bodydata.at(i).second);

            url.addQueryItem(head1, data1);

        }

    } else if (reqFlag == POST) { //Se la richiesta è una post qui si setta l'header content-lengh.
                                  //I dati invece vengono accodati al momento dell'invio della richiesta.

        //Variabili di appoggio per i dati della richiesta POST.
        QUrl postData;

        for(int i=0; i<bodydata.length(); i++) {

            postData.addQueryItem(bodydata.at(i).first, bodydata.at(i).second);

        }

        encodedQueryData = postData.encodedQuery();

        //===============================================================================
        //Si prepara il campo Content-Length::

        QString encodedQueryDataSize;
        encodedQueryDataSize.setNum(encodedQueryData.size());

        //===============================================================================
        //Se presente una vecchia copia dell'header si elimina::

        //Si determina il num. di elementi nella tabella.
        QList< QPair<QString, QString> >list = Htable->getList();
        int pos=-1;

        for(int i=0; i<list.size(); i++) {

            if (list.at(i).first == "Content-Length") {pos = i; break;}

        }

        if (pos != -1) { Htable->removeRows(pos, 1, QModelIndex());}

        this->addEntry("Content-Length",encodedQueryDataSize); //Si setta il nuovo header.

    }

    tester->setRequestUrl(url);

    this->updateCustomLine();
}

//Mostra le intefacce attive.
void TesterGui::showInterfaces() {

    if (tester->ninterfaces().isEmpty() == false) {
      QMessageBox::information(this, tr("Active Interfaces"), tr("%1").arg(tester->ninterfaces()));
    } else {
        QMessageBox::information(this, tr("Active Interfaces"),tr("No Active Interfaces Detected"));
    }

}

//Adatta automaticamente la grandezza dei QLineEdit in base al testo e abilita/disabilita i tasti funzione.
void TesterGui::adaptTextBody() {

    //Ridimensionamento ::

    QString text=reBody->toPlainText();
    int h=text.split('\n').length();

    int pH=reBody->fontMetrics().height();
    reBody->setFixedHeight((h+1)*pH);

    //Abilitazione/disabilitazione tasti funzione ::
    if (text.isEmpty() == true) {

        saveBody->setEnabled(false);
        browserView->setEnabled(false);

    } else {

        saveBody->setEnabled(true);
        browserView->setEnabled(true);

    }

}

void TesterGui::adaptTextHeader() {

    //Ridimensionamento ::

    QString text=reHeader->toPlainText();
    int h=text.split('\n').length();

    int pH=reHeader->fontMetrics().height();
    reHeader->setFixedHeight((h+1)*pH);

    //Abilitazione/disabilitazione tasti funzione ::
       if (text.isEmpty() == true) {

           saveHeader->setEnabled(false);

       } else {

           saveHeader->setEnabled(true);

       }

}

//Slot per l'aggiunta dell'header host quando si aggiunge url della richiesta, viene inoltre aggiornata la requestLine.
void TesterGui::addHostHeader() {

        urlLine->setToolTip("Premere Invio al termine.");

        //Controllo coerenza campo url ::

        //Controllo casella url vuota o incompleta.
        if(urlLine->text().isEmpty() == true || QString::compare("http://", urlLine->text(), Qt::CaseInsensitive) == 0) { return;}

        url.setUrl(urlLine->text());

        if (url.encodedPath() == "") { //Se non è stato inserito il path viene aggiunto all'url.
                                       //Se ci sono parametri il path nella urLine verrà inserito in updateCustomLine.
            url.setPath("/");

        }

        //Controllo validità url inserito. (NON OTTIMO)
        if (!url.isValid() == true) {

            QMessageBox::warning(this, tr("Url non valido"), tr("L'url %1 inserito non e' valido!").arg(urlLine->text()));
            return;
        }

        if (reqFlag == GET) {

                //Risettaggio degli eventuali header GET inseriti ::
                for(int i=0; i<bodydata.length(); i++) {

                    QByteArray head1, data1;

                    head1.append(bodydata.at(i).first);
                    data1.append(bodydata.at(i).second);

                    url.addQueryItem(head1, data1);

                }

        }

    tester->setRequestUrl(url); //Viene impostato l'url della richiesta nel tester.

    //Settaggio dell'header Host (Verifica se già presente una copia vecchia, se si la elimina)::

    //Si determina il num. di elementi nella tabella.
    QList< QPair<QString, QString> >list = Htable->getList();
    int pos=-1;

    for(int i=0; i<list.size(); i++) {

        if (list.at(i).first == "Host") {pos = i; break;}

    }

    if (pos != -1) { Htable->removeRows(pos, 1, QModelIndex());}

    this->addEntry("Host", url.encodedHost());

    //=___________________________________________________________________________________________
    //
    //Cookie Section ::
    //Se la cookieCache è impostata si deve inserire il setCookie passato precedentemente:
    //
    //Se la cookieCache è impostata ma il sito in questione non presenta cookies precedentemente
    //settati deve essere tolto l'header.

    //Vengono restituiti i cookie settati dal server per l'url :
    QList <QNetworkCookie> urlCookies;
    urlCookies = tester->cookiesForUrl(url);

    QString cookiesString = "";

    if (urlCookies.isEmpty() == false) {

        for(int i = 0; i < urlCookies.size()-1; i++) {

            cookiesString.append(urlCookies.at(i).toRawForm(QNetworkCookie::NameAndValueOnly) + ";");

        }

        cookiesString.append(urlCookies.at(urlCookies.size()-1).toRawForm(QNetworkCookie::NameAndValueOnly));

        //Si elimina l'eventuale copia precedente dei cookie:

        //Si determina il num. di elementi nella tabella.
        QList< QPair<QString, QString> >list = Htable->getList();
        int pos=-1;

        for(int i=0; i<list.size(); i++) {

            if (list.at(i).first == "Cookie") {pos = i; break;}

        }

        if (pos != -1) { Htable->removeRows(pos, 1, QModelIndex());}

        this->addEntry("Cookie", cookiesString); //Si aggiunge l'header dei cookies.

    } else { //Se non sono presenti cookie precedentemente settati per l'url.

        //Si elimina l'eventuale copia precedente dei cookie:

        //Si determina il num. di elementi nella tabella.
        QList< QPair<QString, QString> >list = Htable->getList();
        int pos=-1;

        for(int i=0; i<list.size(); i++) {

            if (list.at(i).first == "Cookie") {pos = i; break;}

        }

        if (pos != -1) { Htable->removeRows(pos, 1, QModelIndex());}

    }

    //=___________________________________________________________________________________________

    this->updateCustomLine();                     //Viene aggiornata la customLine.

}

//Mostra un dialogo con il body nel browser.
void TesterGui::viewBodyBrowser() {

    if (rGData.isEmpty() == false) {
    browserViewDialog *bdialog = new browserViewDialog;
    bdialog->setHtmlCode(rGData); // Invio del codice html al dialogo.
    bdialog->show();
    }

}

//Mostra un dialogo per il salvataggio del body ricevuto.
void TesterGui::saveBodyDialog() {

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Body to file"),
                               "./Body.html",
                               tr("HTML (*.html *.htm)"));

    //Per l'apertura di soli file :: QFileDialog::AnyFile;

    if (fileName.isEmpty() != true)
    tester->saveOnfile(fileName, true); //True salva il body.
}

//Mostra un dialogo per il salvataggio degli headers ricevuti.
void TesterGui::saveHeaderDialog() {

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Headers to file"),
                               "./Headers.text",
                               tr("Text files (*.txt *.text)"));

    //Per l'apertura di soli file :: QFileDialog::AnyFile;

    if (fileName.isEmpty() != true)
    tester->saveOnfile(fileName, false); //False salva gli headers.
}

//Aggiorna la statusLine con l'esito della richiesta http.

void TesterGui::setStatusLine(QString status){

    statusLine->setText(status);

}

//Slot che mostra il tooltip dell'urline.
void TesterGui::showUrltt() {

    QToolTip::showText(QPoint(urlLine->pos().x(),urlLine->pos().y()*2+10), "Premere invio al termine", urlLine);

}

//Mostra il dialogo di impostazione cookieJar.
void TesterGui::cookieJarSettings() {

    cookieJarSDialog *cj = new cookieJarSDialog;
    cj->setHttpFuncp(tester);
    cj->setCookieJarState(tester->getCookieJarState()); //Si imposta nella grafica lo stato attuale della cookieJar.
    cj->show();
}

//Mostra il dialogo di visualizzazione cookies.
void TesterGui::viewCookies() {

    viewCookieCache *vck = new viewCookieCache;
    vck->setHttpFuncp(tester);
    vck->show();
}



