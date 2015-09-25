#include <stdio.h>
#include "perf-gear.h"

int add(int a, int b) {
    pg_m_item_t* m1 = PG_NEW_MEASUREMENT("examples/c/example1/add", PG_MEASUREMENT_TYPE_HIT);
    PG_INCREASE_HIT(m1);
    PG_STOP_COLLECTING(m1);

    return a + b;
}

int main() {
    printf("Starting c-example1.c\n");
    
    pg_config_t config = {
        .folder = "/tmp/pg_examples/example1",
        .url = "http://localhost:3000/api/measurements"
    };

    PG_START(&config);
    
    printf("1 + 2 = %i", add(1, 2));

    PG_STOP();
}
