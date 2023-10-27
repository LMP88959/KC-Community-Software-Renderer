/*****************************************************************************/
/*
 * FW LE (Lite edition) - Fundamentals of the King's Crook graphics engine.
 *
 *   by EMMIR 2018-2022
 *
 *   YouTube: https://www.youtube.com/c/LMP88
 *
 * This software is released into the public domain.
 */
/*****************************************************************************/

#ifndef FW_PRIV_H
#define FW_PRIV_H

/*  fw_priv.h
 *
 * Functions and macros intended to be private to the FW library.
 *
 */

#include "fw.h"

#if FW_OS_TYPE_WINDOWS && defined(KC_OS_WIN_BUILD)
/* explicit build version */
#  if KC_OS_WIN_BUILD >= 10240
#    define _WIN32_WINNT 0x0605
#    define WINVER 0x0605
#  else
#    error Windows >8.1 required for AdjustWindowRectExForDpi!
#  endif
#endif

/***********************************************************************/

KC_BEGIN_C_HEADER

#define FW_CALC_PITCH(w, bpp) ((((w) * (bpp)) + 3) & ~3)
#define FW_BYTE_ALIGN(w, bpp) (FW_CALC_PITCH(w, bpp) / (bpp))

extern void clk_init(void);      /* initialize clock interface */
extern void pkb_poll(void);      /* gets called every loop */
extern int wnd_osm_handle(void); /* poll the operating system for events */
extern void wnd_term(void);      /* clean up and close the active window */

KC_END_C_HEADER

#endif
