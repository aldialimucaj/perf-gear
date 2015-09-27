#include <stdio.h>
#include "perf-gear.h"
#include "c-example2.h"

typedef struct { int h, w; double *x;} matrix_t, *matrix;

int add(int a, int b) {
    pg_m_item_t* m1 = PG_NEW_MEASUREMENT("examples/c/example2/add", PG_MEASUREMENT_TYPE_HIT);
    PG_INCREASE_HIT(m1);
    PG_STOP_COLLECTING(m1);

    return a + b;
}

int add2(int a, int b) {
    PG_AUTO_HIT("examples/c/example2/add2");

    return a + b;
}

int fibonacci_at(int i) {
    PG_AUTO_HIT("examples/c/example2/fibonacci_at");
    if(i <= 2) return 1;
    return fibonacci_at(i - 1) + fibonacci_at(i - 2);
}


inline double dot(double *a, double *b, int len, int step)
{
    double r = 0;
    while (len--) {
        r += *a++ * *b;
        b += step;
    }
    return r;
}

matrix mat_new(int h, int w)
{
    matrix r = malloc(sizeof(matrix_t) + sizeof(double) * w * h);
    r->h = h, r->w = w;
    r->x = (double*)(r + 1);
    return r;
}

matrix mat_mul(matrix a, matrix b)
{
    PG_AUTO_TIMESTAMP_TAG("examples/c/example2/mat_mul","start");
    matrix r;
    double *p, *pa;
    int i, j;
    if (a->w != b->h) return 0;

    r = mat_new(a->h, b->w);
    p = r->x;
     
    PG_AUTO_TIMESTAMP_TAG("examples/c/example2/mat_mul","created");
    for (pa = a->x, i = 0; i < a->h; i++, pa += a->w)
        for (j = 0; j < b->w; j++)
            *p++ = dot(pa, b->x + j, a->w, b->w);


    PG_AUTO_TIMESTAMP_TAG("examples/c/example2/mat_mul","end");
    return r;
}

void mat_show(matrix a)
{
    int i, j;
    double *p = a->x;
    for (i = 0; i < a->h; i++, putchar('\n'))
        for (j = 0; j < a->w; j++)
            printf("\t%7.3f", *p++);
    putchar('\n');
}

int main() {
    printf("Starting c-example2.c\n");

    pg_config_t config = {
        .folder = "/tmp/pg_examples/example2",
        .url = "http://localhost:3000/api/measurements"
    };

    PG_START(&config);

    printf("1 + 2 = %i\n", add(1, 2));

    printf("1 + 2 = %i\n", add2(1, 2));
    printf("3 + 4 = %i\n", add2(3, 4));
    printf("5 + 6 = %i\n", add2(5, 6));

    printf("fibonacci @ 5 = %i\n", fibonacci_at(5));
    printf("fibonacci @ 9 = %i\n", fibonacci_at(9));
    printf("fibonacci @ 27 = %i\n", fibonacci_at(27));


    double da[] = { 1, 1,  1,   1,
        2, 4,  8,  16,
        3, 9, 27,  81,
        4,16, 64, 256   };
    double db[] = {     4.0,   -3.0,  4.0/3,
        -13.0/3, 19.0/4, -7.0/3,
        3.0/2,   -2.0,  7.0/6,
        -1.0/6,  1.0/4, -1.0/6};

    matrix_t a = { 4, 4, da }, b = { 4, 3, db };
    matrix c = mat_mul(&a, &b);

    /* mat_show(&a), mat_show(&b); */
    mat_show(c);

    PG_STOP();
}
