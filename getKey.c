/* Not thread-safe, not reentrant, and not efficient */

// It wastes random bits.  But, does it gain a little back by not bit
// picking from the random source?  CPUs use a whole word to act on bits.
// So not calling rand() as much may not save a lot.  We just need this to
// work.

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "d_src/debug.h"

static_assert(MaxLen > 2);

static char key[MaxLen + 1];
// We limit the alphabet so as to get more duplicate keys.
static const char *Encode = "ABCDEFG";
#define MinLen (2)

static_assert(MinLen <= MaxLen);

// Maximum number of random bits
#define MASK  (0xFFFF)

static_assert(MaxLen < MASK);


// Maximum of rand() | MASK
//
#define RMAX ((size_t) RAND_MAX | MASK)


static size_t GC_mult;


static inline size_t Rand(void) {

    // Because we are using the value like a dumb ass and multiplying it
    // by a number larger than one.  We don't want numbers overflowing.
    return rand() | MASK;
}


static inline size_t GetLength(void) {

    // This is very wasteful of random bits and will not give its limiting
    // (maximum) value as often as it should.

    size_t l = Rand();
    l *= (MaxLen - MinLen - 1);
    l /= (size_t)(RMAX);

    //ASSERT(l < MaxLen - MinLen, "l=%zu", l);

    return l + MinLen;
}


static char GetChar(void) {

    // This is very wasteful of random bits and will not give its limiting
    // (maximum) value as often as it should.

    size_t l = (Rand() * GC_mult)/RMAX;

    //ASSERT(l <= strlen(Encode) - 1, "l=%zu", l);

    return *(Encode + l);
}


void Init(unsigned int seed) {

    srand(seed);
    GC_mult = strlen(Encode) - 1;

    ASSERT(GC_mult < MASK);
}


// This returns a pointer to a null terminated char string, key.
//
char *GetKey(size_t *len) {

    size_t l = GetLength();
    *len = l;

    char *s = key;
    for(; l; --l, ++s)
        *s = GetChar();
    *s = '\0';

    return key;
}
