#include <stdio.h>
#include "helper.h"

int lanjut() {
    char lanjut;
    while (1==1) {
        printf("Sekali lagi? [Y]a/[T]idak): ");
        scanf(" %c", &lanjut);
        fflush(stdin);
        if (lanjut == 'T' || lanjut == 't')
            return 1;
        else if (lanjut == 'Y' || lanjut == 'y')
            break;
    }
    return 0;
}
