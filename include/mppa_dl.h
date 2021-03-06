/**
 * Copyright (C) 2018 Kalray SA.
 *
 *
 * \file mppa_dl.h
 * \brief libmppadl public interface.
 */

#ifndef MPPA_DL_H
#define MPPA_DL_H

#include <string.h>
#include <libelf.h>

#ifdef __mos__
#include <vbsp.h>
#endif

#include "mppa_dl_types.h"
#include "mppa_dl_error.h"
#include "mppa_dl_mem.h"
#include "mppa_dl_load.h"
#include "mppa_dl_sym.h"

#ifdef MPPADL_ENABLE_AUTOTRACE
#include "mppa_dl_autotraces.h"
#endif

/**
 * \brief Load a dynamic library.
 *
 * The function mppa_dl_load() loads a dynamic library memory image, pointed by
 * \a image and returns an opaque "handle" for the dynamic library.
 *
 * \param image Pointer to the start of the memory image to load.
 * \param flag Specify if symbols defined by this image will be made available
 * (MPPA_DL_GLOBAL), or won't be made available (MPPA_DL_LOCAL), for symbol
 * resolution of subsequently loaded images.
 * \return The \a handle of the loaded image on success, or NULL in
 * case of error (see mppa_dl_error())
 */
void *mppa_dl_load(const char *image, int flag);

/**
 * \brief Get the memory address of a symbol.
 *
 * The function mppa_dl_sym() returns the memory address of the null-terminated
 * symbol \a symbol from the \a handle of the dynamic library returned by
 * mppa_dl_load().
 *
 * \param handle The \a handle of the dynamic library where to look for
 * \a symbol.
 * \param symbol The symbol name (a null-terminated string).
 * \return The memory location where the symbol is loaded on success, or NULL on
 * error (see mppa_dl_error())
 */
void *mppa_dl_sym(void *handle, const char* symbol);

/**
 * \brief Unload a dynamic library.
 *
 * The mppa_dl_unload() unload the dynamic library handled by \a handle.
 *
 * \param handle The \a handle of the dynamic library to unload.
 * \return Zero on success, and nonzero on error (see mppa_dl_error()).
 */
int mppa_dl_unload(void *handle);

/**
 * \brief Translate errors to human readable strings.
 *
 * The function mppa_dl_error() returns a human readable string describing the
 * newest error arisen in mppa_dl_load(), mppa_dl_sym() or mppa_dl_unload()
 * since its last call.
 *
 * \return A string only if an error has occurred since initialization or the
 * last call of mppa_dl_error(), and NULL otherwise
 */
char *mppa_dl_error(void);

#endif
