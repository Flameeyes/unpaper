// Copyright © 2005-2007 Jens Gulden
// Copyright © 2011-2011 Diego Elio Pettenò
// SPDX-FileCopyrightText: 2005 The unpaper authors
//
// SPDX-License-Identifier: GPL-2.0-only

/* --- global declarations ------------------------------------------------ */

#pragma once

#include <math.h>
#include <stdbool.h>

#include <libavutil/frame.h>

#include "constants.h"

#include "api/unpaper.pb-c.h"

/* --- preprocessor macros ------------------------------------------------ */

#define pluralS(i) ((i > 1) ? "s" : "")

void errOutput(const char *fmt, ...) __attribute__((format(printf, 1, 2)))
__attribute__((noreturn));

/* --- global variable ---------------------------------------------------- */

extern JobParameters *parameters;

extern VERBOSE_LEVEL verbose;
extern INTERP_FUNCTIONS interpolateType;

extern unsigned int absBlackThreshold;
extern unsigned int absWhiteThreshold;
extern unsigned int absBlackfilterScanThreshold;
extern unsigned int absGrayfilterThreshold;
extern float deskewScanRangeRad;
extern float deskewScanStepRad;
extern float deskewScanDeviationRad;

extern struct MultiIndex noBlackfilterMultiIndex;
extern struct MultiIndex noNoisefilterMultiIndex;
extern struct MultiIndex noBlurfilterMultiIndex;
extern struct MultiIndex noGrayfilterMultiIndex;
extern struct MultiIndex noMaskScanMultiIndex;
extern struct MultiIndex noMaskCenterMultiIndex;
extern struct MultiIndex noDeskewMultiIndex;
extern struct MultiIndex noWipeMultiIndex;
extern struct MultiIndex noBorderMultiIndex;
extern struct MultiIndex noBorderScanMultiIndex;
extern struct MultiIndex noBorderAlignMultiIndex;
extern struct MultiIndex sheetMultiIndex;
extern struct MultiIndex excludeMultiIndex;
extern struct MultiIndex ignoreMultiIndex;
extern struct MultiIndex insertBlank;
extern struct MultiIndex replaceBlank;

extern int autoborder[MAX_MASKS][EDGES_COUNT];
extern int autoborderMask[MAX_MASKS][EDGES_COUNT];
extern bool overwrite;
extern int dpi;

/* --- tool function for file handling ------------------------------------ */

void loadImage(const char *filename, AVFrame **image);

void saveImage(char *filename, AVFrame *image, int outputPixFmt);

void saveDebug(char *filenameTemplate, int index, AVFrame *image)
    __attribute__((format(printf, 1, 0)));

/* --- arithmetic tool functions ------------------------------------------ */

static inline float degreesToRadians(float d) { return d * M_PI / 180.0; }

static inline void limit(int *i, int max) {
  if (*i > max) {
    *i = max;
  }
}

#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

#define max3(a, b, c)                                                          \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    __typeof__(c) _c = (c);                                                    \
    (_a > _b ? (_a > _c ? _a : _c) : (_b > _c ? _b : _c));                     \
  })

#define min3(a, b, c)                                                          \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    __typeof__(c) _c = (c);                                                    \
    (_a < _b ? (_a < _c ? _a : _c) : (_b < _c ? _b : _c));                     \
  })

#define red(pixel) ((pixel >> 16) & 0xff)
#define green(pixel) ((pixel >> 8) & 0xff)
#define blue(pixel) (pixel & 0xff)

static inline int pixelValue(uint8_t r, uint8_t g, uint8_t b) {
  return (r) << 16 | (g) << 8 | (b);
}
