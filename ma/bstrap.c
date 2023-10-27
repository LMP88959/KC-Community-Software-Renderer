/*****************************************************************************/
/*
 * MApi - Module interface for the KC Community Software Renderer
 *
 *   by EIGHTFOLD 2023
 *
 * This software is released into the public domain.
 */
/*****************************************************************************/

#include "ma_priv.h"

/* bstrap.c
 *
 * Implements the submodule bootstrapper.
 *
 */

#include <stdlib.h>

/* .module_data is always NULL as it's just the header */
static int submodules_count = 0;
static struct MA_SUBMODULE submodules_list_begin[1];
static struct MA_SUBMODULE *submodules_list_end = NULL;

extern void 
MA_init_bootstrap_list(void) {
    submodules_list_end = &submodules_list_begin[0];
    submodules_list_begin[0] = (struct MA_SUBMODULE) {
        .module_data = NULL,
        .next = NULL,
    };
}

extern int
MA_bootstrap_submodule(struct MA_SUBMODULE *module_data) {
    if(module_data == NULL) {
        return submodules_count;
    }

    submodules_count++;
    submodules_list_end->next = module_data;
    submodules_list_end = module_data;
    return submodules_count;
}

extern struct MA_COMPILED_SUBMODULES 
MA_compile_bootstrap_list(void) {
    struct MA_COMPILED_SUBMODULES submodule_data;
    struct MA_SUBMODULE *curr;
    int idx = 0;

    submodule_data.pipeline = (struct MA_PIPELINE){ 0 };
    submodule_data.count = submodules_count;
    if(submodules_count == 0) {
        submodule_data.submodules = NULL;
        return submodule_data;
    }

    submodule_data.submodules = malloc(
        submodules_count * sizeof(struct MA_MODULE_ENTRY));

    curr = submodules_list_begin->next;
    for(; curr != NULL; curr = curr->next, idx++) {
        submodule_data.submodules[idx] = 
            curr->module_data;
    }

    return submodule_data;
}
