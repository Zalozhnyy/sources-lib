#include <stdio.h>

#include "sources_api.h"

int main() {
    printf("Hello, World!\n");
    init_sources();
    printf("%e", getAmplitude(8));
    return 0;
}
