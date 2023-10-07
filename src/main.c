#include "infix.h"
#include "utils.h"

int main() {
    if (initAll() != 0)
        return 1;

    if (infix() == 0)
        return 0;
    else
        return 1;
}
