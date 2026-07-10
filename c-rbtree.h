// This is not intended to preform well.  It's intended to give a base
// level that should be beaten easily.  Using a RB-tree to make a
// dictionary is not a great thing, but I expect it's done all the time.


// This defines inline wrapper functions and structures to run the
// benchmark using the c-rbtree red black tree package.

#include <errno.h>
#include <stdlib.h>
#include <assert.h>

#include "d_src/c-rbtree.h"

struct Tree {

    struct CRBTree tree;
};

struct Node {

    // Not a good way to make a node.

    struct CRBNode node;

    char *key;

    uintptr_t value;
};


static inline struct Tree *tree_create(void) {

    struct Tree *t;
    t = calloc(1, sizeof(*t));
    ASSERT(t, "calloc(1,%zu) failed", sizeof(*t));

    c_rbtree_init(&t->tree);

    return t;
}


static inline bool tree_remove(struct Tree *d, char *s, size_t len) {

    CRBNode *i = d->tree.root;
    struct Node *n;

    while(i) {

        n = c_rbnode_entry(i, struct Node, node);

        size_t cmp = strncmp(n->key, s, len);

        if(cmp < 0)
            i = i->left;
        else if(cmp > 0)
            i = i->right;
        else
            break;
    }
    if(!i) {
        //ERROR("Node \"%s\" was not found", s);
        return true;
    }

    DASSERT(n->key);

    free(n->key);

    c_rbnode_unlink(&n->node);

    free(n);

    return false;
}


static inline void tree_destroy(struct Tree *d) {

    CRBNode *i;

    // Not sure this it the best way to do this.
    //
    while((i = c_rbtree_first(&d->tree))) {

        struct Node *n = c_rbnode_entry(i, struct Node, node);
        DASSERT(n);
        c_rbnode_unlink(&n->node);
        DASSERT(n->key);
        free(n->key);
        free(n);
    }

    free(d);
}


static inline bool tree_insert(struct Tree *d, char *s,
        size_t len, void *data) {

    CRBNode **i = &d->tree.root;
    CRBNode *parent = 0;

    //ERROR("Inserting \"%s\"", s);

    while(*i) {

        parent = *i;

        struct Node *n = c_rbnode_entry(*i, struct Node, node);

        DASSERT(n);
        DASSERT(n->key);

        // This is not good.
        //
        int cmp = strncmp(s, n->key, len);

        if(cmp < 0)
            i = &parent->left;
        else if(cmp > 0)
            i = &parent->right;
        else {
            // Just change the entry
            n->value = (uintptr_t) data;
            //WARN("key=%s", s);
            return false;
        }
    }

    struct Node *n;
    n = calloc(1, sizeof(*n));
    ASSERT(n, "calloc(1,%zu) failed", sizeof(*n));

    c_rbnode_init(&n->node);

    n->value = (uintptr_t) data;
    n->key = malloc(len + 1);
    ASSERT(n->key, "malloc(%zu) failed", len + 1);
    strncpy(n->key, s, len);
    n->key[len] = '\0';

    c_rbtree_add(&d->tree, parent, i, &n->node);

    return false;
}


static inline void *tree_find(struct Tree *d, char *s, size_t len) {

    CRBNode **i = &d->tree.root;
    CRBNode *parent = 0;

    while(*i) {

        parent = *i;

        struct Node *n = c_rbnode_entry(*i, struct Node, node);

        DASSERT(n);
        DASSERT(n->key);

        int cmp = strncmp(s, n->key, len);

        if(cmp < 0)
            i = &parent->left;
        else if(cmp > 0)
            i = &parent->right;
        else {
            // Found it.
            //ERROR("Found \"%s\": %p", s, (void *) n->value);
            return (void *) n->value;
        }
    }

    //ERROR("Node \"%s\" was not found", s);
    return 0;
}

static inline void tree_print(struct Tree *d) {}

