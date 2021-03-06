/**
 * Copyright (C) 2018 Kalray SA.
 */

#ifndef MPPA_DL_MEM_H
#define MPPA_DL_MEM_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "mppa_dl_error.h"

void *(*mppa_dl_memalign)(size_t, size_t);
void *(*mppa_dl_malloc)(size_t);
void (*mppa_dl_free)(void *);

void mppa_dl_set_memalign(void *(*ptr)(size_t , size_t ));
void mppa_dl_set_malloc(void *(*ptr)(size_t));
void mppa_dl_set_free(void (*ptr)(void *));

#ifdef __rtems__
void * mppa_dl_rtems_memalign_wrapper(size_t boundary, size_t size);
#endif

#endif
