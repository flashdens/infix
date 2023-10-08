//
// Created by miloszek on 08.10.23.
//

#ifndef INFIX_DRAW_H
#define INFIX_DRAW_H

#include "infix.h"

void drawBase ();

void drawMenu (int lvl);

void drawUI (struct timer timer, int opArray[]);

void drawCharacters (int *sprite, int *klatka, int rozwiazane);

void drawUserGuess (int guess);

void drawVictoryScreen (struct timer timer);

#endif //INFIX_DRAW_H
