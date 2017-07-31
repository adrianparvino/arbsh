/* obj.c */
#include <stdio.h>
#include "obj.h"

struct obj {
    int id;
};




/*
 * The caller will handle allocation.
 * Provide the required information only
 */

size_t obj_size(void) {
    return sizeof(obj);
}

void obj_setid(obj *o, int i) {
    o->id = i;
}

int obj_getid(obj *o) {
    return o->id;
}

