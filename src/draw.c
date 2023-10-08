//
// Created by miloszek on 08.10.23.
//

#include "infix.h"
#include "draw.h"
#include "globals.h"
#include "operation.h"


void drawBase () {
    al_draw_bitmap(bgBitmap, 0, 0, 0);
}

void drawMenu (int lvl) {
    al_draw_text(comicLarge, al_map_rgb(255, 255, 255), 0, 0, 0, "instrukcja znajduje sie w dokumentacji");
    al_draw_text(comicSmall, al_map_rgb(255, 255, 255), 300, 75, 0, "infix");
    al_draw_text(comicLarge, al_map_rgb(255, 255, 255), 350, 175, 0, "bardzo fajna gra matematyczna");
    al_draw_text(comicLarge, al_map_rgb(255, 30, 255), 255, 275, 0,
                 "wybierz poziom za pomoca strzalek i wcisnij spacje!");
    al_draw_bitmap(levelBitmap, 380, 350, 0);
    al_draw_bitmap(leftArrowBitmap, 260, 373, 0);
    al_draw_bitmap(rightArrowBitmap, 544, 380, 0);
    al_draw_bitmap(levelBitmap, 380, 350, 0);
    al_draw_textf(comicSmall, al_map_rgb(255, 255, 255), 410, 360, 0, "%d", lvl);
}

void drawUI (struct timer timer, int opArray[]) {
    al_draw_textf(comicSmall, al_map_rgb(255, 255, 255), 0, 0, 0, "%d %c %d =", EQ_VAR1, EQ_OP, EQ_VAR2);
    al_draw_textf(comicSmall, al_map_rgb(255, 255, 255), 600, 0, 0, "%.2f", ALLEGRO_MSECS_TO_SECS(
            timer.gameTime - timer.startTime) * 20); // todo is this really 20?
}

void drawCharacters (int *sprite, int *klatka, int rozwiazane) {
    if (!sprite) {
        al_draw_bitmap(duck2Bitmap, playerPos.x, BASE_Y, 0);
        if (*klatka >= 15) {
            *sprite = 1;
            *klatka = 0;
        }
    } else {
        al_draw_bitmap(duck1Bitmap, playerPos.x, BASE_Y, 0);
        if (*klatka >= 15) {
            *sprite = 0;
            *klatka = 0;
        }
    }

    // draw obstacles
    for (int i = rozwiazane; i <= 5; ++i) {
        al_draw_bitmap(obstacleBitmap, (float) i * 150, BASE_Y, 0);
    }
    al_draw_bitmap(goalBitmap, 850, 399, 0);
}

void drawUserGuess (int guess) {
    al_draw_textf(comicSmall, al_map_rgb(255, 255, 255), 300, 200, 0, "Your guess: %d", guess);
}

void drawVictoryScreen (struct timer timer) {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_bitmap(bgBitmap, 0, 0, 0);
        al_draw_text(comicSmall, al_map_rgb(255, 255, 255), 300, 0, 0, "Gratulacje!");
        al_draw_textf(comicLarge, al_map_rgb(255, 30, 255), 350, 100, 0, "Poziom ukonczony!");
        al_draw_textf(comicLarge, al_map_rgb(255, 30, 255), 350, 200, 0, "Twoj czas to %.2f s.", ALLEGRO_MSECS_TO_SECS(
                timer.gameTime - timer.startTime));
        al_draw_text(comicLarge, al_map_rgb(255, 30, 255), 250, 300, 0,
                     "Wcisnij spacje, aby powrocic do menu glownego");
    }