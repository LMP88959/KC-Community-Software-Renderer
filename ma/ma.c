/*****************************************************************************/
/*
 * MApi - Module interface for the KC Community Software Renderer
 *
 *   by SAALTY, EIGHTFOLD 2023
 *
 * This software is released into the public domain.
 */
/*****************************************************************************/

#include "ma_priv.h"

/* ma.c
 *
 * Handles the compilation and interfacing of submodules.
 *
 */

#include <stdio.h>

#define MODULE_CAST(ty, ptr) ((struct MA_##ty##_MODULE*)(ptr))

static int has_compiled = 0;
static struct MA_COMPILED_SUBMODULES compiled_submodules;

static const char*
get_module_name(struct MA_MODULE_ENTRY e) {
    MA_MODULE mod = e.module;

    switch(e.type) {
        case MA_MODULETY_PREPROCESS:
            return MODULE_CAST(PREPROCESS, mod)->name;
        case MA_MODULETY_RASTER:
            return MODULE_CAST(RASTER, mod)->name;
        case MA_MODULETY_POSTPROCESS:
            return MODULE_CAST(POSTPROCESS, mod)->name;
        case MA_MODULETY_DISPLAY:
            return MODULE_CAST(DISPLAY, mod)->name;
    }

    return "<invalid-module>";
}

extern void 
MA_modules_init(void) {
    MA_init_bootstrap_list();
    MA_do_bootstrapping();
    compiled_submodules = MA_compile_bootstrap_list();
    has_compiled = 1;
}

extern void 
MA_modules_list(void) {
    struct MA_MODULE_ENTRY e;
    int idx;

    if(has_compiled == 0) {
        puts("You have to call MA_modules_init() first!\n");
        return;
    }

    printf("loaded modules[%i] {\n", compiled_submodules.count);
    for(idx = 0; idx < compiled_submodules.count; idx++) {
        e = compiled_submodules.submodules[idx];
        printf("\t%s\n", get_module_name(e));
    }
    printf("}\n");
}


/* TODO: Implement these */
extern void 
MA_module_load(const char *module_name) { }

extern void 
MA_module_unload(const char *module_name) { }

extern int 
MA_module_query(const char *module_name) {
    return 0;
}