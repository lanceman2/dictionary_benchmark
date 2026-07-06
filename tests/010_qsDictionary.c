#include <stdio.h>

#include "debug.h"
#include "Dictionary.h"


int main(void) {

    struct QsDictionary *d = qsDictionaryCreate();
    ASSERT(d);


    WARN("d=%p", d);


    qsDictionaryDestroy(d);

    return 0;
}
