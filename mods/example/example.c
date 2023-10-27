/*****************************************************************************/
/*
 * MApi - Module interface for the KC Community Software Renderer
 *
 *   by EIGHTFOLD 2023
 *
 * This software is released into the public domain.
 */
/*****************************************************************************/

#include <ma.h>

struct MA_POSTPROCESS_MODULE EXAMPLE_mod;

struct MA_MODULE_DATA_FRAME exec(struct MA_MODULE_DATA_FRAME in) {
    struct MA_MODULE_DATA_FRAME frame = { 0 };
    return frame;
}

static struct MA_MODULE_ENTRY 
EXAMPLE_init(void) {
    struct MA_MODULE_ENTRY entry;

    EXAMPLE_mod.entry = &exec;
    EXAMPLE_mod.data_type = (struct MA_DATA_TYPE) {
        .bytes = 4, .isfloat = 1
    };
    EXAMPLE_mod.name = "example-mod";

    entry.module = &EXAMPLE_mod;
    entry.type = MA_MODULETY_POSTPROCESS;

    return entry;
}

MA_DEFAULT_REGISTER_SUBMODULE()
