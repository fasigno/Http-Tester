/*
HTTP-Tester - file: ShowHideButton.cpp - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
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
