/*
HTTP-Tester - file: showhidebutton.h - Compiler: QT Creator - QT 4.8.5
Exam project - "Telematica A".

Filippo Groppi, Fabrizio Signoretti.
filippo.groppi@studenti.unipr.it; fabrizio.signoretti@studenti.unipr.it

Code repository: "github.com/fasigno/Http-Tester". Under GPLv3.
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
