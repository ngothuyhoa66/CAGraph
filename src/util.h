// Copyright (C) 2016 Nguyen Ba Ngoc

#ifndef UTILS_H_
#define UTILS_H_

#include "libfdr/jval.h"

// parse int from an argument, return 1 if success, 0 if failed
extern int parse_int(char* arg, int* out);

extern int cmp_int(Jval v1, Jval v2);

#endif  // UTILS_H_
