/*****************************************************************************/
/*
 * MApi - Module interface for the KC Community Software Renderer
 *
 *   by SAALTY, EIGHTFOLD 2023
 *
 * This software is released into the public domain.
 */
/*****************************************************************************/

#ifndef MA_MAIN_H
#define MA_MAIN_H

/* ma.h
 *
 * Main header file for the module api.
 *
 */

#ifdef __cplusplus
#  define KC_BEGIN_C_HEADER FW_C_API {
#  define KC_END_C_HEADER }
#  define KC_C_API extern "C"
#else
#  define KC_BEGIN_C_HEADER
#  define KC_END_C_HEADER
#  define KC_C_API
#endif

/*****************************************************************************/

KC_BEGIN_C_HEADER

#define MA_MODULETY_PREPROCESS    1
#define MA_MODULETY_RASTER        2
#define MA_MODULETY_POSTPROCESS   3
#define MA_MODULETY_DISPLAY       4

/* Defines a submodule.
 * You must define a `LIB_init` function that
 * returns a `struct MA_MODULE_ENTRY`.
 * 
 * eg. MA_REGISTER_SUBMODULE(FOO)
 */
#define MA_REGISTER_SUBMODULE(lib)              \
struct MA_SUBMODULE lib##_smnode;               \
extern void lib##_load_submodule(void)          \
{   lib##_smnode.module_data = lib##_init();    \
    MA_bootstrap_submodule(&lib##_smnode); }

/* Registers a submodule through cmake defines */
#ifdef MA_SUBMODULE_NAME_
#  define MA_DEFAULT_REGISTER_SUBMODULE()       \
   MA_REGISTER_SUBMODULE_I(MA_SUBMODULE_NAME_)
#  define MA_REGISTER_SUBMODULE_I(lib)          \
   MA_REGISTER_SUBMODULE(lib)
#endif

/* Describes an arbitrary non-struct data type */
struct MA_DATA_TYPE {
    int bytes;
    int isfloat;
};

/* I/O structure for modules */
struct MA_MODULE_DATA {
    void *data; // Zero on failure, non-zero on success
    int size;

    struct MA_DATA_TYPE data_type;
};

/* I/O structure for postprocessing modules */
struct MA_MODULE_DATA_FRAME {
    void *color; // Zero on failure, non-zero on success
    void *aux; // Can be used for depth buffering, whatever
    int res_x;
    int res_y;

    struct MA_DATA_TYPE data_type_color;
    struct MA_DATA_TYPE data_type_aux;
};

/*****************************************************************************/

typedef void *MA_MODULE;

struct MA_PREPROCESS_MODULE {
    struct MA_MODULE_DATA(*entry)(struct MA_MODULE_DATA in);
    struct MA_DATA_TYPE data_type;
    const char *name;
};

struct MA_RASTER_MODULE {
    struct MA_MODULE_DATA_FRAME(*entry)(struct MA_MODULE_DATA in);
    struct MA_DATA_TYPE data_type;
    const char *name;
};

struct MA_POSTPROCESS_MODULE {
    struct MA_MODULE_DATA_FRAME(*entry)(struct MA_MODULE_DATA_FRAME in);
    struct MA_DATA_TYPE data_type;
    const char *name;
};

struct MA_DISPLAY_MODULE {
    void(*entry)(struct MA_MODULE_DATA_FRAME in);
    struct MA_DATA_TYPE data_type;
    const char *name;
};

/*****************************************************************************/

struct MA_PIPELINE {
    struct MA_PREPROCESS_MODULE *preprocess_modules;
    int preprocess_modules_size;

    /* Not an array, only one rasterizer can be active */
    struct MA_RASTER_MODULE *raster_module;

    struct MA_POSTPROCESS_MODULE *postprocess_modules;
    int postprocess_modules_size;

    /* Not an array, only one display backend can be active */
    struct MA_DISPLAY_MODULE *display_module;
};

struct MA_MODULE_ENTRY {
    /* Opaque pointer to any kind of module struct */
    MA_MODULE module;
    int type;
};

/* Only used for initial traversal */
struct MA_SUBMODULE {
    struct MA_MODULE_ENTRY module_data;
    struct MA_SUBMODULE *next;
};

extern void MA_modules_init(void);
extern void MA_modules_list(void); // Functionality undecided
extern void MA_module_load(const char *module_name);
extern void MA_module_unload(const char *module_name);
extern int MA_module_query(const char *module_name);

/* Provides the ability for modules to load themselves.
 * Returns the new number of submodules.
 * Pass NULL to query the current amount.
 */
extern int MA_bootstrap_submodule(struct MA_SUBMODULE *module_data);

KC_END_C_HEADER

#endif
