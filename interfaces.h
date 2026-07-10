// This defines common interfaces for all the dictionary packages that we
// will benchmark.  We write a header wrapper file for each package that
// we benchmark.

#include <stdbool.h>


// Namespace tree and Tree

struct Tree;


static inline struct Tree *tree_create(void);

static inline void tree_destroy(struct Tree *d);

// Return false on success.  Will overwrite if node exists.
static inline bool tree_insert(struct Tree *d, char *s,
        size_t len, void *data);

static inline bool tree_remove(struct Tree *d, char *s, size_t len);

// Print to stdout
static inline void tree_print(struct Tree *d);

