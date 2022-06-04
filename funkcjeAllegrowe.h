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

#ifndef MAIN_C_FUNKCJEALLEGROWE_H
#define MAIN_C_FUNKCJEALLEGROWE_H

int inicjujAllegro() {
    al_init();
    if (!al_init())printf("Blad przy inicjalizacji gry! Skontaktuj sie z sekretariatem WZiKS\n");
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(6);
    return 0;
}

#endif //MAIN_C_FUNKCJEALLEGROWE_H
