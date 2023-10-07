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

int initAll();

void updateResultBuf(char *bufor, ALLEGRO_EVENT event);

int generateRandom(int lower, int upper);

void stworzDzialanie(int tab[], int lvl);

#endif //INFIX_UTILS_H
