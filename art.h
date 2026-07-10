
// This defines inline wrapper functions and structures to run the
// benchmark using the libart package.

#include <errno.h>

#include "common.h"
#include "d_src/art.h"


struct Tree {

    art_tree art;
};


static inline struct Tree *tree_create(void) {

    struct Tree *t;
    t = malloc(sizeof(*t));
    ASSERT(t, "malloc(%zu) failed", sizeof(*t));
    ASSERT(0 == art_tree_init(&t->art));

    return t;
}

static inline void tree_destroy(struct Tree *d) {

    // What does this do?
    ASSERT(0 == art_tree_destroy((void *) d));

    free((void *) d);
}

static inline bool tree_insert(struct Tree *d, char *s,
        size_t len, void *data) {

    art_insert((void *) d, (const unsigned char *) s, len, data);

    return false;
}

static inline void tree_print(struct Tree *d) { }


static inline bool tree_remove(struct Tree *d, char *s, size_t len) {

    art_delete((void *) d, (const unsigned char *) s, len);
    return false;
}

static inline void  *tree_find(struct Tree *d, char *s, size_t len) {

    void *ret = art_search((void *) d, (const unsigned char *) s, len);
    return ret;
}
