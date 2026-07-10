#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <sys/resource.h>

#include "interfaces.h"
#include "common.h"

#include "d_src/debug.h"

#include DICTIONARY_WRAPPER



int main(int argc, char **argv) {

    //size_t n = 1000000;
    size_t n = 100;

    if(argc >= 2 &&
            !(argv[1][0] >= '0' && argv[1][0] <= '9')) {
        printf("Usage: %s [NUMBER_OF_ELEMENTS]\n", argv[0]);
        return 1;
    }

    if(argc >= 2) {
        errno = 0;
        n = strtoul(argv[1], 0, 10);
        if(errno) {
            ERROR("strtoul(\"%s\",0,10) failed", argv[1]);
            return 1;
        }
    }
    struct timespec t0 = { 0, 0 };
    ASSERT(clock_gettime(CLOCK_REALTIME, &t0) == 0);
    ASSERT(t0.tv_sec);


    Init(3);

    struct Tree *d;
    d = tree_create();

    tree_insert(d, "foo", 3, (void *) 1);
    tree_insert(d, "foo", 3, (void *) 2);

    char k[MaxLen + 1];
    k[0] = '\0';

    for(size_t i=3; i<n; ++i) {
        size_t len;
        char *key = GetKey(&len);

        // Try to remove a key once in a while.
        if((i % 321) == 0) {
            if(k[0]) {
                tree_remove(d, k, len);
                k[0] = '\0';
            } else
                strcpy(k, key);
        }

        tree_insert(d, key, len, (void *) ((uint64_t)i));
    }

    //tree_print(d);

    tree_destroy(d);


    struct timespec t1 = { 0, 0 };
    ASSERT(clock_gettime(CLOCK_REALTIME, &t1) == 0);
    ASSERT(t1.tv_sec);

    double dt = t1.tv_sec - t0.tv_sec + 1.0e-9 * (t1.tv_nsec - t0.tv_nsec);

    printf("%lf seconds\n", dt);

    struct rusage usage;

    ASSERT(0 == getrusage(RUSAGE_SELF, &usage));

    printf("mem usage: %ld MBytes\n", usage.ru_maxrss/1024);


    return 0;
}
