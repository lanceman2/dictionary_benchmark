
// This defines inline wrapper functions and structures to run the
// benchmark using the rax package.

#include <errno.h>

#include "common.h"
#include "d_src/Dictionary.h"


struct Tree;


static inline struct Tree *tree_create(void) {

    return (void *) qsDictionaryCreate();
}

static inline void tree_destroy(struct Tree *d) {

    qsDictionaryDestroy((void *) d);
}


static inline bool tree_insert(struct Tree *d, char *s,
        size_t len, void *data) {

    qsDictionaryInsert((void *) d, s, data, 0);

    return false;
}


static inline void tree_print(struct Tree *d) {

}

static inline bool tree_remove(struct Tree *d, char *s, size_t len) {

    qsDictionaryRemove((void *) d, s);

    return false;
}
