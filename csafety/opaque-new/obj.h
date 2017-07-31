/* obj.h */



typedef struct obj obj;





/*
 * The compiler considers struct obj an incomplete type. Incomplete types
 * can be used in declarations.
 */

size_t obj_size(void);

void obj_setid(obj *, int);
//void obj_setid(none *, int);

//int obj_getid(obj *);
