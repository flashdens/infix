//
// Created by milosy on 26/05/2022.
//

#ifndef SAMPLE_FUNKCJEGROWE_H
#define SAMPLE_FUNKCJEGROWE_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <unistd.h>
#include <allegro5/allegro_primitives.h>


int losujLiczbe(int lower, int upper) {
    int liczba = (rand() % (upper - lower + 1)) + lower;
    return liczba;
}

void stworzDzialanie(int tab[], int lvl) { // zwracany jest kod ascii znaku
    srand(time(0));
    tab[0] = losujLiczbe(1 * lvl, 5 * lvl); // liczba1
    tab[1] = losujLiczbe(1 * lvl, 5 * lvl); // liczba2
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
        warunkiOdejmowania:
            if (tab[3] < 0) {
                tab[0] = losujLiczbe(1, 20);
                tab[1] = losujLiczbe(1, 20);
                tab[3] = tab[0] - tab[1];
                goto warunkiOdejmowania;
            }
            return;
        case 2:
            tab[3] = tab[0] * tab[1];
            tab[2] = 42;
            return;
        case 3:
            tab[3] = tab[0] / tab[1];
            tab[2] = 47;
        warunkiDzielenia:
            if (tab[3] <= 0 || tab[0] % tab[1] != 0) {
                tab[0] = losujLiczbe(1 * lvl, 5 * lvl);
                tab[1] = losujLiczbe(1 * lvl, 5 * lvl);
                tab[3] = tab[0] / tab[1];
                goto warunkiDzielenia;
            }
            return;
    }
}

void wprowadzLiczbeDoBufora(char *bufor, ALLEGRO_EVENT event) {
    char x;
    switch (event.keyboard.keycode) {
        case ALLEGRO_KEY_0:
            x = '0';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_1:
            x = '1';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_2:
            x = '2';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_3:
            x = '3';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_4:
            x = '4';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_5:
            x = '5';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_6:
            x = '6';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_7:
            x = '7';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_8:
            x = '8';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_9:
            x = '9';
            bufor = strncat(bufor, &x, 1);
            break;
        case ALLEGRO_KEY_BACKSPACE:
            bufor[strlen(bufor) - 1] = '\0';
            break;
    }

}

#endif //SAMPLE_FUNKCJEGROWE_H
