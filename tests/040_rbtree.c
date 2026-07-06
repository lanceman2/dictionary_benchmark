#include <stdio.h>

#include "debug.h"
#include "c-rbtree.h"


int main(void) {


    CRBTree t;
    struct CRBNode n;
    struct CRBNode m;
    struct CRBNode o;

    c_rbtree_init(&t);

    ASSERT(c_rbtree_is_empty(&t));

    c_rbnode_init(&n);
    c_rbnode_init(&m);
    c_rbnode_init(&o);

    c_rbtree_add(&t, 0/*parent*/, &t.root, &n);
    c_rbtree_add(&t, 0/*parent*/, &t.root, &m);
    c_rbtree_add(&t, 0/*parent*/, &t.root, &o);


    return 0;
}
