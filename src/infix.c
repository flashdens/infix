#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>

#include "infix.h"
#include "utils.h"
#include "draw.h"
#include "operation.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

struct playerPos playerPos;

struct timer timer;

ALLEGRO_EVENT event;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *allegroTimer = NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_FONT *comicSmall = NULL;
ALLEGRO_FONT *comicLarge = NULL;
ALLEGRO_BITMAP *bgBitmap = NULL;
ALLEGRO_BITMAP *goalBitmap = NULL;
ALLEGRO_BITMAP *duck1Bitmap = NULL;
ALLEGRO_BITMAP *duck2Bitmap = NULL;
ALLEGRO_BITMAP *obstacleBitmap = NULL;
ALLEGRO_BITMAP *levelBitmap = NULL;
ALLEGRO_BITMAP *leftArrowBitmap = NULL;
ALLEGRO_BITMAP *rightArrowBitmap = NULL;
ALLEGRO_SAMPLE *menu = NULL;
ALLEGRO_SAMPLE *gameSt = NULL;
ALLEGRO_SAMPLE *ok = NULL;
ALLEGRO_SAMPLE *win = NULL;

int infix() {

    bool initError = false;

    queue = al_create_event_queue();
    if (!queue) {
        printf("Error creating the event queue\n");
        initError = true;
        goto cleanup;
    }
    al_register_event_source(queue, al_get_keyboard_event_source());

    // init allegroTimer
    allegroTimer = al_create_timer(1.0 / 60.0);
    if (!allegroTimer) {
        printf("Error creating allegroTimer\n");
        initError = true;
        goto cleanup;
    }

    // init display
    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        printf("Error creating display\n");
        initError = true;
        goto cleanup;
    }

    // init fonts
    comicSmall = al_load_ttf_font("fonts/COMIC.TTF", 64, 0);
    if (!comicSmall) {
        printf("Error loading small font\n");
        initError = true;
        goto cleanup;
    }

    comicLarge = al_load_ttf_font("fonts/COMIC.TTF", 20, 0);
    if (!comicLarge) {
        printf("Error loading large font\n");
        initError = true;
        goto cleanup;
    }

    // init bitmaps
    bgBitmap = al_load_bitmap("bitmaps/base/bg.png");
    if (!bgBitmap) {
        printf("Error loading bg.png\n");
        initError = true;
        goto cleanup;
    }

    goalBitmap = al_load_bitmap("bitmaps/game/goal.png");
    if (!goalBitmap) {
        printf("Error loading goal.png\n");
        initError = true;
        goto cleanup;
    }

    duck1Bitmap = al_load_bitmap("bitmaps/game/duck1.png");
    if (!duck1Bitmap) {
        printf("Error loading duck1.png\n");
        initError = true;
        goto cleanup;
    }

    duck2Bitmap = al_load_bitmap("bitmaps/game/duck2.png");
    if (!duck2Bitmap) {
        printf("Error loading duck2.png\n");
        initError = true;
        goto cleanup;
    }

    obstacleBitmap = al_load_bitmap("bitmaps/game/obstacle.jpg");
    if (!obstacleBitmap) {
        printf("Error loading obstacle.jpg\n");
        initError = true;
        goto cleanup;
    }

    levelBitmap = al_load_bitmap("bitmaps/menu/monke.png");
    if (!levelBitmap) {
        printf("Error loading monke.png\n");
        initError = true;
        goto cleanup;
    }

    leftArrowBitmap = al_load_bitmap("bitmaps/menu/left.png");
    if (!leftArrowBitmap) {
        printf("Error loading left.png\n");
        initError = true;
        goto cleanup;
    }

    rightArrowBitmap = al_load_bitmap("bitmaps/menu/right.png");
    if (!rightArrowBitmap) {
        printf("Error loading right.png\n");
        initError = true;
        goto cleanup;
    }

    // Initialize samples
    menu = al_load_sample("samples/st/menu.wav");
    if (!menu) {
        printf("Error loading menu.wav\n");
        initError = true;
        goto cleanup;
    }

    gameSt = al_load_sample("samples/st/game.ogg");
    if (!gameSt) {
        printf("Error loading game.ogg\n");
        initError = true;
        goto cleanup;
    }

    ok = al_load_sample("samples/fx/ok.wav");
    if (!ok) {
        printf("Error loading ok.wav\n");
        initError = true;
        goto cleanup;
    }

    win = al_load_sample("samples/fx/win.wav");
    if (!win) {
        printf("Error loading win.wav\n");
        initError = true;
        goto cleanup;
    }

    al_play_sample(menu, 0, 0, 1, ALLEGRO_PLAYMODE_LOOP, 0);

    int klatka = 0, sprite = 0, rozwiazane = 1, lvl = 5;
    int liczba1, opArray[4], userGuess;
    char bufor2[6] = {'\0'};
    bool cannons = true, wygrana = false, menuGlowne = true, stworzonoDzialanie = false, game = false, solve = false;

    // da game loop
    while (cannons) {

        if (menuGlowne) {
            al_get_next_event(queue, &event);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    goto cleanup;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    if (lvl > 0)
                        lvl--;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    if (lvl < 20)
                        lvl++;
                }

                // start the game
                else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    menuGlowne = false;
                    al_stop_samples();
                    al_play_sample(gameSt, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    al_play_sample(ok, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    timer.startTime = al_get_timer_count(allegroTimer);
                    al_start_timer(allegroTimer);
                    game = true;
                }
            }
        }

        if (game) {
            timer.gameTime = al_get_timer_count(allegroTimer) - timer.startTime;
            // handle player move
            al_get_keyboard_state(&keyState);
            if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
                goto cleanup;
            } else if (!solve) {
                if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
                    playerPos.x += 2;
                else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
                    playerPos.x -= 2;

                if ((int) playerPos.x % 150 == 0 && playerPos.x != 0) {
                    solve = true;
                }
            }

            // handle equation generation
            if (!stworzonoDzialanie) {
                opGen(opArray, lvl);
                stworzonoDzialanie = true;
            }
        }

        // handle solving
        if (solve) {
            al_get_next_event(queue, &event);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                al_get_next_event(queue, &event);
                updateResultBuf(bufor2, event);
                userGuess = atoi(bufor2);
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    goto cleanup;
                if (userGuess == EQ_RES) {
                    al_play_sample(ok, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                    playerPos.x += 2;
                    rozwiazane++;
                    memset(bufor2, 0, strlen(bufor2));
                    stworzonoDzialanie = false;
                    userGuess = 0;
                    solve = false;
                    game = true;
                }
            }
        }

        if (rozwiazane == 6) {
            al_stop_timer(allegroTimer);
            al_play_sample(win, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
            wygrana = true;
            game = false;
            rozwiazane = 0;
        }

        if (wygrana) {
            al_wait_for_event(queue, &event);
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                cannons = false;
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                cannons = false;
            if (event.type == al_key_down(&keyState, ALLEGRO_KEY_SPACE)) {
                wygrana = false;
                menuGlowne = true;
                rozwiazane = 1;
                al_stop_samples();
                al_play_sample(ok, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
                playerPos.x = 0;
                timer.gameTime = 0;
            }
        }
        klatka++;

        drawBase();
        if (menuGlowne) {
            drawMenu(lvl);
        }

        // draw game screen
        if (game || solve) {
            drawUI(timer, opArray);
            drawCharacters(&sprite, &klatka, rozwiazane);
        }

        // draw user input
        if (solve) {
            drawUserGuess(userGuess);
        }

        // draw victory screen
        if (wygrana) {
            drawVictoryScreen(timer);
        }
        // finally draw
        al_flip_display();
    }

    cleanup:
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_font(comicSmall);
    al_destroy_font(comicLarge);
    al_destroy_timer(allegroTimer);
    al_uninstall_keyboard();
    al_destroy_bitmap(bgBitmap);
    al_destroy_bitmap(duck1Bitmap);
    al_destroy_bitmap(duck2Bitmap);
    al_destroy_bitmap(obstacleBitmap);
    al_destroy_bitmap(levelBitmap);
    al_destroy_bitmap(leftArrowBitmap);
    al_destroy_bitmap(rightArrowBitmap);
    al_destroy_event_queue(queue);
    al_destroy_sample(menu);
    al_destroy_sample(ok);
    al_destroy_sample(win);
    al_destroy_sample(gameSt);

    if (!initError)
        return 0;
    else
        return 1;
}
