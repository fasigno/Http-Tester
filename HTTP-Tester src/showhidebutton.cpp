/*
HTTP-Tester - file: showhidebutton.cpp - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
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
