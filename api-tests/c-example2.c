#include <stdio.h>
#include "perf-gear.h"


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

    PG_STOP();
}
