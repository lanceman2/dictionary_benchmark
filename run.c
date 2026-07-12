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


void PrintTime(struct timespec *t0) {
    ASSERT(t0);

    struct timespec t1 = { 0, 0 };
    ASSERT(clock_gettime(CLOCK_REALTIME, &t1) == 0);
    ASSERT(t1.tv_sec);

    double dt = t1.tv_sec - t0->tv_sec + 1.0e-9 * (t1.tv_nsec - t0->tv_nsec);
    printf("%3.5lf seconds\n", dt);
}


int main(int argc, char **argv) {

    //size_t n = 1000000;
    size_t n = 100000;
    //size_t n = 10;

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

    printf("\n%s %zu entries\n", argv[0], n);

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

    for(size_t i=0; i<n; ++i) {
        size_t len;
        char *key = GetKey(&len);

        // Try to remove a key once in a while.
        if((i % 321) == 0) {
            if(k[0]) {
                //tree_remove(d, k, len);
                k[0] = '\0';
            } else
                strcpy(k, key);
        }

        tree_insert(d, key, len, (void *) ((uint64_t)i));
    }

    printf("Built in ");
    PrintTime(&t0);

    ASSERT(clock_gettime(CLOCK_REALTIME, &t0) == 0);
    ASSERT(t0.tv_sec);

#define N_FIND_LOOPS  10

    for(int j=0; j<N_FIND_LOOPS; ++j) {

        Init(3);

        // This is where we should be fast.

        for(size_t i=0; i<n; ++i) {
            size_t len;
            char *key = GetKey(&len);
            tree_find(d, key, len);
        }
    }

    //tree_print(d);

    tree_destroy(d);

    printf("%d x %zu Finds in ", N_FIND_LOOPS, n);
    PrintTime(&t0);

    struct rusage usage;

    ASSERT(0 == getrusage(RUSAGE_SELF, &usage));

    // FIXME: Which is it?
    printf("memory usage: %2.2lf MB\n", usage.ru_maxrss/1000.0);
    //printf("memory usage: %2.2lf MB\n", usage.ru_maxrss/1024.0);


    return 0;
}
