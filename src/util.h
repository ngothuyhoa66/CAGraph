// Copyright (C) 2016 Nguyen Ba Ngoc

#ifndef UTILS_H_
#define UTILS_H_

#include "libfdr/jval.h"
#include "terms.h"

// parse int from an argument, return 1 if success, 0 if failed
extern int parse_int(char* arg, int* out);

// đọc đồ thị vô hướng, đỉnh số nguyên. Ví dụ định dạng tệp data\g.txt
extern int parse_graph_ud(char* fname, Graph* out);

// đọc đồ thị có hướng, đỉnh số nguyên. Ví dụ định dạng tệp data/g.txt
extern int parse_graph_d(char* fname, Graph* out);

// đọc đồ thị vô hướng, cạnh có trọng số, đỉnh số nguyên.
// Ví dụ định dạng tệp data/djk.txt
extern int parse_graph_dw(char* fname, Graph* out);

// đọc đồ thị vô hướng, đỉnh kiểu chuỗi, ví dụ định dạng tệp
// data/g_str.txt
int parse_graph_ustr(char* fname, Graph* out);

extern int cmp_int(Jval v1, Jval v2);

extern int cmp_str(Jval v1, Jval v2);

#endif  // UTILS_H_
