/*****************************************************************************/
/*
 * MApi - Module interface for the KC Community Software Renderer
 *
 *   by SAALTY, EIGHTFOLD 2023
 *
 * This software is released into the public domain.
 */
/*****************************************************************************/

#ifndef MA_PRIV_H
#define MA_PRIV_H

#include "ma.h"

/* ma_priv.h
 *
 * Contains functions and structs only used internally.
 *
 */

#include <stdint.h>

KC_BEGIN_C_HEADER

#ifndef NULL
#  define NULL ((void *)0)
#endif

struct MA_COMPILED_SUBMODULES {
    struct MA_MODULE_ENTRY *submodules;
    int count;

    struct MA_PIPELINE pipeline;
};

extern void MA_init_bootstrap_list(void);
extern struct MA_COMPILED_SUBMODULES MA_compile_bootstrap_list(void);

/* Autogenerated, in mods/modloader.c.in */
extern void MA_do_bootstrapping(void);

KC_END_C_HEADER

#endif