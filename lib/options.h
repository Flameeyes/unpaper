// spdx-file_copyright_text: 2005 the unpaper authors
//
// spdx-license-identifier: gpl-2.0-only

#pragma once

#include "constants.h"
#include "parse.h"

typedef struct {
  Layouts layout;
  int start_sheet;
  int end_sheet;
  int start_input;
  int start_output;
  int input_count;
  int output_count;

  struct MultiIndex sheet_multi_index;
  struct MultiIndex exclude_multi_index;
  struct MultiIndex ignore_multi_index;
  struct MultiIndex insert_blank;
  struct MultiIndex replace_blank;

  // 0: allow all, -1: disable all, n: individual entries
  struct MultiIndex no_blackfilter_multi_index;
  struct MultiIndex no_noisefilter_multi_index;
  struct MultiIndex no_blurfilter_multi_index;
  struct MultiIndex no_grayfilter_multi_index;
  struct MultiIndex no_mask_scan_multi_index;
  struct MultiIndex no_mask_center_multi_index;
  struct MultiIndex no_deskew_multi_index;
  struct MultiIndex no_wipe_multi_index;
  struct MultiIndex no_border_multi_index;
  struct MultiIndex no_border_scan_multi_index;
  struct MultiIndex no_border_align_multi_index;
} options;

void options_init(options *o);
