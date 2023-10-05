//
// Created by miloszek on 05.10.23.
//

#ifndef INFIX_UTILS_H
#define INFIX_UTILS_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int initAll() {
    if (!al_init()) {
        printf("Blad przy inicjalizacji gry! Skontaktuj sie z sekretariatem WZiKS\n");
        return 1;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);
    return 0;
}

void updateResultBuf(char *bufor, ALLEGRO_EVENT event) {
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

int generateRandom(int lower, int upper) {
    int liczba = (rand() % (upper - lower + 1)) + lower;
    return liczba;
}

void stworzDzialanie(int tab[], int lvl) {
    srand(time(0));
    tab[0] = generateRandom(2 * lvl, 5 * lvl); // liczba1
    tab[1] = generateRandom(2 * lvl, 5 * lvl); // liczba2
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
                tab[0] = generateRandom(2 * lvl, 5 * lvl);
                tab[1] = generateRandom(2 * lvl, 5 * lvl);
                tab[3] = tab[0] - tab[1];
            }
            return;
        case 2:
            tab[0] = generateRandom(1 * lvl, 3 * lvl); // nerf mnozenia
            tab[1] = generateRandom(1 * lvl, 3 * lvl);
            tab[3] = tab[0] * tab[1];
            tab[2] = 42;
            return;
        case 3:
            tab[3] = tab[0] / tab[1];
            tab[2] = 47;
            while (tab[3] <= 0 || tab[3] == 1 || tab[0] % tab[1] != 0) {
                tab[0] = generateRandom(1 * lvl, 5 * lvl);
                tab[1] = generateRandom(1 * lvl, 5 * lvl);
                tab[3] = tab[0] / tab[1];
            }
            return;
    }
}

#endif //INFIX_UTILS_H
