#include "infix.h"
#include "utils.h"

int main() {
    if (initAll() != 0)
        return 1;
    infix();
    return 0;
}
