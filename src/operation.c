//
// Created by miloszek on 08.10.23.
//

#include "utils.h"
#include "operation.h"

void opGen(int opArray[], int lvl) {
    srand(time(0));
    EQ_VAR1 = randIntInRange(2 * lvl, 5 * lvl);
    EQ_VAR2 = randIntInRange(2 * lvl, 5 * lvl);
    EQ_OP = rand() % 4; 

    //... a opArray[3] to wynik
    switch (EQ_OP) {
        case 0:
            EQ_RES = EQ_VAR1 + EQ_VAR2;
            EQ_OP = 43;
            return;
        case 1:
            EQ_RES = EQ_VAR1 - EQ_VAR2;
            EQ_OP = 45;
            while (EQ_RES < 0) {
                EQ_VAR1 = randIntInRange(2 * lvl, 5 * lvl);
                EQ_VAR2 = randIntInRange(2 * lvl, 5 * lvl);
                EQ_RES = EQ_VAR1 - EQ_VAR2;
            }
            return;
        case 2:
            EQ_VAR1 = randIntInRange(1 * lvl, 3 * lvl); // nerf mnozenia
            EQ_VAR2 = randIntInRange(1 * lvl, 3 * lvl);
            EQ_RES = EQ_VAR1 * EQ_VAR2;
            EQ_OP = 42;
            return;
        case 3:
            EQ_RES = EQ_VAR1 / EQ_VAR2;
            EQ_OP = 47;
            while (EQ_RES <= 0 || EQ_RES == 1 || EQ_VAR1 % EQ_VAR2 != 0) {
                EQ_VAR1 = randIntInRange(1 * lvl, 5 * lvl);
                EQ_VAR2 = randIntInRange(1 * lvl, 5 * lvl);
                EQ_RES = EQ_VAR1 / EQ_VAR2;
            }
            return;
    }
}

