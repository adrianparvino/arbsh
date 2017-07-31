typedef struct object object; 
size_t object_size(void); 
object *object_init(object *);
object *object_populate(object *, char *);
void object_write(object *o);


