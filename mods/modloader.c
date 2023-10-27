#include <ma.h>

#define MA_SUBMODULE_LIST  X(EXAMPLE_load_submodule)

#define X(name) extern void name(void);
MA_SUBMODULE_LIST
#undef X

extern void 
MA_do_bootstrapping(void) {
#define X(name) name();
    MA_SUBMODULE_LIST
#undef X
}
