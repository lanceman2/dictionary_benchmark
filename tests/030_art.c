#include <stdio.h>

#include "debug.h"
#include "art.h"


int main(void) {


    art_tree t;

    int r = art_tree_init(&t);

    ASSERT(r == 0);

    void *oldVal = art_insert(&t, (void *) "hell", 4, (void *) 1);

    ASSERT(oldVal == 0);

    INFO("t=%p", &t);

    art_tree_destroy(&t);

    return 0;
}
