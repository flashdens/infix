/* todo:
   struct???
   japierdole

   tofix:
   gra muli
   czas
 */

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
    int x = 0, y = 425, klatka = 0, sprite = 0, rozwiazane = 1, lvl = 5, liczba1, liczba2, wynik, znak, tabGrowa[4], bufor1;
    char bufor2[6];
    bool cannons = true, rysuj = true, wygrana = false, menuGlowne = true, stworzonoDzialanie = false;

    int init = inicjujAllegro();
    if (init) {
        return 1;
    }

    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_FONT *comicDuzy = al_load_ttf_font("./COMIC.ttf", 64, 0);
    ALLEGRO_FONT *comicMaly = al_load_ttf_font("./COMIC.ttf", 20, 0);
    ALLEGRO_BITMAP *tlo = al_load_bitmap("tlo.png");
    ALLEGRO_BITMAP *goal = al_load_bitmap("goal.png");
    ALLEGRO_BITMAP *kaczkaRuch1 = al_load_bitmap("./walk1.png");
    ALLEGRO_BITMAP *kaczkaRuch2 = al_load_bitmap("./walk2.png");
    ALLEGRO_BITMAP *przeszkoda = al_load_bitmap("./przeszkoda.jpg");
    ALLEGRO_BITMAP *levelSelect = al_load_bitmap("./malpa.png");
    ALLEGRO_BITMAP *strzalkaLewo = al_load_bitmap("./strzalkaLewo.png");
    ALLEGRO_BITMAP *strzalkaPrawo = al_load_bitmap("./strzalkaPrawo.png");
    ALLEGRO_TIMER *timer;
    ALLEGRO_SAMPLE *menu = al_load_sample("./menu.wav");
    ALLEGRO_SAMPLE *ok = al_load_sample("./ok.wav");
    ALLEGRO_SAMPLE *notok = al_load_sample("./notok.wav");
    ALLEGRO_SAMPLE *win = al_load_sample("./win.wav");
    ALLEGRO_SAMPLE *lose = al_load_sample("./lose.wav");
    ALLEGRO_SAMPLE *game = al_load_sample("./game.ogg");
    ALLEGRO_KEYBOARD_STATE keyState;

    display = al_create_display(960, 540);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60.0);
    if (!display)printf("dupa\n");
    printf("hehe xd\n");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);
    al_play_sample(menu, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
    // da game loop
    DWORD czas;
    while (cannons) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        al_get_keyboard_state(&keyState);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            cannons = false;
        if (event.type = ALLEGRO_EVENT_TIMER) {
            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
                x += 2;
            else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
                x -= 2;
            else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
                cannons = false;
                break;
            }
            rysuj = true;
        }
        if (rysuj) {
            al_draw_bitmap(tlo, 0, 0, 0);
            while (menuGlowne) {
                al_draw_text(comicDuzy, al_map_rgb(255, 255, 255), 100, 100, 0, "infix");
                al_draw_text(comicMaly, al_map_rgb(255, 255, 255), 200, 200, 0, "bardzo fajna gra matematyczna");
                al_draw_text(comicMaly, al_map_rgb(255, 30, 255), 200, 300, 0, "wybierz poziom!");
                al_draw_bitmap(levelSelect, 444, 330, 0);
                al_draw_bitmap(strzalkaLewo, 344, 330, 0);
                al_draw_bitmap(strzalkaPrawo, 544, 330, 0);
                al_draw_textf(comicDuzy, al_map_rgb(255, 255, 255), 454, 330, 0, "%d", lvl);
                al_wait_for_event(queue, &event);
                al_get_keyboard_state(&keyState);
                if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    cannons = false;
                if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
                    cannons = false;
                    break;
                }
                if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_LEFT))
                    if (lvl > 1)
                        lvl--;
                if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
                    if (lvl < 20)
                        lvl++;
                if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_SPACE)) {
                    menuGlowne = false;
                    al_stop_samples();
                    al_play_sample(game, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    al_play_sample(ok, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                }
                al_flip_display();
                continue;
            }
            DWORD start = GetTickCount();
            al_draw_bitmap(tlo, 0, 0, 0);
            al_draw_bitmap(goal, 850, 399, 0);
            if (!sprite) {
                al_draw_bitmap(kaczkaRuch2, x, y, 0);
                if (klatka >= 20) {
                    sprite = 1;
                    klatka = 0;
                }
            } else {
                al_draw_bitmap(kaczkaRuch1, x, y, 0);
                if (klatka >= 20) {
                    sprite = 0;
                    klatka = 0;
                }
            }
            if (!stworzonoDzialanie) {
                stworzDzialanie(tabGrowa, lvl);
                liczba1 = tabGrowa[0];
                liczba2 = tabGrowa[1];
                znak = tabGrowa[2];
                wynik = tabGrowa[3];
                stworzonoDzialanie = true;
            }
            czas = GetTickCount() - start;
            al_draw_textf(comicDuzy, al_map_rgb(255, 255, 255), 200, 100, 0, "%d %c %d =", liczba1, znak, liczba2);
            al_draw_textf(comicDuzy, al_map_rgb(255, 255, 255), 300, 300, 0, "%d.%3d", czas / 1000,
                          czas - czas / 1000);
            printf("%d ", klatka);
            printf("%d\n", sprite);

            for (int i = rozwiazane; i <= 5; ++i) {
                al_draw_bitmap(przeszkoda, 150 * i, y, 0);
            }
            if (x % 150 == 0 && x != 0) {
                while (cannons) {
                    al_get_keyboard_state(&keyState);
                    al_wait_for_event(queue, &event);
                    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                        wprowadzLiczbeDoBufora(bufor2, event);
                        bufor1 = atoi(bufor2);
                        printf("%d\n", bufor1);
                        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                            cannons = false;
                        if (bufor1 == wynik) {
                            al_play_sample(ok, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                            x += 2;
                            rozwiazane++;
                            bufor1 = 0;
                            memset(bufor2, 0, strlen(bufor2));
                            stworzonoDzialanie = false;
                            break;
                        }
                    }
                }
            }
            if (rozwiazane == 6 && !wygrana) {
                al_play_sample(win, 2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                wygrana = true;
            }

            while (wygrana) {
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_bitmap(tlo, 0, 0, 0);
                al_draw_text(comicDuzy, al_map_rgb(255, 255, 255), 200, 0, 0, "Gratulacje!");
                al_draw_textf(comicMaly, al_map_rgb(255, 30, 255), 200, 100, 0, "Poziom %d ukonczony!", lvl);
                al_draw_textf(comicMaly, al_map_rgb(255, 30, 255), 200, 200, 0, "Twoj czas to %d", czas / 1000);
                al_draw_text(comicMaly, al_map_rgb(255, 30, 255), 200, 300, 0,
                             "Wcisnij enter, aby powrocic do menu glownego");
                al_get_keyboard_state(&keyState);
                if (event.type = ALLEGRO_KEY_DOWN && al_key_down(&keyState, ALLEGRO_KEY_ENTER)) {
                    wygrana = false;
                    menuGlowne = true;
                    rozwiazane = 1;
                    al_stop_samples();
                    al_play_sample(ok, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    x = 0;
                }
                al_flip_display();
            }
            al_flip_display();
            rysuj = false;
            klatka++;
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
