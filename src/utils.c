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

#include "utils.h"
#include "operation.h"

#define ASCII_OFFSET 21

int initAll() {
    if (!al_init()) {
        printf("Blad przy inicjalizacji gry! Skontaktuj sie z sekretariatem WZiKS\n");
        return 1;
    }

    if (!al_init()) {
        printf("Error initializing Allegro\n");
        return 1;
    }

    if (!al_init_image_addon()) {
        printf("Error initializing Allegro Image addon\n");
        return 1;
    }

    if (!al_install_keyboard()) {
        printf("Error installing keyboard\n");
        return 1;
    }

    if (!al_install_audio()) {
        printf("Error installing audio\n");
        return 1;
    }

    if (!al_init_acodec_addon()) {
        printf("Error initializing audio codecs\n");
        return 1;
    }

    if (!al_init_font_addon()) {
        printf("Error initializing Allegro Font addon\n");
        return 1;
    }

    if (!al_init_ttf_addon()) {
        printf("Error initializing Allegro TTF addon\n");
        return 1;
    }

    if (!al_reserve_samples(5)) {
        printf("Error reserving samples\n");
        return 1;
    }

    return 0;
}

void updateResultBuf(char *buf, ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
        char pressed = (char) (event.keyboard.keycode + ASCII_OFFSET);
        if (pressed >= '0' && pressed <= '9')
            strncat(buf, &pressed, 1);
        else if (pressed == (char) ALLEGRO_KEY_BACKSPACE + ASCII_OFFSET)
            buf[strlen(buf) - 1] = '\0';
    }
}

int randIntInRange(int lower, int upper) {
    int liczba = (rand() % (upper - lower + 1)) + lower;
    return liczba;
}


#endif //INFIX_UTILS_H
