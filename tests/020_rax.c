#include <stdio.h>

#include "debug.h"
#include "rax.h"


int main(void) {

    rax *d = raxNew();
    ASSERT(d);


    WARN("d=%p", d);


    int r = raxInsert(d, (void *) "hell", 4, (void *) 1, 0);

    ASSERT(r==1);
    
    r = raxInsert(d, (void *) "hello", 5, (void *) 2, 0);

    ASSERT(r==1);

    r = raxInsert(d, (void *) "hellasdf", 8, (void *) 3, 0);

    ASSERT(r==1);

    // Add the string null terminator to the key.
    r = raxInsert(d, (void *) "hellasdf", 9, (void *) 4, 0);

    ASSERT(r==1);
     


    raxShow(d);

    INFO();

    raxFree(d);

    return 0;
}
