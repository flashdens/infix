#ifndef INFIX_GLOBALS_H
#define INFIX_GLOBALS_H

#include <allegro5/allegro.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>

// infix.c
extern ALLEGRO_EVENT event;
extern ALLEGRO_EVENT_QUEUE *queue;
extern ALLEGRO_TIMER *allegroTimer;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_KEYBOARD_STATE keyState;

extern ALLEGRO_SAMPLE *menu;
extern ALLEGRO_SAMPLE *gameSt;
extern ALLEGRO_SAMPLE *ok;
extern ALLEGRO_SAMPLE *win;


// draw.c
extern ALLEGRO_FONT *comicSmall;
extern ALLEGRO_FONT *comicLarge;
extern ALLEGRO_BITMAP *bgBitmap;
extern ALLEGRO_BITMAP *goalBitmap;
extern ALLEGRO_BITMAP *duck1Bitmap;
extern ALLEGRO_BITMAP *duck2Bitmap;
extern ALLEGRO_BITMAP *obstacleBitmap;
extern ALLEGRO_BITMAP *levelBitmap;
extern ALLEGRO_BITMAP *leftArrowBitmap;
extern ALLEGRO_BITMAP *rightArrowBitmap;

#endif //INFIX_GLOBALS_H
