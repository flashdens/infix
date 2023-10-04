//
// Created by milosy on 26/05/2022.
//

#ifndef SAMPLE_FUNKCJEGROWE_H
#define SAMPLE_FUNKCJEGROWE_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <stdlib.h>


int losujLiczbe(int lower, int upper) {
    int liczba = (rand() % (upper - lower + 1)) + lower;
    return liczba;
}

void stworzDzialanie(int tab[], int lvl) {
    srand(time(0));
    tab[0] = losujLiczbe(2 * lvl, 5 * lvl); // liczba1
    tab[1] = losujLiczbe(2 * lvl, 5 * lvl); // liczba2
    tab[2] = rand() % 4; // znak
    //... a tab[3] to wynik
    switch (tab[2]) {
        case 0:
            tab[3] = tab[0] + tab[1];
            tab[2] = 43;
            return;
        case 1:
            tab[3] = tab[0] - tab[1];
            tab[2] = 45;
            while (tab[3] < 0) {
                tab[0] = losujLiczbe(2 * lvl, 5 * lvl);
                tab[1] = losujLiczbe(2 * lvl, 5 * lvl);
                tab[3] = tab[0] - tab[1];
            }
            return;
        case 2:
            tab[0] = losujLiczbe(1 * lvl, 3 * lvl); // nerf mnozenia
            tab[1] = losujLiczbe(1 * lvl, 3 * lvl);
            tab[3] = tab[0] * tab[1];
            tab[2] = 42;
            return;
        case 3:
            tab[3] = tab[0] / tab[1];
            tab[2] = 47;
            while (tab[3] <= 0 || tab[3] == 1 || tab[0] % tab[1] != 0) {
                tab[0] = losujLiczbe(1 * lvl, 5 * lvl);
                tab[1] = losujLiczbe(1 * lvl, 5 * lvl);
                tab[3] = tab[0] / tab[1];
            }
            return;
    }
}

#endif //SAMPLE_FUNKCJEGROWE_H
