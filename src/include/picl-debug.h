#ifndef PICL_DEBUG_H
# define PICL_DEBUG_H

//# define DEBUG

# ifdef DEBUG
#  define debug_print(...) fprintf(stderr, __VA_ARGS__);
# else
#  define debug_print(...)
# endif

# ifdef DEBUG
#  define debug_obj(obj) PiclObject_dump(obj);
# else
#  define debug_obj 1 ? (void) 0 : PiclObject_dump
# endif


#endif // ! PICL_DEBUG_H