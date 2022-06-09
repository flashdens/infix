#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#ifndef MAIN_C_FUNKCJEALLEGROWE_H
#define MAIN_C_FUNKCJEALLEGROWE_H

int inicjujAllegro() {
    al_init();
    if (!al_init())printf("Blad przy inicjalizacji gry! Skontaktuj sie z sekretariatem WZiKS\n");
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);
    return 0;
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

#endif //MAIN_C_FUNKCJEALLEGROWE_H
