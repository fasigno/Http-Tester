/*
HTTP-Tester - file: showhidebutton.cpp - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
*/


#include "showhidebutton.h"

ShowHideButton::ShowHideButton()
{

    state = false; //Memorizza lo stato del bottone. False = mostra, True = nasconde.
    this->setText("&Hide");
    //    buttons * sender = dynamic_cast<buttons*> (QObject::sender());

}

//Restituisce lo stato attuale del bottone.
bool ShowHideButton::returnState() {return state;}

//Imposta lo stato del bottone.
void ShowHideButton::setState(bool state) {

    switch (state) {

    case true:

        this->state = state;
        this->setText(tr("&Show"));

        break;

    case false:

        this->state = state;
        this->setText(tr("&Hide"));

        break;

    }

}
