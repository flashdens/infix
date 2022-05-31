//
// Created by milosy on 26/05/2022.
//

#ifndef SAMPLE_FUNKCJEGROWE_H
#define SAMPLE_FUNKCJEGROWE_H

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

#endif //SAMPLE_FUNKCJEGROWE_H
