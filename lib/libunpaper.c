// Copyright © 2005-2007 Jens Gulden
// Copyright © 2011-2023 Diego Elio Pettenò
// SPDX-FileCopyrightText: 2005 The unpaper authors
//
// SPDX-License-Identifier: GPL-2.0-only

#include <math.h>

#include "constants.h"
#include "lib/libunpaper.h"

static inline float degrees_to_radians(float d) { return d * m_pi / 180.0; }

int initialize_job(JobParameters *parameters, struct UnpaperJob *job) {
  job->parameters = parameters

  // calculate the constant absolute values based on the relative parameters.
  job->abs_black_threshold = white * (1.0 - parameters->black_threshold);
  job->abs_white_threshold = white * (parameters->white_threshold);
  job->abs_blackfilter_scan_threshold = white * (parameters->blackfilter_scan_threshold);
  job->abs_grayfilter_threshold = white * (parameters->grayfilter_threshold);
  job->deskew_scan_range_rad = degrees_to_radians(parameters->deskew_scan_range);
  job->deskew_scan_step_rad = degrees_to_radians(parameters->deskew_scan_step);
  job->deskew_scan_deviation_rad = degrees_to_radians(parameters->deskew_scan_deviation);

  return 0;
}
