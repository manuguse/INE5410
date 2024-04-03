#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct MinMax {
    int min;
    int max;
} MinMax;

MinMax *getMinMax(int *vector, int size) {
    MinMax *a;
    a = (MinMax *) malloc(sizeof(MinMax));
    a->min = vector[0];
    a->max = vector[0];
    for (int i = 1; i < size; ++i) {
        if (vector[i] < a->min) {
            a->min = vector[i];
        } else if (vector[i] > a->max) {
            a->max = vector[i];
        }
    }
    return a;
}

void initVector(int *vector, int size) {
    srand ( time(NULL) );
    printf("[ ");
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;
        printf("%d ", vector[i]);
    }
    printf("]\n");
}

int min_max() {
    int vector[10];
    initVector(vector, 10);
    MinMax *m;
    m = getMinMax(vector, 10);
    printf("Min: %d\n", m->min);
    printf("Max: %d\n", m->max);
    free(m);
    return 0;
}
