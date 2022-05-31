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
#include <stdarg.h>
#include "funkcjeGrowe.h"
#include "funkcjeAllegrowe.h"


int main() {
    int x = 0, y = 425, ktory = 0, sprite = 0, rozwiazane = 1;
    bool cannons = true, rysuj = true, wygrana = false;
    const float FPS = 60.0;

    int init = inicjujAllegro();
    if (init) {
        return 1;
    }

    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *font = al_load_ttf_font("./COMIC.ttf", 64, 0);
    ALLEGRO_BITMAP *tlo = NULL;
    ALLEGRO_BITMAP *kaczkaRuch1 = al_load_bitmap("./walk1.png");
    ALLEGRO_BITMAP *kaczkaRuch2 = al_load_bitmap("./walk2.png");
    ALLEGRO_BITMAP *przeszkoda = al_load_bitmap("./przeszkoda.jpg");
    ALLEGRO_TIMER *timer;
    ALLEGRO_SAMPLE *menu = al_load_sample("./menu.wav");
    ALLEGRO_SAMPLE *ok = al_load_sample("./ok.wav");
    ALLEGRO_SAMPLE *notok = al_load_sample("./notok.wav");
    ALLEGRO_SAMPLE *win = al_load_sample("./win.wav");
    ALLEGRO_SAMPLE *lose = al_load_sample("./lose.wav");
    ALLEGRO_KEYBOARD_STATE keyState;

    display = al_create_display(960, 540);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);
    if (!display)printf("dupa\n");
    printf("hehe xd\n");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    tlo = al_load_bitmap("tlo.png");
    al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "huj");
    // da game loop
    DWORD start = GetTickCount();
    DWORD czas;
    al_start_timer(timer);
    al_play_sample(menu, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
    al_draw_bitmap(tlo, 0, 0, 0);
    while (cannons) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&keyState);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            cannons = false;
        if (event.type = ALLEGRO_EVENT_TIMER) {
            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
                x += 2;
            } else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
                x -= 2;
            } else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
                cannons = false;
                break;
            }
            rysuj = true;
        }
        if (rysuj) {
            czas = GetTickCount() - start;
            // do ujednolicenia!!!
            if (!sprite) {
                al_draw_bitmap(tlo, 0, 0, 0);
                al_draw_bitmap(kaczkaRuch1, x, y, 0);
                czas = GetTickCount() - start;
                al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 300, 0, "%d.%3d", czas / 1000, czas - czas / 1000);
                printf("%d\n", x);
                for (int i = rozwiazane; i <= 5; ++i) {
                    al_draw_bitmap(przeszkoda, 150 * i, y, 0);
                }
                if (x % 150 == 0 && x != 0) {
                    while (1) {
                        printf("Przeszkoda!\n");
                        al_get_keyboard_state(&keyState);
                        if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_5)) {
                            al_play_sample(notok, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        }
                        if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_4)) {
                            al_play_sample(ok, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                            x += 4;
                            rozwiazane++;

                            break;
                        }
                    }
                }
                if (rozwiazane == 6 && wygrana == false) {
                    printf("Koniec!\n");
                    al_play_sample(win, 2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    wygrana = true;
                }
                ktory++;
                if (ktory >= 20) {
                    sprite = 1;
                    ktory = 0;
                }
            } else {
                al_draw_bitmap(tlo, 0, 0, 0);
                printf("%d\n", x);
                al_draw_bitmap(kaczkaRuch2, x, y, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 300, 300, 0, "%d.%3d", czas / 1000, czas - czas / 1000);
                for (int i = rozwiazane; i <= 5; ++i) {
                    al_draw_bitmap(przeszkoda, 150 * i, y, 0);
                }
                if (x % 150 == 0 && x != 0) {
                    while (1) {
                        printf("Przeszkoda!\n");
                        al_draw_text(font, al_map_rgb(255, 255, 255), 300, 300, 0, "2+2");
                        al_get_keyboard_state(&keyState);
                        if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_5)) {
                            al_play_sample(notok, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        }
                        if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_4)) {
                            al_play_sample(ok, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                            x += 4;
                            rozwiazane++;
                            break;
                        }
                    }
                }

                if (rozwiazane == 6 && czas > 30000 && win == false) {
                    al_play_sample(lose, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    win = true;
                }
                if (rozwiazane == 6 && win == false) {
                    printf("Koniec!\n");
                    al_play_sample(win, 2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    win = true;
                }
                ktory++;
                if (ktory >= 20) {
                    sprite = 0;
                    ktory = 0;
                }
            }
            al_flip_display();
            rysuj = false;
        }
    }
    // naura
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_uninstall_keyboard();
    al_destroy_bitmap(tlo);
    al_destroy_event_queue(queue);
    return 0;
}
