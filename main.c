#include <stdio.h>
#include <allegro5/allegro.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <allegro5/allegro_native_dialog.h>
#include <unistd.h>

int losujLiczbe(int lower, int upper) {
    int liczba = (rand() % (upper - lower + 1)) + lower;
    return liczba;
}

int stworzDzialanie(int liczba1, int liczba2) {
    srand(time(0));
    int l = rand() % 4;
    int wynik;
    switch (l) {
        case 0:
            wynik = liczba1 + liczba2;
            printf("   %d\n+  %d\n", liczba1, liczba2);
            break;
        case 1:
            wynik = liczba1 - liczba2;
        warunkiOdejmowania:
            if (wynik < 0) {
                liczba1 = losujLiczbe(1, 20);
                liczba2 = losujLiczbe(1, 20);
                wynik = liczba1 - liczba2;
                goto warunkiOdejmowania;
            }
            printf("   %d\n-  %d\n", liczba1, liczba2);
            break;
        case 2:
            wynik = liczba1 * liczba2;
            printf("   %d\n*  %d\n", liczba1, liczba2);
            break;
        case 3:
            wynik = liczba1 / liczba2;
        warunkiDzielenia:
            if (wynik <= 0 || liczba1 % liczba2 != 0) {
                liczba1 = losujLiczbe(1, 20);
                liczba2 = losujLiczbe(1, 20);
                wynik = liczba1 / liczba2;
                goto warunkiDzielenia;
            }
            printf("   %d\n/  %d\n", liczba1, liczba2);
            break;
    }
    return wynik;
}

int main() {
//    bool cannons = false;
//    ALLEGRO_DISPLAY *display = NULL;
//    if(!al_init())printf("cos sie zepsulo\n");
//    display = al_create_display(1920, 1080);
//    if(!display)printf("dupa\n");
//    printf("hehe xd\n");
//    cannons = true;
//    while(cannons){
//        al_flip_display();
//    }
    srand(time(0));
    int ilePozostalo = 5;
    int lvl;
    printf("Ktory poziom?\n");
    scanf("%d", &lvl);
    DWORD start = GetTickCount();
    DWORD czas;
    while (ilePozostalo) {
        int liczba1 = losujLiczbe(1 * lvl, 5 * lvl);
        int liczba2 = losujLiczbe(1 * lvl, 5 * lvl);
        int szukana = stworzDzialanie(liczba1, liczba2);
        int zgadnieta;
        while (1) {
            scanf("%d", &zgadnieta);
            if (zgadnieta == szukana) break;
            else printf("Zla odpowiedz! Probuj dalej...\n");
        }
        ilePozostalo--;
        printf("Pozostalo jeszcze %d przykladow\n", ilePozostalo);
        czas = GetTickCount() - start;
        if (czas > 30000) break;
    }
    if (czas > 30000) printf("Porazka. Towarzyszu! Przekroczyliscie dozwolony czas!\n");
    else printf("Zwyciestwo. Gratulacje!\nRunda zajela %d.%3d sekund.\n", czas / 1000, czas - czas / 1000);
    return 0;
}
