
// This defines inline wrapper functions and structures to run the
// benchmark using the rax package.

#include <errno.h>

#include "common.h"
#include "d_src/rax.h"


struct Tree {

    rax rax;
};


static inline struct Tree *tree_create(void) {

    return (struct Tree *) raxNew();
}

static inline void tree_destroy(struct Tree *d) {

    raxFree((rax *) d);
}


static inline bool tree_insert(struct Tree *d, char *s,
        size_t len, void *data) {

    raxInsert((rax *) d, (unsigned char *) s, len, data, 0);

    DASSERT(errno == 0);

    return (errno == ENOMEM);
}


static inline void tree_print(struct Tree *d) {

    raxShow((rax *) d);
}

static inline bool tree_remove(struct Tree *d, char *s, size_t len) {

    raxRemove(&d->rax, (unsigned char *) s, len, 0);

    return false;
}

static inline void  *tree_find(struct Tree *d, char *s, size_t len) {

    return raxFind(&d->rax, (void *) s, len);
}
