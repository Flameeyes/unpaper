// Copyright © 2005-2007 Jens Gulden
// Copyright © 2011-2023 Diego Elio Pettenò
// SPDX-FileCopyrightText: 2005 The unpaper authors
//
// SPDX-License-Identifier: GPL-2.0-only

#pragma once

#include "api/unpaper.pb-c.h"

struct UnpaperJob {
  // Input parameters (usually provided on command line).
  extern JobParameters *parameters;
  
  // Calculated variables based on the input parameters.
  unsigned int abs_black_threshold;
  unsigned int abs_white_threshold;
  unsigned int abs_blackfilter_scan_threshold;
  unsigned int abs_grayfilter_threshold;
  float deskew_scan_range_rad;
  float deskew_scan_step_rad;
  float deskew_scan_deviation_rad;
};

int initialize_job(JobParameters *parameters, struct UnpaperJob *job);
