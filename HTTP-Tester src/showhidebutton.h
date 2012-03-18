/*
HTTP-Tester - file: showhidebutton.h - Compilatore: QT Creator - QT 4.7.4.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Luca Barili - 200316, Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
luca.barili@studenti.unipr.it; filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it
*/

#ifndef SHOWHIDEBUTTON_H
#define SHOWHIDEBUTTON_H

#include <QPushButton>

class ShowHideButton : public QPushButton
{

    bool state; //Memorizza lo stato del bottone. False = mostra, True = nasconde.

public:
    ShowHideButton();

    bool returnState();   //Restituisce lo stato attuale del bottone.
    void setState(bool);      //Imposta lo stato del bottone.

};

#endif // SHOWHIDEBUTTON_H
