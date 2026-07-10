// A dummy example that may give an idea of the benchmark program
// overhead.


struct Tree {

    void *dummy;
};


static inline struct Tree *tree_create(void) {

    return (void *) 0xFFF;
}

static inline void tree_destroy(struct Tree *d) { }

static inline bool tree_insert(struct Tree *d, char *s,
        size_t len, void *data) {

    return false;
}

static inline void tree_print(struct Tree *d) { }

static inline bool tree_remove(struct Tree *d, char *s, size_t len) {

    return false;
}

static inline void  *tree_find(struct Tree *d, char *s, size_t len) {

    return (void *) 0xFFF;
}
