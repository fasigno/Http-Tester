/*
HTTP-Tester - file: showhidebutton.h - Compiler: QT Creator - QT 4.8.
Progetto d'esame - "Telematica A", corso di laurea in ingegneria informatica.

Filippo Groppi - 201810, Fabrizio Signoretti - 201216.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code site: "github.com/fasigno/Http-Tester".
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
