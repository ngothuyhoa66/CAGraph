// Copyright (C) 2016 Nguyen Ba Ngoc

#include "util.h"

#include <stdio.h>

int parse_int(char* arg, int* out) {
  return sscanf(arg, "%d", out);
}

// int cmp_int(Jval v1, Jval v2) {
//   if (jval_i(v1) < jval_i(v2))
//     return -1;
//   if (jval_i(v1) > jval_i(v2))
//     return 1;
//   return 0;
// }
